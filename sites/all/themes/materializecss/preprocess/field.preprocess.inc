<?php

/**
 * @file
 * Contains preprocess functions for field.
 */

/**
 * Implements hook_preprocess_field().
 */
function materialize_preprocess_field(&$vars) {
  if ($vars['element']['#field_name'] == 'field_tags' || $vars['element']['#field_name'] == 'taxonomy_forums') {
    array_walk($vars['items'], 'materialize_update_element_classes');
  }
}

/**
 * Adds necessary classes for the field element.
 */
function materialize_update_element_classes(&$el) {
  $el['#options']['attributes']['class'][] = 'chip';
}
