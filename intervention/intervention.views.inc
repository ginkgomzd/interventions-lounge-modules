<?php
/**
 * Implementation of hook_views_query_alter
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
function intervention_views_query_alter(&$view, &$query) {

  if ($view->name == 'interventions_by_college') {
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

    $join = $query->table_queue['node_taxonomy_term_data']['join'];
    $join->definition['left_query'] = $sql;
    $join->left_query = $sql;
  }
}