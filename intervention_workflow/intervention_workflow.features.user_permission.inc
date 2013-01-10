<?php
/**
 * @file
 * intervention_workflow.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function intervention_workflow_user_default_permissions() {
  $permissions = array();

  // Exported permission: access content.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: access content overview.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      0 => 'ATD Staff Moderator',
      1 => 'administrator',
      2 => 'themer',
      3 => 'webmaster',
    ),
    'module' => 'node',
  );

  // Exported permission: administer workbench moderation.
  $permissions['administer workbench moderation'] = array(
    'name' => 'administer workbench moderation',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: bypass workbench moderation.
  $permissions['bypass workbench moderation'] = array(
    'name' => 'bypass workbench moderation',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: create college_profile content.
  $permissions['create college_profile content'] = array(
    'name' => 'create college_profile content',
    'roles' => array(
      0 => 'Core Team Lead',
      1 => 'administrator',
      2 => 'themer',
      3 => 'webmaster',
    ),
    'module' => 'node',
  );

  // Exported permission: create intervention content.
  $permissions['create intervention content'] = array(
    'name' => 'create intervention content',
    'roles' => array(
      0 => 'ATD Staff Moderator',
      1 => 'Core Team Lead',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any college_profile content.
  $permissions['delete any college_profile content'] = array(
    'name' => 'delete any college_profile content',
    'roles' => array(
      0 => 'administrator',
      1 => 'themer',
      2 => 'webmaster',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any intervention content.
  $permissions['delete any intervention content'] = array(
    'name' => 'delete any intervention content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: delete own college_profile content.
  $permissions['delete own college_profile content'] = array(
    'name' => 'delete own college_profile content',
    'roles' => array(
      0 => 'Core Team Lead',
      1 => 'administrator',
      2 => 'themer',
      3 => 'webmaster',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own intervention content.
  $permissions['delete own intervention content'] = array(
    'name' => 'delete own intervention content',
    'roles' => array(
      0 => 'ATD Staff Moderator',
      1 => 'Core Team Lead',
    ),
    'module' => 'node',
  );

  // Exported permission: delete revisions.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      0 => 'administrator',
      1 => 'themer',
      2 => 'webmaster',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any college_profile content.
  $permissions['edit any college_profile content'] = array(
    'name' => 'edit any college_profile content',
    'roles' => array(
      0 => 'administrator',
      1 => 'themer',
      2 => 'webmaster',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any intervention content.
  $permissions['edit any intervention content'] = array(
    'name' => 'edit any intervention content',
    'roles' => array(
      0 => 'ATD Staff Moderator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own college_profile content.
  $permissions['edit own college_profile content'] = array(
    'name' => 'edit own college_profile content',
    'roles' => array(
      0 => 'Core Team Lead',
      1 => 'administrator',
      2 => 'themer',
      3 => 'webmaster',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own intervention content.
  $permissions['edit own intervention content'] = array(
    'name' => 'edit own intervention content',
    'roles' => array(
      0 => 'Core Team Lead',
    ),
    'module' => 'node',
  );

  // Exported permission: moderate content from college_approved to published.
  $permissions['moderate content from college_approved to published'] = array(
    'name' => 'moderate content from college_approved to published',
    'roles' => array(
      0 => 'ATD Staff Moderator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: moderate content from draft to college_approved.
  $permissions['moderate content from draft to college_approved'] = array(
    'name' => 'moderate content from draft to college_approved',
    'roles' => array(
      0 => 'ATD Staff Moderator',
      1 => 'Core Team Lead',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: revert revisions.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      0 => 'ATD Staff Moderator',
      1 => 'Core Team Lead',
      2 => 'administrator',
      3 => 'themer',
      4 => 'webmaster',
    ),
    'module' => 'node',
  );

  // Exported permission: search college_profile content.
  $permissions['search college_profile content'] = array(
    'name' => 'search college_profile content',
    'roles' => array(
      0 => 'ATD Staff Moderator',
      1 => 'Core Team Lead',
      2 => 'administrator',
      3 => 'anonymous user',
      4 => 'authenticated user',
    ),
    'module' => 'search_config',
  );

  // Exported permission: search intervention content.
  $permissions['search intervention content'] = array(
    'name' => 'search intervention content',
    'roles' => array(
      0 => 'ATD Staff Moderator',
      1 => 'Core Team Lead',
    ),
    'module' => 'search_config',
  );

  // Exported permission: use workbench_moderation my drafts tab.
  $permissions['use workbench_moderation my drafts tab'] = array(
    'name' => 'use workbench_moderation my drafts tab',
    'roles' => array(
      0 => 'ATD Staff Moderator',
      1 => 'Core Team Lead',
      2 => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: use workbench_moderation needs review tab.
  $permissions['use workbench_moderation needs review tab'] = array(
    'name' => 'use workbench_moderation needs review tab',
    'roles' => array(
      0 => 'ATD Staff Moderator',
      1 => 'Core Team Lead',
      2 => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: view all unpublished content.
  $permissions['view all unpublished content'] = array(
    'name' => 'view all unpublished content',
    'roles' => array(
      0 => 'ATD Staff Moderator',
      1 => 'Core Team Lead',
      2 => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: view moderation history.
  $permissions['view moderation history'] = array(
    'name' => 'view moderation history',
    'roles' => array(
      0 => 'ATD Staff Moderator',
      1 => 'Core Team Lead',
      2 => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: view moderation messages.
  $permissions['view moderation messages'] = array(
    'name' => 'view moderation messages',
    'roles' => array(
      0 => 'ATD Staff Moderator',
      1 => 'Core Team Lead',
      2 => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: view own unpublished content.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      0 => 'ATD Staff Moderator',
      1 => 'Core Team Lead',
      2 => 'administrator',
      3 => 'expert',
      4 => 'themer',
      5 => 'webmaster',
    ),
    'module' => 'node',
  );

  // Exported permission: view revisions.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      0 => 'ATD Staff Moderator',
      1 => 'Core Team Lead',
      2 => 'administrator',
      3 => 'themer',
      4 => 'webmaster',
    ),
    'module' => 'node',
  );

  return $permissions;
}
