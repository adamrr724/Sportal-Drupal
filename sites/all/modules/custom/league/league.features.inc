<?php
/**
 * @file
 * league.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function league_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function league_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function league_node_info() {
  $items = array(
    'league' => array(
      'name' => t('League'),
      'base' => 'node_content',
      'description' => t('Add a league to the site.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
