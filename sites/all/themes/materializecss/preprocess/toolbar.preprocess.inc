<?php

/**
 * @file
 * Contains preprocess functions for Toolbar.
 */

/**
 * Implements hook_preprocess_toolbar().
 */
function materialize_preprocess_toolbar(&$variables) {
  // Override default theme wrappers to be able to style shortcut sets in
  // the same way.
  $variables['toolbar']['toolbar_drawer'][0]['shortcuts']['#theme_wrappers'] = array('menu_tree__shortcut_set');
}
