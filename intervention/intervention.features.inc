<?php
/**
 * @file
 * intervention.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function intervention_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_validation" && $api == "default_field_validation_rules") {
    return array("version" => "2");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function intervention_node_info() {
  $items = array(
    'intervention' => array(
      'name' => t('Intervention'),
      'base' => 'node_content',
      'description' => t('Intervention'),
      'has_title' => '1',
      'title_label' => t('Intervention Name'),
      'help' => '',
    ),
  );
  return $items;
}
