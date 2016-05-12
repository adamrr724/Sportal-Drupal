<?php

/**
 * @file
 * Main template file.
 *
 * Implements preprocess, process functions and alter hooks.
 */

/**
 * Implements hook_css_alter().
 */
function materialize_css_alter(&$css) {
  $exclude = array(
    'modules/aggregator/aggregator.css' => FALSE,
    'modules/comment/comment.css' => FALSE,
    'modules/system/system.css' => FALSE,
    'modules/system/system.menus.css' => FALSE,
    'modules/system/system.messages.css' => FALSE,
    'modules/system/system.theme.css' => FALSE,
    'modules/user/user.css' => FALSE,
    'modules/search/search.css' => FALSE,
    'modules/filter/filter.css' => FALSE,
    'modules/field/theme/field.css' => FALSE,
    'misc/vertical-tabs.css' => FALSE,
  );
  $css = array_diff_key($css, $exclude);
}

/**
 * @file
 * Main template file.
 *
 * Implements preprocess, process functions and alter hooks.
 */

// Include drupal theme and helper functions.
require_once dirname(__FILE__) . '/inc/menu.inc';
require_once dirname(__FILE__) . '/inc/form.inc';
require_once dirname(__FILE__) . '/inc/pager.inc';
require_once dirname(__FILE__) . '/inc/breadcrumb.inc';
require_once dirname(__FILE__) . '/inc/utils.inc';
/**
 * Implements hook_theme_registry_alter().
 */
function materialize_theme_registry_alter(&$registry) {
  global $theme_key;
  $available_themes = list_themes();
  $base_themes = array();
  if (isset($available_themes[$theme_key]->info['base theme'])) {
    $base_themes = drupal_find_base_themes($available_themes, $theme_key);
  }
  // Use materialize theme as it provides necessary
  // functionality for page elements.
  $base_themes += array('materialize' => 'materialize');
  $base_themes += array($theme_key => $theme_key);

  foreach ($base_themes as $theme_key => $theme_human_name) {
    if (empty($theme_key)) {
      continue;
    }
    materialize_discover_hooks($theme_key, $registry);
  }
}


/**
 * Discovers and registers preprocess, process theme functions.
 */
function materialize_discover_hooks($theme, &$registry) {
  foreach (array('process', 'preprocess') as $type) {
    // Iterate over all preprocess/process files in the current theme.
    $discovered_files = materialize_discover_files($theme, $type);
    foreach ($discovered_files as $item) {
      $callback = "{$theme}_{$type}_{$item->hook}";

      // If there is no hook with that name, continue.
      if (!array_key_exists($item->hook, $registry)) {
        continue;
      }

      // Append the included (pre-)process hook to the array of functions.
      $registry[$item->hook]["$type functions"][] = $callback;

      // By adding this file to the 'includes' array we make sure that it is
      // available when the hook is executed.
      $registry[$item->hook]['includes'][] = $item->uri;
    }
  }
}

/**
 * Scans for files of a certain type in the current theme's path.
 */
function materialize_discover_files($theme, $type) {
  $length = -(strlen($type) + 1);

  $path = drupal_get_path('theme', $theme);
  // Only look for files that match the 'something.preprocess.inc' pattern.
  $mask = '/.' . $type . '.inc$/';

  // Recursively scan the folder for the current step for (pre-)process
  // files and write them to the registry.
  $files = file_scan_directory($path . '/' . $type, $mask);
  foreach ($files as &$file) {
    $file->hook = strtr(substr($file->name, 0, $length), '-', '_');
  };

  return $files;
}


/**
 * Implements hook_theme().
 */
function materialize_theme($existing, $type, $theme, $path) {
  return array(
    'search_block_input_wrapper' => array(
      'render element' => 'element',
      'function' => 'materialize_search_block_input_wrapper',
    ),
    'pager_item_list' => array(
      'variables' => array(
        'items' => array(),
      ),
    ),
  );
}
