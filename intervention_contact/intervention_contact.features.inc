<?php
/**
 * @file
 * intervention_contact.features.inc
 */

/**
 * Implements hook_node_info().
 */
function intervention_contact_node_info() {
  $items = array(
    'intervention_contact' => array(
      'name' => t('Intervention Contact'),
      'base' => 'node_content',
      'description' => t('Contacts for intervention data'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
