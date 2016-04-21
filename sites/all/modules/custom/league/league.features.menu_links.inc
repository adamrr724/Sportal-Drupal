<?php
/**
 * @file
 * league.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function league_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_leagues:leagues.
  $menu_links['main-menu_leagues:leagues'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'leagues',
    'router_path' => 'leagues',
    'link_title' => 'Leagues',
    'options' => array(
      'identifier' => 'main-menu_leagues:leagues',
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
  t('Leagues');

  return $menu_links;
}
