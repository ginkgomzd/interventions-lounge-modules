<?php
/**
 * @file
 * intervention_workflow.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function intervention_workflow_user_default_roles() {
  $roles = array();

  // Exported role: ATD Staff Moderator.
  $roles['ATD Staff Moderator'] = array(
    'name' => 'ATD Staff Moderator',
    'weight' => '7',
  );

  // Exported role: Core Team Lead.
  $roles['Core Team Lead'] = array(
    'name' => 'Core Team Lead',
    'weight' => '6',
  );

  return $roles;
}
