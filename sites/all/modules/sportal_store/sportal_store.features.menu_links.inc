<?php
/**
 * @file
 * sportal_store.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function sportal_store_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-sportal_sportal-store:node/26.
  $menu_links['menu-sportal_sportal-store:node/26'] = array(
    'menu_name' => 'menu-sportal',
    'link_path' => 'node/26',
    'router_path' => 'node/%',
    'link_title' => 'Sportal Store',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-sportal_sportal-store:node/26',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Sportal Store');

  return $menu_links;
}
