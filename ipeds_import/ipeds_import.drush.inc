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
        //TODO: handle null
        die("\nsinvalid csv file\n");
    }

    $ipeds = _ipeds_import_parse_csv($csv_file);

    $coll_profiles = _ipeds_import_get_college_profiles();
    $sf_ipeds_id_map = _ipeds_import_external_id_unitid_map();
    //$sf_ipeds_id_map  = _ipeds_import_name_unitid_map();
    $ipeds_drupal_map = _ipeds_import_field_map();

    $successes = 0;
    $failures = 0;
    foreach ($coll_profiles['node'] as $stub) {
        $node = node_load($stub->nid);
        $sf_id = $node->field_external_id['und'][0]['value'];
        //var_dump($sf_id . "||" . array_key_exists($sf_id, $sf_ipeds_id_map));
        if (!isset($sf_id)) continue;
        //truncate ID to match bad id's in map
        $sf_id = substr($sf_id, 0, 15);
        if (array_key_exists($sf_id, $sf_ipeds_id_map)) {
            var_dump($sf_id);
            $ipeds_data = _ipeds_import_get_ipeds_row($ipeds, $sf_ipeds_id_map[$sf_id]);
        } else {
            continue;
        }

        _ipeds_import_update_fields(
                _ipeds_import_generate_fields_array($ipeds_data, $ipeds_drupal_map), 
                $node
                );

        if (TRUE) { //TODO: test success
            //TODO: update fields;
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

/*
 * returns an array of associative arrays
 * first line of file is used for row-keys
 * 
 */

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

    return $file_arr;
}

function _ipeds_import_field_map() {
    return array(
        "unitid" => 'field_ipeds_unitid',
        "instnm" => 'title',
        "year" => null,
        "hd2011.instsize:VL-Institution size category" => "field_ipeds_inst_size_category",
        "hd2011.stabbr:VL-State abbreviation" => null,
        "hd2011.obereg:VL-Geographic region" => 'field_ipeds_geo_region',
        "hd2011.hbcu:VL-Historically Black College or University" => 'field_ipeds_hbcu',
        "hd2011.tribal:VL-Tribal college" => 'field_ipeds_tribal',
        "hd2011.locale:VL-Degree of urbanization (Urban-centric locale)" => 'field_ipeds_degree_of_urb',
        "hd2011.ccbasic:VL-Carnegie Classification 2010: Basic" => 'field_ipeds_carnegie_2010',
        "drvef2011.enrtot:VL-Total  enrollment" => 'field_ipeds_total_enrollment',
        "drvef2011.enrft:VL-Full-time enrollment" => 'field_ipeds_full_time_enrollment',
        "drvef2011.enrpt:VL-Part-time enrollment" => 'field_ipeds_part_time_enrollment',
        "drvef2011.efug1st:VL-First-time degree/certificate-seeking undergraduate enrollment" => 'field_ipeds_first_time',
        "drvef2011.efug1spt:VL-Part-time first-time degree/certificate-seeking undergraduate enrollment" => 'field_ipeds_part_first',
        "drvef2011.pctenran:VL-Percent of total enrollment that are American Indian or Alaska Native" => 'field_ipeds_pct_indian_dec',
        "drvef2011.pctenras:VL-Percent of total enrollment that are Asian" => 'field_ipeds_pct_asian_dec',
        "drvef2011.pctenrbk:VL-Percent of total enrollment that are Black or African American" => 'field_ipeds_pct_black_dec',
        "drvef2011.pctenrhs:VL-Percent of total enrollment that are Hispanic/Latino" => 'field_ipeds_pct_latino_dec',
        "drvef2011.pctenrnh:VL-Percent of total enrollment that are Native Hawaiian or Other Pacific Islander" => 'field_ipeds_pct_pacific_dec',
        "drvef2011.pctenrwh:VL-Percent of total enrollment that are White" => 'field_ipeds_pct_white_dec',
        "drvef2011.pctenr2m:VL-Percent of total enrollment that are two or more races" => 'field_ipeds_pct_2more_dec',
        "drvef2011.pctenrun:VL-Percent of total enrollment that are Race/ethnicity unknown" => 'field_ipeds_pct_unknown_dec',
        "drvef2011.pctenrw:VL-Percent of total enrollment that are women" => 'field_ipeds_pct_women_dec',
    );
}

function _ipeds_import_external_id_unitid_map() {
    return array(
        '001U0000007PdGG' => '217615',
        '001U00000091nDY' => '138682',
        '001U0000007PdHT' => '222576',
        '001U0000007PdH6' => '161767',
        '001U00000091nDZ' => '106306',
        '001U0000007PdHU' => '197887',
        '001U0000007PdHV' => '246813',
        '001U00000091nDa' => '138840',
        '001U000000DJpc1' => '183655',
        '001U00000091nDb' => '138956',
        '001U0000007PdHW' => '222992',
        '001U0000008lCht' => '109819',
        '001U0000007PdHD' => '168883',
        '001U0000007PdGS' => '234696',
        '001U000000Vv7Vk' => '102429',
        '001U000000BBZOG' => '208275',
        '001U0000007PdHF' => '223506',
        '001U0000007PdFJ' => '132709',
        '001U0000007PdGA' => '165112',
        '001U0000007PdFK' => '129367',
        '001U00000091nFS' => '100760',
        '001U00000091nFT' => '140304',
        '001U0000007PdGU' => '198260',
        '001U0000007PdGu' => '175315',
        '001U000000YkD5B' => '111896',
        '001U0000007PdHY' => '234951',
        '001U0000007PdGV' => '223320',
        '001U0000008lCiH' => '182005',
        '001U0000007PdFO' => '226408',
        '001U0000007PdFP' => '107521',
        '001U000000BBZ4z' => '420556',
        '001U00000091nFV' => '202222',
        '001U00000091nFW' => '139357',
        '001U0000007PdFL' => '210605',
        '001U0000007PdFM' => '211079',
        '001U0000007PdFN' => '215239',
        '001U0000007PdHX' => '230861',
        '001U0000007Pd5o' => '184205',
        '001U0000007PdFR' => '202356',
        '001U0000007PdH9' => '144564',
        '001U0000007PdFS' => '231882',
        '001U0000007PdHZ' => '198376',
        '001U0000007PdFT' => '211927',
        '001U0000007PdHa' => '169521',
        '001U000000Xhy4Z' => '105297',
        '001U0000007PikK' => '187620',
        '001U0000007PdFU' => '198455',
        '001U0000007PdFV' => '203331',
        '001U0000007PdGv' => '161138',
        '001U0000007PdHb' => '113856',
        '001U0000007PdHc' => '235103',
        '001U0000007PdGw' => '224615',
        '001U0000007PdGW' => '144944',
        '001U0000007PdGD' => '224642',
        '001U0000007PdGX' => '235149',
        '001U0000007PdFW' => '224961',
        '001U00000091nFX' => '198570',
        '001U00000091nFY' => '244446',
        '001U0000007PdGZ' => '169974',
        '001U0000007PdHA' => '170055',
        '001U0000007PdHG' => '235334',
        '001U000000QfYrc' => '235343',
        '001U0000007PdGq' => '218113',
        '001U0000007PdFX' => '198622',
        '001U000000NUFRJ' => '140012',
        '001U0000007Pd5p' => '149842',
        '001U0000007PdFY' => '383190',
        '001U0000007PdGE' => '170055',
        '001U0000007PdFZ' => '235431',
        '001U0000007PdFE' => '134495',
        '001U0000007PdGJ' => '141680',
        '001U0000007PdGa' => '129543',
        '001U0000007PdFa' => '225423',
        '001U000000KFXte' => '134608',
        '001U0000007PdGb' => '440244',
        '001U0000007PdFb' => '170444',
        '001U0000007PdGx' => '156921',
        '001U0000007PdGK' => '141796',
        '001U0000007PdGL' => '141802',
        '001U0000007PdGc' => '226019',
        '001U0000008lCiz' => '190619',
        '001U000000BBZOe' => '428392',
        '001U0000007PdFd' => '170620',
        '001U0000007PdHH' => '209038',
        '001U0000007PdGd' => '170657',
        '001U0000007PdGB' => '226204',
        '001U0000007PdGM' => '141811',
        '001U000000AcgIi' => '209074',
        '001U0000007PdFe' => '227182',
        '001U0000007PdHI' => '203748',
        '001U0000007PdHJ' => '117788',
        '001U0000007PdGe' => '117690',
        '001U0000007PdHK' => '117867',
        '001U0000007PdGy' => '117715',
        '001U0000007PdHL' => '117724',
        '001U0000007Pd5r' => '117733',
        '001U0000007PdHd' => '170790',
        '001U0000007PdFf' => '198905',
        '001U000000DHiUR' => '135717',
        '001U0000007PdGf' => '171234',
        '001U0000007PdFg' => '214111',
        '001U0000007PdHk' => '147411',
        '001U0000007PdGH' => '169275',
        '001U0000007PdFh' => '232788',
        '001U0000007PdH7' => '171304',
        '001U0000007PdFi' => '106980',
        '001U0000007PdFk' => '214379',
        '001U0000007PdFI' => '171395',
        '001U0000007PdFj' => '204422',
        '001U0000007PdGg' => '239488',
        '001U0000007PdFl' => '167376',
        '001U0000007PdHe' => '232946',
        '001U0000007PdGs' => '227191',
        '001U0000007PdH0' => '380377',
        '001U0000009RPQd' => '420398',
        '001U0000007PdFm' => '130004',
        '001U0000007PdHM' => '171535',
        '001U000000QfYvq' => '147800',
        '001U0000007PdH1' => '227304',
        '001U0000007PdFF' => '218487',
        '001U000000BBZOP' => '423652',
        '001U0000009RQ8r' => '246354',
        '001U0000007PdHp' => '227401',
        '001U0000007PdHf' => '186034',
        '001U0000007PdFo' => '233019',
        '001U000000A9PNE' => '233037',
        '001U0000007PdFp' => '107619',
        '001U0000007PdH2' => '117706',
        '001U00000091nFa' => '235237',
        '001U000000YkCqm' => '121363',
        '001U0000007PdH3' => '163657',
        '001U0000007PdFG' => '107664',
        '001U0000007PdHN' => '186645',
        '001U0000007PdFr' => '236382',
        '001U0000007PdHl' => '227766',
        '001U0000007PdFs' => '207670',
        '001U0000007PdFt' => '167631',
        '001U000000YMKJW' => '180647',
        '001U0000009RQ6X' => '227924',
        '001U0000007PdFu' => '227979',
        '001U0000007PdFw' => '236513',
        '001U0000007PdFx' => '205470',
        '001U0000007PdHO' => '236638',
        '001U000000VuCCK' => '368911',
        '001U000000QfYpy' => '141006',
        '001U0000007PdGF' => '409315',
        '001U000000BBXJk' => '210155',
        '001U0000007PdFy' => '228316',
        '001U0000007PdHP' => '236708',
        '001U0000007PdG0' => '167905',
        '001U0000007PdHg' => '172291',
        '001U0000007PdGh' => '179292',
        '001U0000008lCk0' => '137078',
        '001U0000009RKZQ' => '227854',
        '001U00000091nFb' => '199740',
        '001U0000007PdG1' => '236753',
        '001U0000007PdGC' => '137759',
        '001U0000007PdH4' => '228547',
        '001U0000007PdHm' => '228608',
        '001U0000007Pd5q' => '228699',
        '001U0000007PdGQ' => '229072',
        '001U0000007PdGk' => '434672',
        '001U0000007PdH8' => '999997',
        '001U000000BBZOo' => '420723',
        '001U000000BBXT9' => '210234',
        '001U0000007PdHR' => '218894',
        '001U0000007PdHn' => '149532',
        '001U0000007PdHC' => '207935',
        '001U0000007PdGt' => '229355',
        '001U000000BBaOJ' => '210270',
        '001U0000007PdGO' => '141839',
        '001U0000007PdG5' => '138187',
        '001U00000091nFc' => '101295',
        '001U000000VTI4H' => '236887',
        '001U0000007PdGi' => '172617',
        '001U0000007PdG6' => '172635',
        '001U0000007PdHi' => '125471',
        '001U0000007PdG7' => '216825',
        '001U0000007PdG8' => '229841',
        '001U0000007PdGj' => '237039',
        '001U0000007PdGP' => '141990',
        '001U0000007PdG9' => '237109',
        '001U0000007PdFH' => '204255',  
    );
}

function _ipeds_import_name_unitid_map() {
    return array(
     'Aiken Technical College' => '217615',
    'Albany Technical College' => '138682',
    'Amarillo College' => '222576',
    'Anne Arundel Community College' => '161767',
    'Arkansas Baptist College' => '106306',
    'Asheville-Buncombe Technical Community College' => '197887',
    'Athens Technical College' => '246813',
    'Atlanta Technical College' => '138840',
    'Atlantic Cape Community College' => '183655',
    'Augusta Technical College' => '138956',
    'Austin Community College District' => '222992',
    'Bakersfield College' => '109819',
    'Bay de Noc Community College' => '168883',
    'Bellingham Technical College' => '234696',
    'Bevill State Community College' => '102429',
    'Blue Mountain Community College' => '208275',
    'Brazosport College' => '223506',
    'Broward College' => '132709',
    'Bunker Hill Community College' => '165112',
    'Capital Community College' => '129367',
    'Central Alabama Community College' => '100760',
    'Central Georgia Technical College' => '140304',
    'Central Piedmont Community College' => '198260',
    'Century College' => '175315',
    'Cerro Coso Community College' => '111896',
    'Clover Park Technical College' => '234951',
    'Coastal Bend College' => '223320',
    'College of Southern Nevada' => '182005',
    'College of the Mainland' => '226408',
    'College of the Ouachitas' => '107521',
    'Columbia Gorge Community College' => '420556',
    'Columbus State Community College' => '202222',
    'Columbus Technical College' => '139357',
    'Community College of Allegheny County' => '210605',
    'Community College of Beaver County' => '211079',
    'Community College of Philadelphia' => '215239',
    'Community College of Vermont' => '230861',
    'Cumberland County College' => '184205',
    'Cuyahoga Community College' => '202356',
    'Danville Area Community College' => '144564',
    'Danville Community College' => '231882',
    'Davidson County Community College' => '198376',
    'Delaware County Community College' => '211927',
    'Delta College' => '169521',
    'Dine College' => '105297',
    'Doña Ana Community College' => '187620',
    'Durham Technical Community College' => '198455',
    'Eastern Gateway Community College' => '203331',
    'Eastern Maine Community College' => '161138',
    'East Los Angeles College' => '113856',
    'Edmonds Community College' => '235103',
    'El Centro College' => '224615',
    'Elgin Community College' => '144944',
    'El Paso Community College' => '224642',
    'Everett Community College' => '235149',
    'Galveston College' => '224961',
    'Gaston College' => '198570',
    'Georgia Piedmont Technical College' => '244446',
    'Glen Oaks Community College' => '169974',
    'Grand Rapids Community College' => '170055',
    'Grays Harbor College' => '235334',
    'Green River Community College' => '235343',
    'Greenville Technical College' => '218113',
    'Guilford Technical Community College' => '198622',
    'Gwinnett Technical College' => '140012',
    'Harper College' => '149842',
    'Hawai\'i Community College' => '383190',
    'Henry Ford Community College' => '170055',
    'Highline Community College' => '235431',
    'Hillsborough Community College' => '134495',
    'Honolulu Community College' => '141680',
    'Housatonic Community College' => '129543',
    'Houston Community College' => '225423',
    'Indian River State College' => '134608',
    'Ivy Tech Community College' => '440244',
    'Jackson Community College' => '170444',
    'Jefferson Community & Technical College' => '156921',
    'Kapi\'olani Community College' => '141796',
    'Kaua\'i Community College' => '141802',
    'Kilgore College' => '226019',
    'Kingsborough Community College' => '190619',
    'Klamath Community College' => '428392',
    'Lake Michigan College' => '170620',
    'Lane Community College' => '209038',
    'Lansing Community College' => '170657',
    'Lee College' => '226204',
    'Leeward Community College' => '141811',
    'Linn-Benton Community College' => '209074',
    'Lone Star College System' => '227182',
    'Lorain County Community College' => '203748',
    'Los Angeles City College' => '117788',
    'Los Angeles Harbor College' => '117690',
    'Los Angeles Mission College' => '117867',
    'Los Angeles Southwest College' => '117715',
    'Los Angeles Trade-Technical College' => '117724',
    'Los Angeles Valley College' => '117733',
    'Macomb Community College' => '170790',
    'Martin Community College' => '198905',
    'Miami Dade College' => '135717',
    'Montcalm Community College' => '171234',
    'Montgomery County Community College' => '214111',
    'Morton College' => '147411',
    'Mott Community College' => '169275',
    'Mountain Empire Community College' => '232788',
    'Muskegon Community College' => '171304',
    'National Park Community College' => '106980',
    'Northampton Community College' => '214379',
    'North Central Michigan College' => '171395',
    'North Central State College' => '204422',
    'Northeast Wisconsin Technical College' => '239488',
    'Northern Essex Community College' => '167376',
    'Northern Virginia Community College' => '232946',
    'North Lake College' => '227191',
    'Northwest Indian College' => '380377',
    'Northwest Vista College' => '420398',
    'Norwalk Community College' => '130004',
    'Oakland Community College' => '171535',
    'Oakton Community College' => '147800',
    'Odessa College' => '227304',
    'Orangeburg-Calhoun Technical College' => '218487',
    'Oregon Coast Community College' => '423652',
    'Palo Alto College' => '246354',
    'Paris Junior College' => '227401',
    'Passaic County Community College' => '186034',
    'Patrick Henry Community College' => '233019',
    'Paul D. Camp Community College' => '233037',
    'Phillips Community College of the University of Arkansas' => '107619',
    'Pierce College' => '117706',
    'Pierce College at Fort Steilacoom' => '235237',
    'Porterville College' => '121363',
    'Prince George\'s Community College' => '163657',
    'Pulaski Technical College' => '107664',
    'Raritan Valley Community College' => '186645',
    'Renton Technical College' => '236382',
    'Richland College' => '227766',
    'Rose State College' => '207670',
    'Roxbury Community College' => '167631',
    'Salish Kootenai College' => '180647',
    'San Antonio College' => '227924',
    'San Jacinto College' => '227979',
    'Seattle Central Community College' => '236513',
    'Sinclair Community College' => '205470',
    'Skagit Valley College' => '236638',
    'Southeastern Technical College' => '368911',
    'South Georgia Technical College' => '141006',
    'South Texas College' => '409315',
    'Southwestern Oregon Community College' => '210155',
    'Southwest Texas Junior College' => '228316',
    'Spokane Falls Community College' => '236708',
    'Springfield Technical Community College' => '167905',
    'St. Clair County Community College' => '172291',
    'St. Louis Community College' => '179292',
    'St. Petersburg College' => '137078',
    'St. Philip\'s College' => '227854',
    'Stanly Community College' => '199740',
    'Tacoma Community College' => '236753',
    'Tallahassee Community College' => '137759',
    'Tarrant County College' => '228547',
    'Temple College' => '228608',
    'Texarkana College' => '228699',
    'Texas Southmost College' => '229072',
    'The Community College of Baltimore County' => '434672',
    'The University of the District of Columbia Community College (UDC-CC)' => '999997',
    'Tillamook Bay Community College' => '420723',
    'Treasure Valley Community College' => '210234',
    'Trident Technical College' => '218894',
    'Triton College' => '149532',
    'Tulsa Community College' => '207935',
    'Tyler Junior College' => '229355',
    'Umpqua Community College' => '210270',
    'University of Hawai’i Maui College' => '141839',
    'Valencia College' => '138187',
    'Wallace State Community College - Hanceville' => '101295',
    'Walla Walla Community College' => '236887',
    'Washtenaw Community College' => '172617',
    'Wayne County Community College District' => '172635',
    'West Los Angeles College' => '125471',
    'Westmoreland County Community College' => '216825',
    'Wharton County Junior College' => '229841',
    'Whatcom Community College' => '237039',
    'Windward Community College' => '141990',
    'Yakima Valley Community College' => '237109',
    'Zane State College' => '204255',
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
        //$fieldname = 'field_' . $fieldname;

        /*if ($fieldname == 'field_ipeds_hbcu'
            || $fieldname == 'field_ipeds_tribal'
            )
            continue;
        */
        if (!array_key_exists('format', $data)) {
            $data['format'] = NULL;
        }
        
        if ( !property_exists($entity, $fieldname))
        {
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