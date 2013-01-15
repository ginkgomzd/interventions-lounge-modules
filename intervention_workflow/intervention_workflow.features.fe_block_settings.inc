<?php
/**
 * @file
 * intervention_workflow.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function intervention_workflow_default_fe_block_settings() {
  $export = array();

  $export['version'] = '1.0';

  // Theme independent visibility settings.
  $export['visibility'] = array(
    'block-interventions_directions' => array(
      'machine_name' => 'interventions_directions',
      'module' => 'block',
    ),
    'block-interventions_moderator' => array(
      'machine_name' => 'interventions_moderator',
      'module' => 'block',
    ),
    'block-my_interventions' => array(
      'machine_name' => 'my_interventions',
      'module' => 'block',
    ),
  );

  // ATD
  $theme = array();

  $theme['block-interventions_moderator'] = array(
    'module' => 'block',
    'theme' => 'ATD',
    'status' => '1',
    'weight' => '-26',
    'region' => 'sidebar_second',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Interventions Moderator',
    'cache' => -1,
    'machine_name' => 'interventions_moderator',
  );

  $theme['block-my_interventions'] = array(
    'module' => 'block',
    'theme' => 'ATD',
    'status' => '1',
    'weight' => '-25',
    'region' => 'sidebar_second',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'My Interventions',
    'cache' => -1,
    'machine_name' => 'my_interventions',
  );

  $theme['block-interventions_directions'] = array(
    'module' => 'block',
    'theme' => 'ATD',
    'status' => '1',
    'weight' => '-24',
    'region' => 'sidebar_second',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Directions',
    'cache' => -1,
    'machine_name' => 'interventions_directions',
  );

  $export['theme']['ATD'] = $theme;

  // bartik
  $theme = array();

  $theme['block-interventions_moderator'] = array(
    'module' => 'block',
    'theme' => 'bartik',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Interventions Moderator',
    'cache' => -1,
    'machine_name' => 'interventions_moderator',
  );

  $theme['block-my_interventions'] = array(
    'module' => 'block',
    'theme' => 'bartik',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'My Interventions',
    'cache' => -1,
    'machine_name' => 'my_interventions',
  );

  $theme['block-interventions_directions'] = array(
    'module' => 'block',
    'theme' => 'bartik',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Directions',
    'cache' => -1,
    'machine_name' => 'interventions_directions',
  );

  $export['theme']['bartik'] = $theme;

  // seven
  $theme = array();

  $theme['block-interventions_moderator'] = array(
    'module' => 'block',
    'theme' => 'seven',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Interventions Moderator',
    'cache' => -1,
    'machine_name' => 'interventions_moderator',
  );

  $theme['block-my_interventions'] = array(
    'module' => 'block',
    'theme' => 'seven',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'My Interventions',
    'cache' => -1,
    'machine_name' => 'my_interventions',
  );

  $theme['block-interventions_directions'] = array(
    'module' => 'block',
    'theme' => 'seven',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Directions',
    'cache' => -1,
    'machine_name' => 'interventions_directions',
  );

  $export['theme']['seven'] = $theme;

  // zen
  $theme = array();

  $theme['block-interventions_moderator'] = array(
    'module' => 'block',
    'theme' => 'zen',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Interventions Moderator',
    'cache' => -1,
    'machine_name' => 'interventions_moderator',
  );

  $theme['block-my_interventions'] = array(
    'module' => 'block',
    'theme' => 'zen',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'My Interventions',
    'cache' => -1,
    'machine_name' => 'my_interventions',
  );

  $theme['block-interventions_directions'] = array(
    'module' => 'block',
    'theme' => 'zen',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Directions',
    'cache' => -1,
    'machine_name' => 'interventions_directions',
  );

  $export['theme']['zen'] = $theme;

  $theme_default = variable_get('theme_default', 'garland');
  $themes = list_themes();
  foreach ($export as $theme_key => $settings) {
    if ($theme_key != $theme_default && empty($themes[$theme_key]->status)) {
      unset($export['theme'][$theme_key]);
    }
  }
  return $export;
}
