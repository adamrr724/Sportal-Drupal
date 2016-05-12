<?php

/**
 * @file
 * Override or insert variables into the BLOCK templates.
 *
 * To add dynamically your own classes use
 * $vars['classes_array'][] = 'my_class';
 */

/**
 * Implements hook_preprocess_block().
 */
function materialize_preprocess_block(&$variables) {
  if ($variables['block_html_id'] == 'block-system-main') {
    $variables['theme_hook_suggestions'][] = 'block__no_wrapper';
  }
  $variables['content_attributes_array']['class'][] = 'content';
  $variables['title_attributes_array']['class'][] = 'collection-header';
  $variables['wrapper'] = empty($variables['wrapper']) ? array() : $variables['wrapper'];
  $variables['title'] = $variables['block']->subject;
  $sidebars = array('sidebar_first', 'sidebar_second');
  if (!empty($variables['block']->region) && in_array($variables['block']->region, $sidebars)) {
    // Check if the block represents a menu and unset title as it is already
    // added to menu structure in the hook_preprocess_page().
    if (!empty($variables['elements']['#is_menu'])) {
      unset($variables['title']);
    }
    else {
      $variables['wrapper']['class'][] = 'collection with-header';
      $variables['content_attributes_array']['class'][] = 'collection-item';
    }
    $variables['title_attributes_array']['class'][] = 'block-title';
  }
}
