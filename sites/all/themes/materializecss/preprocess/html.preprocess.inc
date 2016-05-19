<?php

/**
 * @file
 * Override or insert variables into the HTML templates.
 *
 * To add dynamically your own classes use
 * $vars['classes_array'][] = 'my_class';
 */

/**
 * Implements hook_preprocess_html().
 */
function materialize_preprocess_html(&$vars) {
  if (materialize_check_library('materialize', 'css/materialize.min.css') && materialize_check_library('materialize', 'js/materialize.min.js')) {
    drupal_add_css(libraries_get_path('materialize') . '/css/materialize.min.css', array('group' => CSS_THEME, 'every_page' => TRUE));
    drupal_add_js(libraries_get_path('materialize') . '/js/materialize.min.js',
      array(
        'group' => JS_THEME,
        'every_page' => TRUE,
        'weight' => '-1',
      )
    );
  }
  else {
    drupal_set_message(t('Please download the latest version of <a href="http://materializecss.com/getting-started.html">Materialize</a> and place all content after extract to a new libraries folder <em>/materialize</em> within your drupal installation. %css_file and %js_file', array('%css_file' => 'sites/all/libraries/materialize/css/materialize.min.css', '%js_file' => 'sites/all/libraries/materialize/js/materialize.min.js')), 'error');
  }
  if (!module_exists('jquery_update')) {
    drupal_set_message(t('Materialize requires the <a href="@url">jQuery Update module</a> to be installed.',
      array(
        '@url' => url('https://www.drupal.org/project/jquery_update/'),
      )), 'error');
  }
  elseif (version_compare(variable_get('jquery_update_jquery_version'), '1.8', '<')) {
    drupal_set_message(t('Materialize requires at least @version. Please enable it by <a href="@url">clicking here</a>.',
      array(
        '@version' => 'jQuery 1.8',
        '@url' => url('admin/config/development/jquery_update'),
      )), 'error');
  }
}
