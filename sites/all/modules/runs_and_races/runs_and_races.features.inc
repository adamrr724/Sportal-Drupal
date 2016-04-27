<?php
/**
 * @file
 * runs_and_races.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function runs_and_races_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function runs_and_races_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function runs_and_races_node_info() {
  $items = array(
    'runs_and_races' => array(
      'name' => t('Runs and Races'),
      'base' => 'node_content',
      'description' => t('Find an event like a 5k run or a bike race!'),
      'has_title' => '1',
      'title_label' => t('Event Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
