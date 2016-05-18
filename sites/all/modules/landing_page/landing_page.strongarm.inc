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
    'default_favicon' => 1,
    'favicon_path' => '',
    'favicon_upload' => '',
    'breadcrumbs' => 1,
    'slideshow_display' => 1,
    'slide1_head' => 'Sample product',
    'slide1_desc' => 'Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt elit, sed do eiusmod tempor...',
    'slide1_url' => 'node/1',
    'slide2_head' => 'Sample service',
    'slide2_desc' => 'Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do Lorem ipsum dolor sit amet irure dolor in reprehenderit...',
    'slide2_url' => 'node/2',
    'slide3_head' => 'Contact us',
    'slide3_desc' => 'Duis aute irure dolor in reprehenderit inLorem ipsum dolor sit amet, consectetur do Lorem ipsum dolor sit amet irure...',
    'slide3_url' => 'node/3',
  );
  $export['theme_sportal_settings'] = $strongarm;

  return $export;
}
