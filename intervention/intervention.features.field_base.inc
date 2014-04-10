<?php
/**
 * @file
 * intervention.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function intervention_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'body'
  $field_bases['body'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'body',
    'field_permissions' => array(
      'type' => 0,
    ),
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'views_base_columns' => array(),
      'views_base_table' => 0,
    ),
    'translatable' => 0,
    'type' => 'text_with_summary',
  );

  // Exported field_base: 'field_college_reference'
  $field_bases['field_college_reference'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_college_reference',
    'field_permissions' => array(
      'type' => 2,
    ),
    'foreign keys' => array(
      'nid' => array(
        'columns' => array(
          'nid' => 'nid',
        ),
        'table' => 'node',
      ),
    ),
    'indexes' => array(
      'nid' => array(
        0 => 'nid',
      ),
    ),
    'locked' => 0,
    'module' => 'node_reference',
    'settings' => array(
      'referenceable_types' => array(
        'article' => 0,
        'atd_newsletter' => 0,
        'brag_bar_item' => 0,
        'coach_resource' => 0,
        'college_profile' => 'college_profile',
        'college_profile_salesforce' => 0,
        'event' => 0,
        'faq' => 0,
        'group' => 0,
        'hidden_page' => 0,
        'intervention' => 0,
        'intervention_contact' => 0,
        'news' => 0,
        'newsletter_component' => 0,
        'organization' => 0,
        'page' => 0,
        'panel' => 0,
        'person' => 0,
        'press_release' => 0,
        'resource' => 0,
        'slideshow_image' => 0,
        'state_policy_team' => 0,
      ),
      'view' => array(
        'args' => array(),
        'display_name' => '',
        'view_name' => '',
      ),
      'views_base_columns' => array(),
      'views_base_table' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'node_reference',
  );

  // Exported field_base: 'field_contact'
  $field_bases['field_contact'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_contact',
    'field_permissions' => array(
      'type' => 2,
    ),
    'foreign keys' => array(
      'nid' => array(
        'columns' => array(
          'nid' => 'nid',
        ),
        'table' => 'node',
      ),
    ),
    'indexes' => array(
      'nid' => array(
        0 => 'nid',
      ),
    ),
    'locked' => 0,
    'module' => 'node_reference',
    'settings' => array(
      'referenceable_types' => array(
        'article' => 0,
        'atd_newsletter' => 0,
        'brag_bar_item' => 0,
        'college_profile' => 0,
        'college_profile_salesforce' => 0,
        'faq' => 0,
        'group' => 0,
        'hidden_page' => 0,
        'intervention' => 0,
        'intervention_contact' => 'intervention_contact',
        'news' => 0,
        'newsletter_component' => 0,
        'organization' => 0,
        'page' => 0,
        'panel' => 0,
        'person' => 0,
        'press_release' => 0,
        'resource' => 0,
        'slideshow_image' => 0,
        'state_policy_team' => 0,
      ),
      'view' => array(
        'args' => array(),
        'display_name' => '',
        'view_name' => '',
      ),
      'views_base_columns' => array(),
      'views_base_table' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'node_reference',
  );

  // Exported field_base: 'field_content_area'
  $field_bases['field_content_area'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_content_area',
    'field_permissions' => array(
      'type' => 0,
    ),
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => 'Arts',
        1 => 'Business',
        2 => 'Communications',
        3 => 'Computer Science',
        4 => 'English',
        5 => 'Humanities',
        6 => 'Math',
        10 => 'n/a',
        7 => 'Reading',
        8 => 'Science',
        11 => 'Social Sciences',
        9 => 'Student Success',
      ),
      'allowed_values_function' => '',
      'views_base_columns' => array(),
      'views_base_table' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_identify_the_key_target_po'
  $field_bases['field_identify_the_key_target_po'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_identify_the_key_target_po',
    'field_permissions' => array(
      'type' => 0,
    ),
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
      'views_base_columns' => array(),
      'views_base_table' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_intervention_family'
  $field_bases['field_intervention_family'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_intervention_family',
    'field_permissions' => array(
      'type' => 2,
    ),
    'foreign keys' => array(
      'tid' => array(
        'columns' => array(
          'tid' => 'tid',
        ),
        'table' => 'taxonomy_term_data',
      ),
    ),
    'indexes' => array(
      'tid' => array(
        0 => 'tid',
      ),
    ),
    'locked' => 0,
    'module' => 'taxonomy',
    'settings' => array(
      'allowed_values' => array(
        0 => array(
          'vocabulary' => 'interventions',
          'parent' => 0,
        ),
      ),
      'views_base_columns' => array(),
      'views_base_table' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'taxonomy_term_reference',
  );

  // Exported field_base: 'field_intervention_status'
  $field_bases['field_intervention_status'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_intervention_status',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => 'Active',
        1 => 'Planned',
        2 => 'Discontinued',
      ),
      'allowed_values_function' => '',
      'views_base_columns' => array(),
      'views_base_table' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_intervention_type'
  $field_bases['field_intervention_type'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_intervention_type',
    'field_permissions' => array(
      'type' => 0,
    ),
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        1 => 'Advising',
        2 => 'Board of Trustees',
        3 => 'Budgeting Process',
        4 => 'Committee or Governance Structure',
        5 => 'Community Engagement',
        6 => 'Course Redesign',
        32 => 'Curriculum Redesign',
        7 => 'Developmental Education',
        8 => 'Dual Enrolled',
        33 => 'Early Alert',
        9 => 'Equity',
        24 => 'Faculty and Staff Engagement',
        11 => 'First-Year Experience',
        12 => 'Gateway Courses',
        13 => 'Improved Use of Data',
        14 => 'Information Systems',
        15 => 'Institutional Effectiveness',
        16 => 'Institutional Research',
        17 => 'Internal Policy Review & Revision',
        18 => 'K-14 Strategies',
        19 => 'Learning Communities',
        20 => 'Mentoring',
        21 => 'Orientation',
        29 => 'Placement Process',
        22 => 'Policy Change',
        10 => 'Professional Development',
        23 => 'Program Evaluation',
        25 => 'Student Engagement',
        26 => 'Student Success Course',
        27 => 'Student Support Services',
        34 => 'Summer Bridge',
        28 => 'Supplemental Instruction',
        35 => 'Technology',
        30 => 'Tutoring',
        31 => 'Other',
      ),
      'allowed_values_function' => '',
      'views_base_columns' => array(),
      'views_base_table' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_legacy_id'
  $field_bases['field_legacy_id'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_legacy_id',
    'field_permissions' => array(
      'type' => 2,
    ),
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(
      'views_base_columns' => array(),
      'views_base_table' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'number_integer',
  );

  // Exported field_base: 'field_outcome_indicators'
  $field_bases['field_outcome_indicators'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_outcome_indicators',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => 'Complete the courses they take with a grade of "C" or better',
        1 => 'Earn a certificate or associate degree',
        2 => 'Enroll in and successfully complete the initial college-level or gateway courses in subjects such as Math and English',
        3 => 'Persistence from one term to the next',
        4 => 'Successfully complete remedial or developmental instruction',
      ),
      'allowed_values_function' => '',
      'views_base_columns' => array(),
      'views_base_table' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_promising_practice'
  $field_bases['field_promising_practice'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_promising_practice',
    'field_permissions' => array(
      'type' => 2,
    ),
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'Yes' => 'Yes',
        'No' => 'No',
      ),
      'allowed_values_function' => '',
      'views_base_columns' => array(),
      'views_base_table' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_proportion_served'
  $field_bases['field_proportion_served'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_proportion_served',
    'field_permissions' => array(
      'type' => 0,
    ),
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'Some' => 'Some (25% or less)',
        'More' => 'More (25.1% to 60%)',
        'Most' => 'Most (more than 60%)',
        'NA' => 'Not Available',
      ),
      'allowed_values_function' => '',
      'views_base_columns' => array(),
      'views_base_table' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_reporting_year'
  $field_bases['field_reporting_year'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_reporting_year',
    'field_permissions' => array(
      'type' => 2,
    ),
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'date',
    'settings' => array(
      'cache_count' => 4,
      'cache_enabled' => 0,
      'granularity' => array(
        'day' => 0,
        'hour' => 0,
        'minute' => 0,
        'month' => 0,
        'second' => 0,
        'year' => 'year',
      ),
      'repeat' => 0,
      'timezone_db' => '',
      'todate' => '',
      'tz_handling' => 'none',
      'views_base_columns' => array(),
      'views_base_table' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'datetime',
  );

  // Exported field_base: 'field_start_year'
  $field_bases['field_start_year'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_start_year',
    'field_permissions' => array(
      'type' => 0,
    ),
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 9,
      'views_base_columns' => array(),
      'views_base_table' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_target_ethnicity'
  $field_bases['field_target_ethnicity'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_target_ethnicity',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'All' => 'All',
        'Latino' => 'Hispanic or Latin@',
        'NonLatino' => 'Not Hispanic or Latin@',
      ),
      'allowed_values_function' => '',
      'views_base_columns' => array(),
      'views_base_table' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_target_gender'
  $field_bases['field_target_gender'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_target_gender',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'Males' => 'Males only',
        'Females' => 'Females only',
        'All' => 'All',
      ),
      'allowed_values_function' => '',
      'views_base_columns' => array(),
      'views_base_table' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_target_population'
  $field_bases['field_target_population'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_target_population',
    'field_permissions' => array(
      'type' => 0,
    ),
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => 'All Students',
        1 => 'Academically Underprepared Students',
        12 => 'Career and Technical Ed Students',
        2 => 'ESL-ESOL-ELL',
        3 => 'Enrollment: Full Time Students',
        4 => 'Enrollment: Part Time Students',
        5 => 'Faculty and Staff',
        13 => 'Financial Aid Recipients',
        7 => 'First Generation Students',
        8 => 'First time in any college',
        15 => 'First time in this college',
        9 => 'High School Students',
        6 => 'Pell-eligible/Low-income Students',
        14 => 'Transfer Track Students',
        11 => 'Veterans/Active Military',
        10 => 'Other',
      ),
      'allowed_values_function' => '',
      'views_base_columns' => array(),
      'views_base_table' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_target_race'
  $field_bases['field_target_race'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_target_race',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => 'All Races',
        1 => 'American Indian or Alaska Native',
        5 => 'Asian',
        2 => 'Black or African American',
        6 => 'Native Hawaiian or Other Pacific Islander',
        7 => 'White',
        4 => 'Other',
      ),
      'allowed_values_function' => '',
      'views_base_columns' => array(),
      'views_base_table' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_why_promising'
  $field_bases['field_why_promising'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_why_promising',
    'field_permissions' => array(
      'type' => 2,
    ),
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'views_base_columns' => array(),
      'views_base_table' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'text_with_summary',
  );

  return $field_bases;
}
