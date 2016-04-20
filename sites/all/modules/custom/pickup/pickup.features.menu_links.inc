<?php
/**
 * @file
 * pickup.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function pickup_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_pickup-games:pickup.
  $menu_links['main-menu_pickup-games:pickup'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'pickup',
    'router_path' => 'pickup',
    'link_title' => 'Pickup Games',
    'options' => array(
      'identifier' => 'main-menu_pickup-games:pickup',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Pickup Games');

  return $menu_links;
}
