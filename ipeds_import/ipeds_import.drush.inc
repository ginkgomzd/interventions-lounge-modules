<?php

/**
 * @file
 * Load an ipeds csv from nces.ed.gov and update
 * College Profile custom fields, via drush framework.
 */

/**
 * Implementation of hook_drush_command().
 */
function ipeds_import_drush_command() {
    $items['update-ipeds'] = array(
        'description' =>
        'Update College Profile fields from a csv generated from nces.ed.gov',
        'aliases' => array('ipeds-up'),
        'options' => array(
            'csv' => 'CSV of Unit-ID Identified IPEDS data',
        ),
        'examples' => array(
            'drush ipeds-up --csv=ipeds_data.csv',
        ),
    );
    return $items;
}

/**
 * Command callback
 */
function drush_ipeds_import_update_ipeds() {
    $csv_file = drush_get_option('csv');

    if (!is_file($csv_file)) {
        die("\ninvalid csv file\nbe sure full path is provided.\n");
    }

    $ipeds = _ipeds_import_parse_csv($csv_file);

    $coll_profiles = _ipeds_import_get_college_profiles();
   $ipeds_drupal_map = _ipeds_import_field_map();

    $successes = 0;
    $failures = 0;
    foreach ($coll_profiles['node'] as $stub) {
        $node = node_load($stub->nid);
        $ipeds_data = _ipeds_import_get_data_for_node_by_unitid($node, $ipeds);

        _ipeds_import_update_fields(
                _ipeds_import_generate_fields_array($ipeds_data, $ipeds_drupal_map), 
                $node
                );

        if (TRUE) { //TODO: test success
            node_save($node);
            $successes++;
        } else {
            $failures++;
        }
    }

    if ($successes > 0) {
        drush_log(t('Update-Ipeds: Updated @number records.', array('@number' => $successes)), 'success');
    }

    if ($failures > 0) {
        drush_log(t('Update-Ipeds: failed for @number records.', array('@number' => $failures)), 'warning');
    }
}

function _ipeds_import_get_data_for_node_by_unitid($node, $ipeds) {
  $unit_id = $node->field_ipeds_unitid['und'][0]['value'];

  if (!isset($unit_id)) {
	echo "\n".'WARNING: $unit_id is not set; dump $node:'.var_export($node->title,true).' unitid:'.var_export($node->field_ipeds_unitid,true);
    return null;
  }

  return _ipeds_import_get_ipeds_row($ipeds, $unit_id);
}

/***
 * returns an array of associative arrays
 * first line of file is used for row-keys
 ***/
function _ipeds_import_parse_csv($filepath) {
    $fd = fopen($filepath, "r");

    while (!feof($fd)) {
        $line = fgets($fd);

        if (!isset($file_arr)) {
            $keys_arr = str_getcsv($line, ',', '"');
            $file_arr = array();
        } else {
            if ( count($keys_arr)!= count(str_getcsv($line, ',', '"')) ) {
                continue;
            }
            $file_arr[] = array_combine($keys_arr, str_getcsv($line, ',', '"'));
        }
    }
    fclose($fd);

    return _ipeds_import_generate_derrived_fields($file_arr);
}

/***
 * field_atd_grouping_hispanic
    0|0 to 12.5% Hispanic/Latino
    1|12.6 to 25% Hispanic/Latino
    2|More than 25% Hispanic/Latino

 * field_atd_grouping_black
    0|0 to 20% Black
    1|20.1 to 40% Black
    2|More than 40% Black

 * field_atd_grouping_pell
    0|0 to 15% Pell Recipients
    1|15.1 to 30% Pell Recipients
    2|More than 30% Pell Recipients
 ***/
function _ipeds_import_generate_derrived_fields(array $rows) {
  $field_map = array_flip(_ipeds_import_field_map()_);
  $hisp_row_key = $field_map['field_ipeds_pct_latino_dec'];
  $black_row_key = $field_map['field_ipeds_pct_black_dec'];
  $pell_row_key = $field_map['field_ipeds_pell_recipients_pct'];
    
  foreach ($rows as &$row) {
    $hispanic = $row[$hisp_row_key];
    $black = $row[$black_row_key];
    $pell = $row[$pell_row_key];

    if (isset($hispanic)) {
      $row ['hisp_grouped'] = _ipeds_import_get_tiers($hispanic,
              array('12.5' => 0, '25.0' => 1, '100' => 2)
      );
    }
    if (isset($black)) {
      $row['black_grouped'] = _ipeds_import_get_tiers($black,
              array('20.0' => 0, '40.0' => 1, '100' => 2)
      );
    }
    if (isset($pell)) {
      $row['pell_grouped'] = _ipeds_import_get_tiers($pell,
              array('20.0' => 0, '40.0' => 1, '60.0' => 2, '100' => 3)
      );
    }
  }

  return $rows;
}

function _ipeds_import_get_tiers($value, array $tiers) {
  foreach ($tiers as $max => $tier) {
    if ((float)$value <= (float) $max) {
      return $tier;
    }
  }
}

function _ipeds_import_field_map() {
    return array(
        "unitid" => 'field_ipeds_unitid',
        "institution name" => 'title',
        "year" => null,
        "HD2012.Institution size category" => "field_ipeds_inst_size_category",
        "HD2012.State abbreviation" => null,
        "HD2012.Geographic region" => 'field_ipeds_geo_region',
        "HD2012.Historically Black College or University" => 'field_ipeds_hbcu_text',
        "HD2012.Tribal college" => 'field_ipeds_tribal_text',
        "HD2012.Degree of urbanization (Urban-centric locale)" => 'field_ipeds_degree_of_urb',
        "HD2012.Carnegie Classification 2010: Basic" => 'field_ipeds_carnegie_2010',

        "DRVEF2012.Total  enrollment" => 'field_ipeds_total_enrollment',
        "DRVEF2012.Full-time enrollment" => 'field_ipeds_full_time_enrollment',
        "DRVEF2012.Part-time enrollment" => 'field_ipeds_part_time_enrollment',
        "DRVEF2012.First-time degree/certificate-seeking undergraduate enrollment" => 'field_ipeds_first_time',
        "DRVEF2012.Part-time first-time degree/certificate-seeking undergraduate enrollment" => 'field_ipeds_part_first',

        "DRVEF2012.Percent of total enrollment that are American Indian or Alaska Native" => 'field_ipeds_pct_indian_dec',
        "DRVEF2012.Percent of total enrollment that are Asian" => 'field_ipeds_pct_asian_dec',
        "DRVEF2012.Percent of total enrollment that are Black or African American" => 'field_ipeds_pct_black_dec',
        "DRVEF2012.Percent of total enrollment that are Hispanic/Latino" => 'field_ipeds_pct_latino_dec',
        "DRVEF2012.Percent of total enrollment that are Native Hawaiian or Other Pacific Islander" => 'field_ipeds_pct_pacific_dec',
        "DRVEF2012.Percent of total enrollment that are White" => 'field_ipeds_pct_white_dec',
        "DRVEF2012.Percent of total enrollment that are two or more races" => 'field_ipeds_pct_2more_dec',
        "DRVEF2012.Percent of total enrollment that are Race/ethnicity unknown" => 'field_ipeds_pct_unknown_dec',
        "DRVEF2012.Percent of total enrollment that are women" => 'field_ipeds_pct_women_dec',

	"SFA1112.Number of undergraduate students receiving Pell grants" => 'field_field_ipeds_num_pell',
	"SFA1112.Percent of undergraduate students receiving Pell grants" => 'field_ipeds_pell_recipients_pct',
	"C2012_B.Grand total women" => 'field_ipeds_num_women',
	"C2012_B.American Indian or Alaska Native total" => 'field_ipeds_num_indian',
	"C2012_B.Asian total" => 'field_ipeds_num_asian',
	"C2012_B.Black or African American total" => 'field_ipeds_num_black',
	"C2012_B.Hispanic or Latino total" => 'field_ipeds_num_latino',
	"C2012_B.Native Hawaiian or Other Pacific Islander total" => 'field_ipeds_num_pacific',
	"C2012_B.White total" => 'field_ipeds_num_white',
	"C2012_B.Two or more races total" => 'field_ipeds_num_2more',
	"C2012_B.Race/ethnicity unknown total" => 'field_ipeds_num_unknown',
// calculated grouping fields (not in csv), but should be present in this mapping:
	"hispanic_grouped" => 'field_field_atd_grouping_hispani',
	"black_grouped" => 'field_field_atd_grouping_black',
	"pell_grouped" => 'field_field_atd_grouping_pell',
    );
}

/**
 * Helper function
 *
 * Returns all College Profile nodes 
 */
function _ipeds_import_get_college_profiles() {
    $query = new EntityFieldQuery();

    $result = $query
            ->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'college_profile')
            ->execute();

    return $result;
}

function _ipeds_import_get_ipeds_row($ipeds_array, $unitid) {
    reset($ipeds_array);
    while ($row = next($ipeds_array)) {
        if ($row['unitid'] == $unitid)
            return $row;
    }
    return NULL;
}

function _ipeds_import_generate_fields_array($ipeds_record, $field_map) {
    $fields = array();
    foreach ($ipeds_record as $key => $value) {
        $field_name = $field_map[$key];
        
        $fields[$field_name] = array(
            'value' => array($value),
            'type' => 'text',
        );
    }
    return $fields;
}

/**
 * Very simple helper function to assign values to custom fields on entities
 * such as nodes or files. The primary purpose of this function is to capture in
 * one place the logic for navigating Drupal's field arrays.
 *
 * No validation is done to ensure that the custom
 * fields exist on the entity in question. (If they do not, expect silent
 * failure for just the fields that don't exist.)
 *
 * @param array $fields Expected structure is:
 *
 * $fields = array(
 *   'field_name_1' => array(
 *     'type' => 'text|number|float',
 *     'value' => array(
 *       'value_1',
 *       'value_2', // most fields will probably have just one value
 *     ),
 *   ),
 *   'field_name_2' => array(
 *     ...
 *   ),
 * );
 *
 * @param stdClass $entity A node or file (or other entity?) object, implicitly
 * passed by reference.
 */
function _ipeds_import_update_fields(array $fields, stdClass $entity) {

    $lang = (property_exists($entity, 'language') ? $entity->language : LANGUAGE_NONE);
    foreach ($fields as $fieldname => $data) {

       if (!array_key_exists('format', $data)) {
            $data['format'] = NULL;
        }
        
        if (!property_exists($entity, $fieldname)) {
            var_dump("\n".$fieldname . 'notfound');
            continue;
        }
        if (!is_array($entity->{$fieldname})) {
            var_dump("\n$fieldname is not array;");
            continue;
        }

        foreach ($data['value'] as $k => $v) {
            switch ($data['type']) {
                case 'float':
                    if (is_float($v) || ($v == (string) (float) $v)) {
                        $entity->{$fieldname}[$lang][$k]['value'] = $v;
                    }
                    break;
                case 'number':
                    $entity->{$fieldname}[$lang][$k]['value'] = (int) $v;
                    break;
                case 'text':
                    $entity->{$fieldname}[$lang][$k]['value'] = utf8_encode($v);
                    $entity->{$fieldname}[$lang][$k]['format'] = $data['format'];
            }
        }
    }
}
