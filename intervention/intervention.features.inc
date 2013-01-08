<?php
/**
 * @file
 * intervention.features.inc
 */

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
