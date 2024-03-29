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

  $items['intervention-normalize-target-population'] = array(
    'description' => 'Updates interventions to ensure that no other choices are selected when Target-All has been selected.',
    'aliases' => array('intv-norm-targ', 'int'),
  );

  $items['intervention-update-core-team-leads'] = array (
    'callback' => 'intervention_drush_update_core_team_leads',
    'description' => 'Updates interventions contact-info from a file',
    'aliases' => array('ctl-up'),
    'options' => array(
      'csv' => 'CSV of Unit-ID Identified IPEDS data',
      ),
    'examples' => array(
      'drush ipeds-up --csv=sites/default/files/ipeds_data.csv',
    ),
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

/***
 * Block users in the Core Team Lead Role
 * PIO and Webmaster Roles excepted
 ***/ 
function intervention_block_core_team_leads() {

  $role_core_team_lead = user_role_load_by_name('Core Team Lead');
  $role_pio = user_role_load_by_name('PIO');
  $role_webmaster = user_role_load_by_name('Webmaster');

  $ctl_users = intervention_get_users_in_role($role_core_team_lead);
  $pios_users = intervention_get_users_in_role($role_pio);
  $webmaster_users = intervention_get_users_in_role($role_webmaster);

  # exclude PIO and webmasters from being blocked:
  $users = array_diff($ctl_users, $pios_users, $webmaster_users);

  user_user_operations_block($users);

}

/***
 * Get an array of user ID's in a role
 * 
 * @param $role Role Object, e.g. user_role_load_by_name($role)
 * 
 * @return array an Array of user id's
 ***/
function intervention_get_users_in_role($role) {

  $result = db_select('users_roles', 'ur')
      ->fields('ur')
      ->condition('ur.rid', $role->rid, '=')
      ->execute();
  foreach ($result as $record) {
        $uids[] = $record->uid;
  };

  return $uids;
}

/***
 * Callback for drush command, intervention-normalize-target-population
 *
 *
 ***/
function drush_intervention_normalize_target_population() {

  #get the key stored in the field_data table:
  $field_info = field_info_instance('node', 'field_target_population', 'intervention');
  $field_info = field_info_field('field_target_population');
  $all_students_value = array_search('All Students', $field_info['settings']['allowed_values']);

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->propertyCondition('type', 'intervention')
    ->fieldCondition('field_target_population', 'value', array($all_students_value), 'IN')
  ;

  $result = $query->execute();
  if (!isset($result['node'])) die('No Target-Population-All nodes found');

  $interventions = entity_load('node', array_keys($result['node']));
  foreach( $interventions as $intv ) {
    #set target population to only "All Students"
    $intv->field_target_population['und'] = array(array('value' => '0'));
    node_save($intv);
  }
}

/***
 * Callback for drush command, 
 * update core team lead contact info
 ***/
function intervention_drush_update_core_team_leads() {
  echo 'intervention-drush_update_core_team_leads';
  watchdog('intervention_drush', 'running update_core_team_leads');
  $csv_file = drush_get_option('csv');

  if (!is_file($csv_file)) {
    watchdog('intervention_drush', "invalid csv file", null, WATCHDOG_ERROR);
  }
  $contacts = _intervention_parse_csv($csv_file);

  #block users:
  intervention_block_core_team_leads();

  watchdog('intervention_drush', 'loading role, "core team lead"');
  $role_core_team_lead = user_role_load_by_name('Core Team Lead');

  foreach ($contacts as $contact) {

    $unitid = $contact['UNITID'];
    $name = $contact['Contact Full Name'];
    $title = $contact['Title'];
    $mail = $contact['Email'];
    $phone = $contact['Phone'];

    if ($mail == '') continue;

    $account = user_load_by_mail($mail);
//watchdog('drush_interventionsMZD', '%account', array('%account' => var_export($account, true))); continue;

    if ($account === false) {
      watchdog('drush_interventions', 'user load by mail failed for %mail', array('%mail' => $mail));
      $new_user = new StdClass();
      $new_user->mail = $mail;
      $new_user->name = $mail;
      $new_user->is_new = true;
      $account = user_save($new_user);
watchdog('drush_interventions', 'user_save new user result: %account', array('%account'=> var_export($account, true)));
    }

    $account->roles[$role_core_team_lead->rid] = $role_core_team_lead->name;
    $account = user_save($account, array('name'=>$mail, 'mail'=>$mail));
watchdog('drush interventions', 'account->uid: %uid', array('%uid' => $account->uid));
    user_user_operations_unblock(array($account->uid));

    $interventions = _intervention_get_interventions($unitid);
    if (!is_array($interventions) ) {
      watchdog('drush_interventions', 'drush_update_core_team_leads failed to retrieve interventions for unitid: %unitid', array('%unitid'=>$unitid));
      continue;
    } else {
      watchdog('drush_interventions', 'updating interventions for unitid: %unitid', array('%unitid'=>$unitid));
    }

    $field_contact_nid = 0;
    foreach ($interventions as $intervention) {
      if ($field_contact_nid != $intervention->field_contact[LANGUAGE_NONE][0]['nid']) {
        $field_contact_nid = $intervention->field_contact[LANGUAGE_NONE][0]['nid'];
        _intervention_update_intervention_contact($field_contact_nid, array('name'=>$name, 'title'=>$title, 'email'=>$mail, 'phone'=>$phone, 'uid'=>$account->uid));
      }
      //ensure intervention uid
      $intervention->uid = $account->uid;
      node_save($intervention);
    }
  }
  watchdog('drush_intervention', 'core team lead update complete');
}

/***
 * Utility to update an Intervention Contact
 ***/
function _intervention_update_intervention_contact($field_contact_nid, $data = array('name' => null, 'title' => null, 'email' => null, 'phone' => null) ) {
  $contact = node_load($field_contact_nid);

  $contact->name = $data['name'];
  $contact->title = $contact->name;
  $contact->field_email[LANGUAGE_NONE][0]['email'] = $data['email'];
  $contact->field_job_title[LANGUAGE_NONE][0]['value'] = $data['title'];
  $contact->field_contact_phone[LANGUAGE_NONE][0]['value'] = $data['phone'];
  $contact->uid = $data['uid'];

  return node_save($contact);
}

/***
 * returns an array of associative arrays
 * first line of file is used for row-keys
 **/
function _intervention_parse_csv($filepath, $DELIM = '|', $QUAL = '"' ) {
    $fd = fopen($filepath, "r");

    $file_arr = array();
    $line = fgets($fd);
    $keys_arr = str_getcsv($line, $DELIM, $QUAL);
    while (!feof($fd)) {
        $line = fgets($fd);

         if ( count($keys_arr)!= count(str_getcsv($line, $DELIM, $QUAL)) ) {
              continue;
          }
          $file_arr[] = array_combine($keys_arr, str_getcsv($line, $DELIM, $QUAL));
    }
    fclose($fd);

    return $file_arr;
}

/***
 * Get interventions for a Given IPEDS UNITID
 ***/
function _intervention_get_interventions($UNITID) {
  if (empty($UNITID)) return null;
  $query = new EntityFieldQuery();

  $result = $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'college_profile')
    ->fieldCondition('field_ipeds_unitid', 'value', $UNITID, '=')
    ->execute();

  if (empty($result['node'])) { watchdog('drush_interventions', 'warning, get_interventions failed to load college_profile for %unitid', array('%unitid'=>$UNITID)); return null; }
  if (count($result) > 1) watchdog('drush_interventions', 'warning, get_interventions found multiple colleges for ipeds_unitid, %unitid', array('%unitid'=>$UNITID), WATHDOG_WARNING);

  $query = new EntityFieldQuery();
  $college = array_keys($result['node']);
  $college_nid = $college[0];

  $interventions = $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'intervention')
    ->fieldCondition('field_college_reference', 'nid', $college_nid, '=')
    ->execute(); 

  if (count($interventions) < 1) return;

  return entity_load('node', array_keys($interventions['node']));
}

