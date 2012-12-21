<?php
/**
 * @file
 * college_profile.features.inc
 */

/**
 * Implements hook_node_info().
 */
function college_profile_node_info() {
  $items = array(
    'college_profile' => array(
      'name' => t('College Profile'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('College Name'),
      'help' => '',
    ),
  );
  return $items;
}
