<?php
/**
 * @file
 * intervention.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function intervention_taxonomy_default_vocabularies() {
  return array(
    'interventions' => array(
      'name' => 'Interventions',
      'machine_name' => 'interventions',
      'description' => 'This taxonomy should not be updated manually. It is maintained via an integration with the Rules module.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
