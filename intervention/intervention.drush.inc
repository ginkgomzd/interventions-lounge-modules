<?php

/**
 * @file
 * Assigns an Intervention Family taxonomy term to any Intervention which
 * is not already assigned, via drush framework.
 */

define('INTERVENTION_FAM_TAX_ID', 10);

/**
 * Implementation of hook_drush_command().
 */
function intervention_drush_command() {
  $items['intervention-assign-family'] = array(
    'description' => 'Assigns an Intervention Family taxonomy term to any
      Intervention which is not already assigned.',
    'aliases' => array('iaf'),
  );

  $items['intervention-refresh-users'] = array(
    'description' => 'Update users associated with interventions from salesforce export',
    'aliases' => array('iru'),
  );

  return $items;
}

/**
 * Command callback
 */
function drush_intervention_assign_family() {
  $entitylist = _drush_intervention_get_all();

  $successes = 0;
  $failures = 0;
  foreach ($entitylist['node'] as $stub) {
    $node = node_load($stub->nid);

    // check for missing term reference field
    if (
      !property_exists($node, 'field_intervention_family') ||
      !is_array($node->field_intervention_family) ||
      !$node->field_intervention_family[LANGUAGE_NONE][0]['tid']
    ) {
      // create the term and assign it to the node
      if ($tid = _drush_intervention_create_taxonomy_term('Intervention Family ' . uniqid(), INTERVENTION_FAM_TAX_ID)) {
        $node->field_intervention_family[LANGUAGE_NONE][0]['tid'] = $tid;
        node_save($node);
        $successes++;
      } else {
        $failures++;
      }
    }
  }

  if ($successes > 0) {
    drush_log(t('Updated @number records.', array('@number' => $successes)), 'success');
  }

  if ($failures > 0) {
    drush_log(t('Term creation failed for @number records.', array('@number' => $failures)), 'warning');
  }
}

/**
 * Helper function
 *
 * EntityFieldQuery doesn't support search by IS NULL, so we'll just return
 * all Intervention nodes and do the IS NULL check iteratively elsewhere.
 */
function _drush_intervention_get_all() {
  $query = new EntityFieldQuery();

  $result = $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'intervention')
//    ->fieldCondition('field_intervention_family', 'tid', NULL)
    ->execute();

  return $result;
}

/**
 * Helper function
 *
 * Create a taxonomy term and return the tid.
 *
 * @param string $name Human-readable name to give the term
 * @param int $vid Vocabulary ID to which to add the term
 * @return mixed Boolean false on failure; integer term ID on success
 */
function _drush_intervention_create_taxonomy_term($name, $vid) {
  $result = FALSE;

  $term = new stdClass();
  $term->name = $name;
  $term->vid = $vid;
  taxonomy_term_save($term);

  if (property_exists($term, 'tid') && ctype_digit($term->tid)) {
    $result = $term->tid;
  }

  return $result;
}

/**
 * 
 *
 ***/
function drush_intervention_refresh_users() {

  $users = intervention_users_by_role('Core Team Lead');
  var_dump($users);
}

/**
 * Retrieve Users by role
 *
 * @param $role mixed The name or rid of the role we're wanting users to have
 * @param $active_user boolean Only return active accounts?
 *
 * @return array An array of user objects with the role
 * 
 * credit: http://drupal.stackexchange.com/a/53609
 */
function intervention_users_by_role($role, $active_user = TRUE) {
      $uids = array();
      $users = array();
      if (is_int($role)) {
        $my_rid = $role;
      }
      else {
        $role_obj = user_role_load_by_name($role);
      }
      $result = db_select('users_roles', 'ur')
        ->fields('ur')
        ->condition('ur.rid', $role_obj->rid, '=')
        ->execute();
      foreach ($result as $record) {
        $uids[] = $record->uid;
      };
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', 'user')
        ->propertyCondition('uid', $uids, 'IN');
      if ($active_user) {
        $query->propertyCondition('status', 1);
      }
      $entities = $query->execute();
      if (!empty($entities)) {
        $users = entity_load('user', array_keys($entities['user']));
      }
      return $users;
}

