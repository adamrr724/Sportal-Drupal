<?php
/**
 * @file
 * league.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function league_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'leagues';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Leagues';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['style_plugin'] = 'gmap';
  $handler->display->display_options['style_options']['macro'] = '[gmap zoom=12 |center=45.5231,-122.6765| width=100% | height=600px | type=Map]';
  $handler->display->display_options['style_options']['markertype'] = 'blue';
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
    'field_league_sport' => 'field_league_sport',
    'field_league_date' => 'field_league_date',
    'field_notes' => 'field_notes',
    'field_skill_level' => 'field_skill_level',
    'field_fees' => 'field_fees',
    'field_league_image' => 'field_league_image',
    'field_league_address' => 'field_league_address',
  );
  $handler->display->display_options['row_options']['separator'] = '<hr>';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Sport */
  $handler->display->display_options['fields']['field_league_sport']['id'] = 'field_league_sport';
  $handler->display->display_options['fields']['field_league_sport']['table'] = 'field_data_field_league_sport';
  $handler->display->display_options['fields']['field_league_sport']['field'] = 'field_league_sport';
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_league_date']['id'] = 'field_league_date';
  $handler->display->display_options['fields']['field_league_date']['table'] = 'field_data_field_league_date';
  $handler->display->display_options['fields']['field_league_date']['field'] = 'field_league_date';
  $handler->display->display_options['fields']['field_league_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: Skill Level */
  $handler->display->display_options['fields']['field_skill_level']['id'] = 'field_skill_level';
  $handler->display->display_options['fields']['field_skill_level']['table'] = 'field_data_field_skill_level';
  $handler->display->display_options['fields']['field_skill_level']['field'] = 'field_skill_level';
  /* Field: Content: Fees */
  $handler->display->display_options['fields']['field_fees']['id'] = 'field_fees';
  $handler->display->display_options['fields']['field_fees']['table'] = 'field_data_field_fees';
  $handler->display->display_options['fields']['field_fees']['field'] = 'field_fees';
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_league_image']['id'] = 'field_league_image';
  $handler->display->display_options['fields']['field_league_image']['table'] = 'field_data_field_league_image';
  $handler->display->display_options['fields']['field_league_image']['field'] = 'field_league_image';
  $handler->display->display_options['fields']['field_league_image']['label'] = '';
  $handler->display->display_options['fields']['field_league_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_league_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_league_image']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => 'content',
  );
  /* Field: Content: Address */
  $handler->display->display_options['fields']['field_league_address']['id'] = 'field_league_address';
  $handler->display->display_options['fields']['field_league_address']['table'] = 'field_data_field_league_address';
  $handler->display->display_options['fields']['field_league_address']['field'] = 'field_league_address';
  $handler->display->display_options['fields']['field_league_address']['label'] = '';
  $handler->display->display_options['fields']['field_league_address']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
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
    'league' => 'league',
  );
  /* Filter criterion: Content: Sport (field_league_sport) */
  $handler->display->display_options['filters']['field_league_sport_value']['id'] = 'field_league_sport_value';
  $handler->display->display_options['filters']['field_league_sport_value']['table'] = 'field_data_field_league_sport';
  $handler->display->display_options['filters']['field_league_sport_value']['field'] = 'field_league_sport_value';
  $handler->display->display_options['filters']['field_league_sport_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_league_sport_value']['expose']['operator_id'] = 'field_league_sport_value_op';
  $handler->display->display_options['filters']['field_league_sport_value']['expose']['label'] = 'Sport ';
  $handler->display->display_options['filters']['field_league_sport_value']['expose']['operator'] = 'field_league_sport_value_op';
  $handler->display->display_options['filters']['field_league_sport_value']['expose']['identifier'] = 'field_league_sport_value';
  $handler->display->display_options['filters']['field_league_sport_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    3 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Leagues';
  $handler->display->display_options['path'] = 'leagues';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Leagues';
  $handler->display->display_options['menu']['name'] = 'main-menu';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Fees */
  $handler->display->display_options['fields']['field_fees']['id'] = 'field_fees';
  $handler->display->display_options['fields']['field_fees']['table'] = 'field_data_field_fees';
  $handler->display->display_options['fields']['field_fees']['field'] = 'field_fees';
  /* Field: Content: Address */
  $handler->display->display_options['fields']['field_league_address']['id'] = 'field_league_address';
  $handler->display->display_options['fields']['field_league_address']['table'] = 'field_data_field_league_address';
  $handler->display->display_options['fields']['field_league_address']['field'] = 'field_league_address';
  $handler->display->display_options['fields']['field_league_address']['type'] = 'location_all';
  /* Field: Content: Notes */
  $handler->display->display_options['fields']['field_notes']['id'] = 'field_notes';
  $handler->display->display_options['fields']['field_notes']['table'] = 'field_data_field_notes';
  $handler->display->display_options['fields']['field_notes']['field'] = 'field_notes';
  /* Field: Content: Skill Level */
  $handler->display->display_options['fields']['field_skill_level']['id'] = 'field_skill_level';
  $handler->display->display_options['fields']['field_skill_level']['table'] = 'field_data_field_skill_level';
  $handler->display->display_options['fields']['field_skill_level']['field'] = 'field_skill_level';
  /* Field: Content: Sport */
  $handler->display->display_options['fields']['field_league_sport']['id'] = 'field_league_sport';
  $handler->display->display_options['fields']['field_league_sport']['table'] = 'field_data_field_league_sport';
  $handler->display->display_options['fields']['field_league_sport']['field'] = 'field_league_sport';
  $export['leagues'] = $view;

  return $export;
}
