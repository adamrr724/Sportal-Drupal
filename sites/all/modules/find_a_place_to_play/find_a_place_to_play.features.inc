<?php
/**
 * @file
 * find_a_place_to_play.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function find_a_place_to_play_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function find_a_place_to_play_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function find_a_place_to_play_node_info() {
  $items = array(
    'place_to_play' => array(
      'name' => t('Place to Play'),
      'base' => 'node_content',
      'description' => t('A facility, field, or court where you can play!'),
      'has_title' => '1',
      'title_label' => t('Place Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
