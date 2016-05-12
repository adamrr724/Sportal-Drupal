<?php

/**
 * @file
 * Contains preprocess functions for table.
 */

/**
 * Implements hook_preprocess_table().
 */
function materialize_preprocess_table(&$variables) {
  $variables['attributes']['class'][] = 'bordered';
  $variables['attributes']['class'][] = 'responsive-table';
  $variables['attributes']['class'][] = 'striped';
}
