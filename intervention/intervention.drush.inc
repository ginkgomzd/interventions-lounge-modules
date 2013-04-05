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