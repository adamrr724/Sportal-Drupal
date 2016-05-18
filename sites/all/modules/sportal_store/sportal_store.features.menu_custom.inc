<?php
/**
 * @file
 * sportal_store.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function sportal_store_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-sportal.
  $menus['menu-sportal'] = array(
    'menu_name' => 'menu-sportal',
    'title' => 'Sportal',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Sportal');

  return $menus;
}
