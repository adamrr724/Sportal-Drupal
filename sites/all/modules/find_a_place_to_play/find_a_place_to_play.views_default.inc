<?php
/**
 * @file
 * find_a_place_to_play.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function find_a_place_to_play_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'find_a_place_to_play';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Find a Place to Play';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Find a Place to Play';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['style_plugin'] = 'gmap';
  $handler->display->display_options['style_options']['macro'] = '[gmap zoom=12 |center=45.5231,-122.6765| width=100% | height=600px | type=Map]';
  $handler->display->display_options['style_options']['markertype'] = 'green';
  $handler->display->display_options['style_options']['latfield'] = 'title';
  $handler->display->display_options['style_options']['lonfield'] = 'title';
  $handler->display->display_options['style_options']['markerfield'] = 'title';
  $handler->display->display_options['style_options']['geofield'] = 'title';
  $handler->display->display_options['style_options']['enablermt'] = 0;
  $handler->display->display_options['style_options']['rmtfield'] = 'title';
  $handler->display->display_options['style_options']['rmtfieldraw'] = 1;
  $handler->display->display_options['style_options']['animation'] = '2';
  $handler->display->display_options['style_options']['tooltipfield'] = 'title';
  $handler->display->display_options['style_options']['bubbletextfield'] = 'title';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'title' => 'title',
    'field_address_place' => 'field_address_place',
    'field_image_place' => 'field_image_place',
    'field_facilities' => 'field_facilities',
  );
  $handler->display->display_options['row_options']['separator'] = '<hr>';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Address */
  $handler->display->display_options['fields']['field_address_place']['id'] = 'field_address_place';
  $handler->display->display_options['fields']['field_address_place']['table'] = 'field_data_field_address_place';
  $handler->display->display_options['fields']['field_address_place']['field'] = 'field_address_place';
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_image_place']['id'] = 'field_image_place';
  $handler->display->display_options['fields']['field_image_place']['table'] = 'field_data_field_image_place';
  $handler->display->display_options['fields']['field_image_place']['field'] = 'field_image_place';
  $handler->display->display_options['fields']['field_image_place']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image_place']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => 'content',
  );
  /* Field: Content: Facilities */
  $handler->display->display_options['fields']['field_facilities']['id'] = 'field_facilities';
  $handler->display->display_options['fields']['field_facilities']['table'] = 'field_data_field_facilities';
  $handler->display->display_options['fields']['field_facilities']['field'] = 'field_facilities';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'place_to_play' => 'place_to_play',
  );
  /* Filter criterion: Content: Facilities (field_facilities) */
  $handler->display->display_options['filters']['field_facilities_value']['id'] = 'field_facilities_value';
  $handler->display->display_options['filters']['field_facilities_value']['table'] = 'field_data_field_facilities';
  $handler->display->display_options['filters']['field_facilities_value']['field'] = 'field_facilities_value';
  $handler->display->display_options['filters']['field_facilities_value']['operator'] = 'and';
  $handler->display->display_options['filters']['field_facilities_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_facilities_value']['expose']['operator_id'] = 'field_facilities_value_op';
  $handler->display->display_options['filters']['field_facilities_value']['expose']['label'] = 'Facilities (field_facilities)';
  $handler->display->display_options['filters']['field_facilities_value']['expose']['operator'] = 'field_facilities_value_op';
  $handler->display->display_options['filters']['field_facilities_value']['expose']['identifier'] = 'field_facilities_value';
  $handler->display->display_options['filters']['field_facilities_value']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_facilities_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    4 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_facilities_value']['group_info']['label'] = 'Facilities (field_facilities)';
  $handler->display->display_options['filters']['field_facilities_value']['group_info']['identifier'] = 'field_facilities_value';
  $handler->display->display_options['filters']['field_facilities_value']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['field_facilities_value']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'place_to_play' => 'place_to_play',
  );
  /* Filter criterion: Content: Facilities (field_facilities) */
  $handler->display->display_options['filters']['field_facilities_value']['id'] = 'field_facilities_value';
  $handler->display->display_options['filters']['field_facilities_value']['table'] = 'field_data_field_facilities';
  $handler->display->display_options['filters']['field_facilities_value']['field'] = 'field_facilities_value';
  $handler->display->display_options['filters']['field_facilities_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_facilities_value']['expose']['operator_id'] = 'field_facilities_value_op';
  $handler->display->display_options['filters']['field_facilities_value']['expose']['label'] = 'Filter by Facilities';
  $handler->display->display_options['filters']['field_facilities_value']['expose']['operator'] = 'field_facilities_value_op';
  $handler->display->display_options['filters']['field_facilities_value']['expose']['identifier'] = 'field_facilities_value';
  $handler->display->display_options['filters']['field_facilities_value']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_facilities_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    4 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_facilities_value']['group_info']['label'] = 'Facilities (field_facilities)';
  $handler->display->display_options['filters']['field_facilities_value']['group_info']['identifier'] = 'field_facilities_value';
  $handler->display->display_options['filters']['field_facilities_value']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['field_facilities_value']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  $handler->display->display_options['path'] = 'find-a-place-to-play';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Find a Place to Play';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $export['find_a_place_to_play'] = $view;

  return $export;
}
