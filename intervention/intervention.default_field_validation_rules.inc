<?php
/**
 * @file
 * intervention.default_field_validation_rules.inc
 */

/**
 * Implements hook_default_field_validation_rule().
 */
function intervention_default_field_validation_rule() {
  $export = array();

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'School Year';
  $rule->name = 'school_year';
  $rule->field_name = 'field_start_year';
  $rule->col = 'value';
  $rule->entity_type = 'node';
  $rule->bundle = 'intervention';
  $rule->validator = 'field_validation_pattern_validator';
  $rule->settings = array(
    'pattern' => '9999-9999',
    'bypass' => 0,
    'roles' => array(
      2 => 0,
      3 => 0,
      4 => 0,
      5 => 0,
      6 => 0,
      8 => 0,
      7 => 0,
    ),
    'errors' => 0,
  );
  $rule->error_message = 'Enter school year with 4-digit years.';
  $export['school_year'] = $rule;

  return $export;
}
