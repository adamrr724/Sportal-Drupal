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
  $strongarm->name = 'theme_nexus_settings';
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
    'default_logo' => 0,
    'logo_path' => 'public://designcrowd_944_8420995_1595193_414486a0_thumbnail_0.png',
    'logo_upload' => '',
    'default_favicon' => 0,
    'favicon_path' => 'public://designcrowd_944_8421036_1595193_084da4f2_thumbnail_0.png',
    'favicon_upload' => '',
    'breadcrumbs' => 0,
    'slideshow_display' => 1,
    'slide1_head' => 'Find your next Game',
    'slide1_desc' => 'Search among hundreds of Leagues, Pick-Up games, Runs, Races, or Places to Play. ',
    'slide1_url' => '',
    'favicon_mimetype' => 'image/png',
  );
  $export['theme_nexus_settings'] = $strongarm;

  return $export;
}
