<?php
/**
 * @file
 * pickup.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pickup_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function pickup_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function pickup_node_info() {
  $items = array(
    'pickup_game' => array(
      'name' => t('Pickup Game'),
      'base' => 'node_content',
      'description' => t('Please enter the details of the game you want to display.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
