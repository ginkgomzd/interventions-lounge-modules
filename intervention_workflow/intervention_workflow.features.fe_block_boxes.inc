<?php
/**
 * @file
 * intervention_workflow.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function intervention_workflow_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Interventions Directions';
  $fe_block_boxes->format = 'filtered_html';
  $fe_block_boxes->machine_name = 'interventions_directions';
  $fe_block_boxes->body = '<p>Instructions overview will go here.</p>';

  $export['interventions_directions'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Interventions for ATD Staff Moderator';
  $fe_block_boxes->format = 'filtered_html';
  $fe_block_boxes->machine_name = 'interventions_moderator';
  $fe_block_boxes->body = '<p><a href="/admin/workbench/needs-review">Interventions Needing Review</a></p><p>Published Interventions</p><p><a href="/user/logout">Log Out</a></p>';

  $export['interventions_moderator'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Interventions for CTLs';
  $fe_block_boxes->format = 'filtered_html';
  $fe_block_boxes->machine_name = 'my_interventions';
  $fe_block_boxes->body = '<p><a href="/admin/workbench/drafts">To Be Reviewed</a></p><p><a href="/admin/workbench/reviewed_approved">Reviewed: Approved</a></p><p><a href="/admin/workbench/reviewed_opted_out">Reviewed: Opted Out</a></p><p><a href="/user/logout">Log Out</a></p>';

  $export['my_interventions'] = $fe_block_boxes;

  return $export;
}
