<?php

/**
 * @file
 * Preprocess functions for page.
 */

/**
 * Implements hook_preprocess_page().
 */
function materialize_preprocess_page(&$variables) {
  if (!empty($variables['page']['sidebar_first'])) {
    $left = $variables['page']['sidebar_first'];
  }

  if (!empty($variables['page']['sidebar_second'])) {
    $right = $variables['page']['sidebar_second'];
  }
  // Dynamic sidebars.
  if (!empty($left) && !empty($right)) {
    $variables['main_grid'] = 'col s12 m6';
    $variables['sidebar_left'] = 'col s12 m3';
    $variables['sidebar_right'] = 'col s12 m3';
  }
  elseif (empty($left) && !empty($right)) {
    $variables['main_grid'] = 'col s12 m9';
    $variables['sidebar_left'] = '';
    $variables['sidebar_right'] = 'col s12 m3';
  }
  elseif (!empty($left) && empty($right)) {
    $variables['main_grid'] = 'col s12 m9';
    $variables['sidebar_left'] = 'col s12 m3';
    $variables['sidebar_right'] = '';
  }
  else {
    $variables['main_grid'] = 'col s12';
    $variables['sidebar_left'] = '';
    $variables['sidebar_right'] = '';
  }

  // Primary nav.
  $variables['primary_nav'] = FALSE;
  if ($variables['main_menu']) {
    // Build links.
    $variables['primary_nav'] = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
    // Provide default theme wrapper function.
    $variables['primary_nav']['#theme_wrappers'] = array('menu_tree__primary');
  }
  // Secondary nav.
  $variables['secondary_nav'] = FALSE;
  if ($variables['secondary_menu']) {
    // Build links.
    $variables['secondary_nav'] = menu_tree(variable_get('menu_secondary_links_source', 'user-menu'));
    // Provide default theme wrapper function.
    $variables['secondary_nav']['#theme_wrappers'] = array('menu_tree__secondary');
  }
  // Update menus in sidebars to use separate wrapper.
  materialize_iscale_page_update_sidebar_menus($variables);
  // As we are placing secondary menu inside the wrapper we need to split menus
  // into two variables.
  $variables['tabs_primary'] = $variables['tabs'];
  unset($variables['tabs_primary']['#secondary']);
  $variables['tabs_secondary'] = $variables['tabs'];
  unset($variables['tabs_secondary']['#primary']);
}

/**
 * Update menu if it is placed in a sidebar.
 *
 * By default Drupal renders block title above the block. It would be good to
 * render it as a menu title inside menu structure (with classes "header item").
 *
 * @param array $variables
 *   An array of variables passed from hook_preprocess_page().
 */
function materialize_iscale_page_update_sidebar_menus(&$variables) {
  $menus = menu_get_menus(TRUE);
  $sidebars = array('sidebar_first', 'sidebar_second');

  // Walk through both sidebars.
  foreach ($sidebars as $sidebar) {
    $sidebar_elements = isset($variables['page'][$sidebar]) ? element_children($variables['page'][$sidebar]) : array();
    foreach ($sidebar_elements as $element_name) {
      $element = $variables['page'][$sidebar][$element_name];

      // Check if sidebar element is a menu.
      if (isset($element['#block']) &&
          in_array($element['#block']->module, array('system', 'menu')) &&
          array_key_exists($element['#block']->delta, $menus)) {

        // Do not add title item if it is empty.
        if (!empty($variables['page'][$sidebar][$element_name]['#block']->subject)) {
          $menu_header['menu_header'] = array(
            '#prefix' => '<h4 class="collection-header">',
            '#suffix' => '</h4>',
          );
          $menu_header['menu_header']['header'] = array(
            '#markup' => $variables['page'][$sidebar][$element_name]['#block']->subject,
          );

          $variables['page'][$sidebar][$element_name] = $menu_header + $variables['page'][$sidebar][$element_name];
        }

        $variables['page'][$sidebar][$element_name]['#is_menu'] = TRUE;
      }
    }
  }
}
