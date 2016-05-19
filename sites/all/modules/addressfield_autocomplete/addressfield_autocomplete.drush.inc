<?php

/**
 * @file
 * Drush integration for addressfield autocomplete.
 */

define('ADDRESSFIELD_AUTOCOMPLETE_GEOCOMPLETE_DOWNLOAD_URI', 'https://github.com/ubilabs/geocomplete/archive/master.zip');
define('ADDRESSFIELD_AUTOCOMPLETE_GEOCOMPLETE_DOWNLOAD_PREFIX', 'geocomplete-');

/**
 * Implements hook_drush_command().
 */
function addressfield_autocomplete_drush_command() {
  $items = array();
  $items['geocomplete-plugin'] = array(
    'callback' => 'drush_addressfield_autocomplete_geocomplete_plugin',
    'description' => dt('Download and install the Geocomplete plugin.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'arguments' => array(
      'path' => dt('Optional. A path where to install the Geocomplete plugin. If omitted Drush will use the default location.'),
    ),
    'aliases' => array('geocompleteplugin', 'addressfieldautocomplete-plugin'),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function addressfield_autocomplete_drush_help($section) {
  switch ($section) {
    case 'drush:geocomplete-plugin':
      return dt('Download and install the Geocomplete plugin from ubilabs.github.io/geocomplete/, default location is sites/all/libraries.');
  }
}

/**
 * Command to download the Geocomplete plugin.
 */
function drush_addressfield_autocomplete_geocomplete_plugin() {
  $args = func_get_args();
  $result = FALSE;

  if (!empty($args[0])) {
    $path = $args[0];
  }
  else {
    $path = 'sites/all/libraries';
  }

  // Create the path if it does not exist.
  if (!is_dir($path)) {
    drush_op('mkdir', $path);
    drush_log(dt('Directory @path was created', array('@path' => $path)), 'notice');
  }

  // Set the directory to the download location.
  $olddir = getcwd();
  chdir($path);

  // Download the tarball archive.
  if ($filepath = drush_download_file(ADDRESSFIELD_AUTOCOMPLETE_GEOCOMPLETE_DOWNLOAD_URI)) {
    $filename = basename($filepath);
    $dirname = ADDRESSFIELD_AUTOCOMPLETE_GEOCOMPLETE_DOWNLOAD_PREFIX . basename($filepath, '.zip');

    // Remove any existing Geocomplete plugin directory.
    if (is_dir($dirname) || is_dir('geocomplete')) {
      drush_delete_dir($dirname, TRUE);
      drush_delete_dir('geocomplete', TRUE);
      drush_log(dt('An existing Geocomplete plugin was deleted from @path', array('@path' => $path)), 'notice');
    }

    // Decompress the zip archive.
    $result = drush_tarball_extract($filename);

    // Change the directory name to "geocomplete" if needed.
    if ($dirname != 'geocomplete') {
      $result = drush_move_dir($dirname, 'geocomplete', TRUE);
    }
  }

  if ($result) {
    drush_log(dt('Geocomplete plugin has been installed in @path', array('@path' => $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to install the Geocomplete plugin to @path', array('@path' => $path)), 'error');
  }

  // Set working directory back to the previous working directory.
  chdir($olddir);
}
