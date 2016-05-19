<?php
/**
 * @file
 * landing_page.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function landing_page_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_frontpage';
  $strongarm->value = 'node';
  $export['site_frontpage'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_sportal_settings';
  $strongarm->value = array(
    'toggle_logo' => 1,
    'toggle_name' => 0,
    'toggle_slogan' => 1,
    'toggle_node_user_picture' => 1,
    'toggle_comment_user_picture' => 1,
    'toggle_comment_user_verification' => 1,
    'toggle_favicon' => 1,
    'toggle_main_menu' => 1,
    'toggle_secondary_menu' => 1,
    'default_logo' => 1,
    'logo_path' => '',
    'logo_upload' => '',
    'default_favicon' => 0,
    'favicon_path' => 'public://screenshot.png',
    'favicon_upload' => '',
    'breadcrumbs' => 0,
    'slideshow_display' => 1,
    'slide1_head' => 'Sample product',
    'slide1_desc' => 'Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt elit, sed do eiusmod tempor...',
    'slide1_url' => 'node/1',
    'favicon_mimetype' => 'image/png',
  );
  $export['theme_sportal_settings'] = $strongarm;

  return $export;
}
