<?php
/**
 * @file
 * intervention.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function intervention_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-intervention-body'
  $field_instances['node-intervention-body'] = array(
    'bundle' => 'intervention',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Please provide a description of the intervention that is one to two paragraphs long. Include relevant details about the target areas of improvement you are hoping to address through this intervention as well as key intervention elements and activities.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'semantic_field_format' => 0,
        ),
        'type' => 'text_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'semantic_field_format' => 0,
          'trim_length' => 300,
        ),
        'type' => 'text_summary_or_trimmed',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Description of Intervention',
    'required' => 1,
    'settings' => array(
      'display_summary' => 1,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 20,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'node-intervention-field_college_reference'
  $field_instances['node-intervention-field_college_reference'] = array(
    'bundle' => 'intervention',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'node_reference',
        'settings' => array(
          'semantic_field_format' => 0,
        ),
        'type' => 'node_reference_default',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'node_reference',
        'settings' => array(
          'semantic_field_format' => 0,
        ),
        'type' => 'node_reference_plain',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_college_reference',
    'label' => 'Name of Institution',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'node_reference',
      'settings' => array(
        'autocomplete_match' => 'contains',
        'autocomplete_path' => 'node_reference/autocomplete',
        'size' => 100,
      ),
      'type' => 'node_reference_autocomplete',
      'weight' => 17,
    ),
  );

  // Exported field_instance: 'node-intervention-field_contact'
  $field_instances['node-intervention-field_contact'] = array(
    'bundle' => 'intervention',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Person to contact regarding this intervention.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'node_reference',
        'settings' => array(
          'node_reference_view_mode' => 'full',
          'semantic_field_format' => 0,
        ),
        'type' => 'node_reference_node',
        'weight' => 14,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 16,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_contact',
    'label' => 'Contact',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'node_reference',
      'settings' => array(
        'autocomplete_match' => 'contains',
        'autocomplete_path' => 'node_reference/autocomplete',
        'size' => 60,
      ),
      'type' => 'node_reference_autocomplete',
      'weight' => 18,
    ),
  );

  // Exported field_instance: 'node-intervention-field_content_area'
  $field_instances['node-intervention-field_content_area'] = array(
    'bundle' => 'intervention',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'If the intervention is to be implemented within a specific discipline, choose all that apply from the following list [ctrl+click to select multiple].',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(
          'semantic_field_format' => 0,
        ),
        'type' => 'list_default',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(
          'semantic_field_format' => 0,
        ),
        'type' => 'list_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_content_area',
    'label' => 'Content Area',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-intervention-field_identify_the_key_target_po'
  $field_instances['node-intervention-field_identify_the_key_target_po'] = array(
    'bundle' => 'intervention',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Example: male students of color, part-time students, faculty, etc.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(
          'semantic_field_format' => 0,
        ),
        'type' => 'text_default',
        'weight' => 21,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_identify_the_key_target_po',
    'label' => 'Identify the key target population served by this intervention',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 14,
    ),
  );

  // Exported field_instance: 'node-intervention-field_intervention_family'
  $field_instances['node-intervention-field_intervention_family'] = array(
    'bundle' => 'intervention',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 20,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_intervention_family',
    'label' => 'Intervention Family',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 22,
    ),
  );

  // Exported field_instance: 'node-intervention-field_intervention_status'
  $field_instances['node-intervention-field_intervention_status'] = array(
    'bundle' => 'intervention',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'Indicate whether the intervention is already in place at your institution (active), if implementation has yet to begin (planned), or if the intervention was in place but is no longer in place (discontinued).',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(
          'semantic_field_format' => 0,
        ),
        'type' => 'list_default',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 12,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_intervention_status',
    'label' => 'Intervention Status',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-intervention-field_intervention_type'
  $field_instances['node-intervention-field_intervention_type'] = array(
    'bundle' => 'intervention',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Choose all that apply from the following list [ctrl+click to select multiple].',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(
          'semantic_field_format' => 0,
        ),
        'type' => 'list_default',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(
          'semantic_field_format' => 0,
        ),
        'type' => 'list_default',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_intervention_type',
    'label' => 'Intervention Type',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-intervention-field_legacy_id'
  $field_instances['node-intervention-field_legacy_id'] = array(
    'bundle' => 'intervention',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Import ID',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'semantic_field_format' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 15,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 13,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_legacy_id',
    'label' => 'Legacy ID',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 19,
    ),
  );

  // Exported field_instance: 'node-intervention-field_outcome_indicators'
  $field_instances['node-intervention-field_outcome_indicators'] = array(
    'bundle' => 'intervention',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Indicate which of the five Achieving the Dream outcome indicators the intervention addresses [ctrl+click to select multiple].',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(
          'semantic_field_format' => 0,
        ),
        'type' => 'list_default',
        'weight' => 12,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 14,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_outcome_indicators',
    'label' => 'Target ATD Student Success Indicator',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 16,
    ),
  );

  // Exported field_instance: 'node-intervention-field_promising_practice'
  $field_instances['node-intervention-field_promising_practice'] = array(
    'bundle' => 'intervention',
    'default_value' => array(
      0 => array(
        'value' => 'No',
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 19,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 15,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_promising_practice',
    'label' => 'Promising Practice',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 12,
    ),
  );

  // Exported field_instance: 'node-intervention-field_proportion_served'
  $field_instances['node-intervention-field_proportion_served'] = array(
    'bundle' => 'intervention',
    'default_value' => array(
      0 => array(
        'value' => 'NA',
      ),
    ),
    'deleted' => 0,
    'description' => '<p>The proportion of the key target population that was served by this intervention in this reporting year. Use the following designations to classify the proportion:</p><ul><li>Some: serving 25% or less of the target student population.</li><li>More: serving 25.1% to 60% of the target student population.</li><li>Most: serving more than 60% of the target student population.</li></ul>',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(
          'semantic_field_format' => 0,
        ),
        'type' => 'list_default',
        'weight' => 11,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 11,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_proportion_served',
    'label' => 'Proportion of Key Target Population Served',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 15,
    ),
  );

  // Exported field_instance: 'node-intervention-field_reporting_year'
  $field_instances['node-intervention-field_reporting_year'] = array(
    'bundle' => 'intervention',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'semantic_field_format' => 0,
          'show_repeat_rule' => 'show',
        ),
        'type' => 'date_default',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 10,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_reporting_year',
    'label' => 'Reporting Year',
    'required' => 1,
    'settings' => array(
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'display_all_day' => 0,
        'increment' => 15,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'repeat_collapsed' => 0,
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_select',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-intervention-field_start_year'
  $field_instances['node-intervention-field_start_year'] = array(
    'bundle' => 'intervention',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The academic year in which the intervention began or is planned to begin. Format: YYYY-YYYY.',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(
          'semantic_field_format' => 0,
        ),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_start_year',
    'label' => 'Start Academic Year',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 10,
      ),
      'type' => 'text_textfield',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-intervention-field_target_ethnicity'
  $field_instances['node-intervention-field_target_ethnicity'] = array(
    'bundle' => 'intervention',
    'default_value' => array(
      0 => array(
        'value' => 'All',
      ),
    ),
    'deleted' => 0,
    'description' => 'Indicate an ethnicity focus in the target populations, if applicable.',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(
          'semantic_field_format' => 0,
        ),
        'type' => 'list_default',
        'weight' => 10,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_target_ethnicity',
    'label' => 'Target Ethnicity',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'node-intervention-field_target_gender'
  $field_instances['node-intervention-field_target_gender'] = array(
    'bundle' => 'intervention',
    'default_value' => array(
      0 => array(
        'value' => 'All',
      ),
    ),
    'deleted' => 0,
    'description' => 'Indicate a gender focus in the target populations, if applicable.',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(
          'semantic_field_format' => 0,
        ),
        'type' => 'list_default',
        'weight' => 8,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 7,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_target_gender',
    'label' => 'Target Gender',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-intervention-field_target_population'
  $field_instances['node-intervention-field_target_population'] = array(
    'bundle' => 'intervention',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Choose all that apply from the following list [ctrl+click to select multiple].',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(
          'semantic_field_format' => 0,
        ),
        'type' => 'list_default',
        'weight' => 7,
      ),
      'teaser' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(
          'semantic_field_format' => 0,
        ),
        'type' => 'list_default',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_target_population',
    'label' => 'Target Populations',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-intervention-field_target_race'
  $field_instances['node-intervention-field_target_race'] = array(
    'bundle' => 'intervention',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'Indicate a race focus in the target populations, if applicable.',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(
          'semantic_field_format' => 0,
        ),
        'type' => 'list_default',
        'weight' => 9,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 8,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_target_race',
    'label' => 'Target Race',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'node-intervention-field_why_promising'
  $field_instances['node-intervention-field_why_promising'] = array(
    'bundle' => 'intervention',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(
          'semantic_field_format' => 0,
        ),
        'type' => 'text_default',
        'weight' => 13,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 9,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_why_promising',
    'label' => 'Why This Intervention Demonstrates Promise',
    'required' => 0,
    'settings' => array(
      'display_summary' => 0,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 20,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => 13,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('<p>The proportion of the key target population that was served by this intervention in this reporting year. Use the following designations to classify the proportion:</p><ul><li>Some: serving 25% or less of the target student population.</li><li>More: serving 25.1% to 60% of the target student population.</li><li>Most: serving more than 60% of the target student population.</li></ul>');
  t('Choose all that apply from the following list [ctrl+click to select multiple].');
  t('Contact');
  t('Content Area');
  t('Description of Intervention');
  t('Example: male students of color, part-time students, faculty, etc.');
  t('Identify the key target population served by this intervention');
  t('If the intervention is to be implemented within a specific discipline, choose all that apply from the following list [ctrl+click to select multiple].');
  t('Import ID');
  t('Indicate a gender focus in the target populations, if applicable.');
  t('Indicate a race focus in the target populations, if applicable.');
  t('Indicate an ethnicity focus in the target populations, if applicable.');
  t('Indicate whether the intervention is already in place at your institution (active), if implementation has yet to begin (planned), or if the intervention was in place but is no longer in place (discontinued).');
  t('Indicate which of the five Achieving the Dream outcome indicators the intervention addresses [ctrl+click to select multiple].');
  t('Intervention Family');
  t('Intervention Status');
  t('Intervention Type');
  t('Legacy ID');
  t('Name of Institution');
  t('Person to contact regarding this intervention.');
  t('Please provide a description of the intervention that is one to two paragraphs long. Include relevant details about the target areas of improvement you are hoping to address through this intervention as well as key intervention elements and activities.');
  t('Promising Practice');
  t('Proportion of Key Target Population Served');
  t('Reporting Year');
  t('Start Academic Year');
  t('Target ATD Student Success Indicator');
  t('Target Ethnicity');
  t('Target Gender');
  t('Target Populations');
  t('Target Race');
  t('The academic year in which the intervention began or is planned to begin. Format: YYYY-YYYY.');
  t('Why This Intervention Demonstrates Promise');

  return $field_instances;
}
