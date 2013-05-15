<?php
/**
 * Implementation of hook_views_query_alter
 */
function intervention_views_query_alter(&$view, &$query) {

  // TODO: Perhaps we want this workaround to apply to all Views with a
  //       "representative node" Relationship rather than to a select list of
  //       Views, as we're doing below. The former certainly seems more
  //       maintainable...
  $views_to_modify = array(
      'interventions_by_college',
      'interventions_missing_reports',
  );
  if (in_array($view->name, $views_to_modify)) {
    _interventions_views_query_alter_allow_taxonomy_lookup_on_unpublished_nodes($query);
  }

  // to keep this readable, each View gets its own function for customization
  $function = "_intervention_views_{$view->name}_query_alter";
  if (function_exists($function)) {
    $function($view, $query);
  }
}

/**
 * Callback function for interventions_missing_reports View
 *
 * Due to limitations in the Views UI, for a filter we cannot specify a relative
 * date as a value or a "less than" as an operator for a date field, so we do it
 * here, overriding the UI.
 *
 * @see hook_views_query_alter
 */
function _intervention_views_interventions_missing_reports_query_alter(&$view, &$query) {
  foreach($query->where[1]['conditions'] as $i => $arr) {
    if ($arr['field'] == 'node_taxonomy_term_data__field_data_field_reporting_year.field_reporting_year_value') {
      $query->where[1]['conditions'][$i]['value'] = date('Y-m-d H:i:s', strtotime('January 1'));
      $query->where[1]['conditions'][$i]['operator'] = '<';
    }
  }
}

/**
 * Helper function for implementation of hook_views_query_alter
 *
 * This is a terrible hack. The "representative node" Views Relationship
 * uses the taxonomy_index table to look up which terms are associated with
 * which nodes. In Drupal 7, only published nodes are tracked in
 * this table. For us, this means that Intervention nodes in a draft state
 * will be excluded from the interventions_by_college View.
 *
 * A little background:
 *
 * From code comments in taxonomy.module: Taxonomy uses default field storage
 * to store canonical relationships between terms and fieldable entities.
 * However its most common use case requires listing all content associated
 * with a term or group of terms sorted by creation date. To avoid slow
 * queries due to joining across multiple node and field tables with various
 * conditions and order by criteria, we maintain a denormalized table with all
 * relationships between terms, published nodes and common sort criteria such
 * as sticky and created.
 *
 * bangpound, one of the designers of taxonomy_index, was surprised to learn
 * that Views relies on this table, which "is mostly a bridge back to old (D6)
 * functionality" (@see http://drupal.org/node/962664#comment-3675872).
 *
 * Dave Reid developed the taxonomy_entity_index module (@see
 * http://drupal.org/project/taxonomy_entity_index), which seeks to resolve
 * some of the problems with taxonomy_index. While it offers some new filters,
 * relationships, etc. to Views, it does not fix the "representative node"
 * Relationship, which is what we're interested in.
 *
 * So we resort to harcoded SQL.
 */
function _interventions_views_query_alter_allow_taxonomy_lookup_on_unpublished_nodes(&$query) {
  $sql = "
    SELECT nodeINNER.nid AS nidINNER
    FROM {node} nodeINNER
    LEFT JOIN {field_data_field_intervention_family} taxonomy_indexINNER
    ON nodeINNER.nid = taxonomy_indexINNER.entity_id
    LEFT JOIN {taxonomy_term_data} taxonomy_term_data_nodeINNER
    ON taxonomy_indexINNER.field_intervention_family_tid = taxonomy_term_data_nodeINNER.tid
    WHERE (( (taxonomy_term_data_nodeINNER.tid = taxonomy_term_data.tid ) ))
    ORDER BY nodeINNER.nid DESC
    LIMIT 1 OFFSET 0";

  $query->table_queue['node_taxonomy_term_data']['join']->definition['left_query'] = $sql;
  $query->table_queue['node_taxonomy_term_data']['join']->left_query = $sql;
}