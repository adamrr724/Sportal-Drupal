<?php

/**
 * @file
 * Contains breadcrumb theme and related functions.
 */

/**
 * Implements theme_breadrumb().
 *
 * Prints breadcrumbs.
 */
function materialize_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';

    $output .= '<div class="breadcrumb card-panel">' . implode(' » ', $breadcrumb) . '</div>';
    return $output;
  }
}
