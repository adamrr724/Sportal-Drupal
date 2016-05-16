<?php
/**
 * @file
 * pickup.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function pickup_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'game_calendar';
  $view->description = '';
  $view->tag = 'Calendar';
  $view->base_table = 'node';
  $view->human_name = 'Pickup Calendar';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Pickup Game Calendar';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['link_display'] = 'page_1';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'month';
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_date']['id'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['table'] = 'field_data_field_date';
  $handler->display->display_options['fields']['field_date']['field'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['label'] = '';
  $handler->display->display_options['fields']['field_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_date']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => '',
  );
  $handler->display->display_options['fields']['field_date']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_date']['delta_offset'] = '0';
  /* Sort criterion: Content: Date (field_date) */
  $handler->display->display_options['sorts']['field_date_value']['id'] = 'field_date_value';
  $handler->display->display_options['sorts']['field_date_value']['table'] = 'field_data_field_date';
  $handler->display->display_options['sorts']['field_date_value']['field'] = 'field_date_value';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Month */
  $handler = $view->new_display('page', 'Month', 'page_1');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'month';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['row_options']['colors']['legend'] = 'type';
  $handler->display->display_options['row_options']['colors']['calendar_colors_type'] = array(
    'article' => '#ffffff',
    'page' => '#ffffff',
    'league' => '#ffffff',
    'pickup_game' => '#ffffff',
  );
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_date.field_date_value' => 'field_data_field_date.field_date_value',
  );
  $handler->display->display_options['path'] = 'calendar/month';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Month';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Calendar';
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Week */
  $handler = $view->new_display('page', 'Week', 'page_2');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'week';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['calendar_type'] = 'week';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['granularity'] = 'week';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_date.field_date_value' => 'field_data_field_date.field_date_value',
  );
  $handler->display->display_options['path'] = 'calendar/week';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Week';
  $handler->display->display_options['menu']['weight'] = '2';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Day */
  $handler = $view->new_display('page', 'Day', 'page_3');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'day';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['calendar_type'] = 'day';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['granularity'] = 'day';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_date.field_date_value' => 'field_data_field_date.field_date_value',
  );
  $handler->display->display_options['path'] = 'calendar/day';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Day';
  $handler->display->display_options['menu']['weight'] = '3';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Year */
  $handler = $view->new_display('page', 'Year', 'page');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'year';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['calendar_type'] = 'year';
  $handler->display->display_options['style_options']['name_size'] = '1';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_date']['id'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['table'] = 'field_data_field_date';
  $handler->display->display_options['fields']['field_date']['field'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['label'] = '';
  $handler->display->display_options['fields']['field_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_date']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => '',
  );
  $handler->display->display_options['fields']['field_date']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_date']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['granularity'] = 'year';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_date.field_date_value' => 'field_data_field_date.field_date_value',
  );
  $handler->display->display_options['path'] = 'calendar-node-field-date/year';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Year';
  $handler->display->display_options['menu']['weight'] = '4';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'mini';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '1';
  $handler->display->display_options['style_options']['mini'] = '1';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_date.field_date_value' => 'field_data_field_date.field_date_value',
  );
  $handler->display->display_options['block_description'] = 'Pickup Calendar';

  /* Display: Upcoming */
  $handler = $view->new_display('block', 'Upcoming', 'block_2');
  $handler->display->display_options['display_description'] = 'Upcoming events block';
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>=';
  $handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
  $handler->display->display_options['filters']['date_filter']['add_delta'] = 'yes';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_date.field_date_value' => 'field_data_field_date.field_date_value',
  );
  $export['game_calendar'] = $view;

  $view = new view();
  $view->name = 'pickup_games';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Pickup Games';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'allow_secondary' => 0,
      'secondary_label' => 'Advanced options',
      'collapsible_label' => NULL,
      'combine_rewrite' => NULL,
      'reset_label' => NULL,
      'bef_filter_description' => NULL,
      'any_label' => NULL,
      'filter_rewrite_values' => NULL,
    ),
    'field_sport_value' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'bef_select_all_none' => FALSE,
        'bef_collapsible' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
            'secondary_label' => NULL,
            'collapsible_label' => NULL,
            'combine_rewrite' => NULL,
            'reset_label' => NULL,
            'bef_filter_description' => NULL,
            'any_label' => NULL,
            'filter_rewrite_values' => NULL,
          ),
          'secondary_label' => NULL,
          'collapsible_label' => NULL,
          'combine_rewrite' => NULL,
          'reset_label' => NULL,
          'bef_filter_description' => NULL,
          'any_label' => NULL,
          'filter_rewrite_values' => NULL,
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
          'secondary_label' => NULL,
          'collapsible_label' => NULL,
          'combine_rewrite' => NULL,
          'reset_label' => NULL,
          'bef_filter_description' => NULL,
          'any_label' => NULL,
        ),
        'secondary_label' => NULL,
        'collapsible_label' => NULL,
        'combine_rewrite' => NULL,
        'reset_label' => NULL,
        'filter_rewrite_values' => NULL,
      ),
      'secondary_label' => NULL,
      'collapsible_label' => NULL,
      'combine_rewrite' => NULL,
      'reset_label' => NULL,
      'bef_filter_description' => NULL,
      'any_label' => NULL,
      'filter_rewrite_values' => NULL,
    ),
    'field_pickup_skill_level_value' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'bef_select_all_none' => FALSE,
        'bef_collapsible' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
            'secondary_label' => NULL,
            'collapsible_label' => NULL,
            'combine_rewrite' => NULL,
            'reset_label' => NULL,
            'bef_filter_description' => NULL,
            'any_label' => NULL,
            'filter_rewrite_values' => NULL,
          ),
          'secondary_label' => NULL,
          'collapsible_label' => NULL,
          'combine_rewrite' => NULL,
          'reset_label' => NULL,
          'bef_filter_description' => NULL,
          'any_label' => NULL,
          'filter_rewrite_values' => NULL,
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
          'secondary_label' => NULL,
          'collapsible_label' => NULL,
          'combine_rewrite' => NULL,
          'reset_label' => NULL,
          'bef_filter_description' => NULL,
          'any_label' => NULL,
        ),
        'secondary_label' => NULL,
        'collapsible_label' => NULL,
        'combine_rewrite' => NULL,
        'reset_label' => NULL,
        'filter_rewrite_values' => NULL,
      ),
      'secondary_label' => NULL,
      'collapsible_label' => NULL,
      'combine_rewrite' => NULL,
      'reset_label' => NULL,
      'bef_filter_description' => NULL,
      'any_label' => NULL,
      'filter_rewrite_values' => NULL,
    ),
    'field_geofield_distance' => array(
      'bef_format' => 'bef_slider',
      'slider_options' => array(
        'bef_slider_min' => '0',
        'bef_slider_max' => '100',
        'bef_slider_step' => '1',
        'bef_slider_animate' => 'normal',
        'bef_slider_orientation' => 'vertical',
        'secondary_label' => NULL,
        'collapsible_label' => NULL,
        'combine_rewrite' => NULL,
        'reset_label' => NULL,
        'bef_filter_description' => NULL,
        'any_label' => NULL,
        'filter_rewrite_values' => NULL,
      ),
      'more_options' => array(
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
            'secondary_label' => NULL,
            'collapsible_label' => NULL,
            'combine_rewrite' => NULL,
            'reset_label' => NULL,
            'bef_filter_description' => NULL,
            'any_label' => NULL,
            'filter_rewrite_values' => NULL,
          ),
          'secondary_label' => NULL,
          'collapsible_label' => NULL,
          'combine_rewrite' => NULL,
          'reset_label' => NULL,
          'bef_filter_description' => NULL,
          'any_label' => NULL,
          'filter_rewrite_values' => NULL,
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
          'secondary_label' => NULL,
          'collapsible_label' => NULL,
          'combine_rewrite' => NULL,
          'reset_label' => NULL,
          'bef_filter_description' => NULL,
          'any_label' => NULL,
        ),
        'secondary_label' => NULL,
        'collapsible_label' => NULL,
        'combine_rewrite' => NULL,
        'reset_label' => NULL,
        'filter_rewrite_values' => NULL,
      ),
      'secondary_label' => NULL,
      'collapsible_label' => NULL,
      'combine_rewrite' => NULL,
      'reset_label' => NULL,
      'bef_filter_description' => NULL,
      'any_label' => NULL,
      'filter_rewrite_values' => NULL,
    ),
    'secondary_label' => NULL,
    'collapsible_label' => NULL,
    'combine_rewrite' => NULL,
    'reset_label' => NULL,
    'bef_filter_description' => NULL,
    'any_label' => NULL,
    'filter_rewrite_values' => NULL,
  );
  $handler->display->display_options['exposed_form']['options']['input_required'] = 0;
  $handler->display->display_options['exposed_form']['options']['text_input_required_format'] = 'filtered_html';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'node';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_date']['id'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['table'] = 'field_data_field_date';
  $handler->display->display_options['fields']['field_date']['field'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: Sport */
  $handler->display->display_options['fields']['field_sport']['id'] = 'field_sport';
  $handler->display->display_options['fields']['field_sport']['table'] = 'field_data_field_sport';
  $handler->display->display_options['fields']['field_sport']['field'] = 'field_sport';
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_pickup_image']['id'] = 'field_pickup_image';
  $handler->display->display_options['fields']['field_pickup_image']['table'] = 'field_data_field_pickup_image';
  $handler->display->display_options['fields']['field_pickup_image']['field'] = 'field_pickup_image';
  $handler->display->display_options['fields']['field_pickup_image']['label'] = '';
  $handler->display->display_options['fields']['field_pickup_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pickup_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_pickup_image']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => 'content',
  );
  /* Field: Content: Position */
  $handler->display->display_options['fields']['field_position_pickup']['id'] = 'field_position_pickup';
  $handler->display->display_options['fields']['field_position_pickup']['table'] = 'field_data_field_position_pickup';
  $handler->display->display_options['fields']['field_position_pickup']['field'] = 'field_position_pickup';
  $handler->display->display_options['fields']['field_position_pickup']['click_sort_column'] = 'geom';
  $handler->display->display_options['fields']['field_position_pickup']['type'] = 'geofield_map_map';
  $handler->display->display_options['fields']['field_position_pickup']['settings'] = array(
    'geofield_map_width' => '100%',
    'geofield_map_height' => '300px',
    'geofield_map_center' => array(
      'lat' => '',
      'lon' => '',
      'geocode' => 'Find my location',
    ),
    'geofield_map_zoom' => '8',
    'geofield_map_min_zoom' => '0',
    'geofield_map_max_zoom' => '0',
    'geofield_map_controltype' => 'default',
    'geofield_map_mtc' => 'standard',
    'geofield_map_pancontrol' => 1,
    'geofield_map_maptype' => 'map',
    'geofield_map_baselayers_map' => 1,
    'geofield_map_baselayers_satellite' => 1,
    'geofield_map_baselayers_hybrid' => 1,
    'geofield_map_baselayers_physical' => 0,
    'geofield_map_scale' => 0,
    'geofield_map_overview' => 0,
    'geofield_map_overview_opened' => 0,
    'geofield_map_scrollwheel' => 0,
    'geofield_map_draggable' => 0,
    'geofield_map_streetview_show' => 0,
  );
  /* Field: Content: Position (field_position_pickup) - proximity */
  $handler->display->display_options['fields']['field_geofield_distance']['id'] = 'field_geofield_distance';
  $handler->display->display_options['fields']['field_geofield_distance']['table'] = 'field_data_field_position_pickup';
  $handler->display->display_options['fields']['field_geofield_distance']['field'] = 'field_geofield_distance';
  $handler->display->display_options['fields']['field_geofield_distance']['precision'] = '0';
  $handler->display->display_options['fields']['field_geofield_distance']['source'] = 'contextual_geofield_filter';
  $handler->display->display_options['fields']['field_geofield_distance']['geofield_proximity_manual'] = array(
    'lat' => '',
    'lon' => '',
  );
  $handler->display->display_options['fields']['field_geofield_distance']['geofield_proximity_entity_url_field'] = 'field_league_position';
  $handler->display->display_options['fields']['field_geofield_distance']['geofield_proximity_current_user_field'] = 'field_league_position';
  $handler->display->display_options['fields']['field_geofield_distance']['radius_of_earth'] = '3959';
  /* Sort criterion: Content: Position (field_position_pickup) - proximity */
  $handler->display->display_options['sorts']['field_geofield_distance']['id'] = 'field_geofield_distance';
  $handler->display->display_options['sorts']['field_geofield_distance']['table'] = 'field_data_field_position_pickup';
  $handler->display->display_options['sorts']['field_geofield_distance']['field'] = 'field_geofield_distance';
  $handler->display->display_options['sorts']['field_geofield_distance']['source'] = 'current_user';
  $handler->display->display_options['sorts']['field_geofield_distance']['geofield_proximity_manual'] = array(
    'lat' => '',
    'lon' => '',
  );
  $handler->display->display_options['sorts']['field_geofield_distance']['geofield_proximity_entity_url_field'] = 'field_league_position';
  $handler->display->display_options['sorts']['field_geofield_distance']['geofield_proximity_current_user_field'] = 'field_league_position';
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
    'pickup_game' => 'pickup_game',
  );
  /* Filter criterion: Content: Sport (field_sport) */
  $handler->display->display_options['filters']['field_sport_value']['id'] = 'field_sport_value';
  $handler->display->display_options['filters']['field_sport_value']['table'] = 'field_data_field_sport';
  $handler->display->display_options['filters']['field_sport_value']['field'] = 'field_sport_value';
  $handler->display->display_options['filters']['field_sport_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_sport_value']['expose']['operator_id'] = 'field_sport_value_op';
  $handler->display->display_options['filters']['field_sport_value']['expose']['label'] = 'Sport';
  $handler->display->display_options['filters']['field_sport_value']['expose']['operator'] = 'field_sport_value_op';
  $handler->display->display_options['filters']['field_sport_value']['expose']['identifier'] = 'field_sport_value';
  $handler->display->display_options['filters']['field_sport_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    4 => 0,
    3 => 0,
  );
  /* Filter criterion: Content: Skill Level (field_pickup_skill_level) */
  $handler->display->display_options['filters']['field_pickup_skill_level_value']['id'] = 'field_pickup_skill_level_value';
  $handler->display->display_options['filters']['field_pickup_skill_level_value']['table'] = 'field_data_field_pickup_skill_level';
  $handler->display->display_options['filters']['field_pickup_skill_level_value']['field'] = 'field_pickup_skill_level_value';
  $handler->display->display_options['filters']['field_pickup_skill_level_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_pickup_skill_level_value']['expose']['operator_id'] = 'field_pickup_skill_level_value_op';
  $handler->display->display_options['filters']['field_pickup_skill_level_value']['expose']['label'] = 'Skill Level ';
  $handler->display->display_options['filters']['field_pickup_skill_level_value']['expose']['operator'] = 'field_pickup_skill_level_value_op';
  $handler->display->display_options['filters']['field_pickup_skill_level_value']['expose']['identifier'] = 'field_pickup_skill_level_value';
  $handler->display->display_options['filters']['field_pickup_skill_level_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    4 => 0,
    3 => 0,
  );
  /* Filter criterion: Content: Position (field_position_pickup) - proximity */
  $handler->display->display_options['filters']['field_geofield_distance']['id'] = 'field_geofield_distance';
  $handler->display->display_options['filters']['field_geofield_distance']['table'] = 'field_data_field_position_pickup';
  $handler->display->display_options['filters']['field_geofield_distance']['field'] = 'field_geofield_distance';
  $handler->display->display_options['filters']['field_geofield_distance']['operator'] = '<';
  $handler->display->display_options['filters']['field_geofield_distance']['value'] = array(
    'distance' => '25',
    'distance2' => 200,
    'unit' => '3959',
    'origin' => '',
  );
  $handler->display->display_options['filters']['field_geofield_distance']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_geofield_distance']['expose']['operator_id'] = 'field_geofield_distance_op';
  $handler->display->display_options['filters']['field_geofield_distance']['expose']['label'] = 'Search by Zip Code';
  $handler->display->display_options['filters']['field_geofield_distance']['expose']['operator'] = 'field_geofield_distance_op';
  $handler->display->display_options['filters']['field_geofield_distance']['expose']['identifier'] = 'field_geofield_distance';
  $handler->display->display_options['filters']['field_geofield_distance']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    4 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_geofield_distance']['source'] = 'geocoder';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_entity_url_field'] = 'field_league_position';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_current_user_field'] = 'field_league_position';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Pickup Games';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'gmap';
  $handler->display->display_options['style_options']['macro'] = '[gmap zoom=12 | behavior=+autozoom | width=100% | height=600px | type=Map]';
  $handler->display->display_options['style_options']['datasource'] = 'geofield';
  $handler->display->display_options['style_options']['markertype'] = 'gray';
  $handler->display->display_options['style_options']['latfield'] = 'title';
  $handler->display->display_options['style_options']['lonfield'] = 'title';
  $handler->display->display_options['style_options']['markerfield'] = 'title';
  $handler->display->display_options['style_options']['geofield'] = 'field_position_pickup';
  $handler->display->display_options['style_options']['enablermt'] = 0;
  $handler->display->display_options['style_options']['rmtfield'] = 'title';
  $handler->display->display_options['style_options']['rmtfieldraw'] = 1;
  $handler->display->display_options['style_options']['animation'] = '2';
  $handler->display->display_options['style_options']['tooltipfield'] = 'title';
  $handler->display->display_options['style_options']['bubbletextfield'] = 'title';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'title' => 'title',
    'field_date' => 'field_date',
    'field_sport' => 'field_sport',
    'field_pickup_image' => 'field_pickup_image',
  );
  $handler->display->display_options['row_options']['separator'] = '<hr>';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = '<h3><strong>No Results Found.</strong></h3>
Please try again.';
  $handler->display->display_options['path'] = 'pickup';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Pickup Games';
  $handler->display->display_options['menu']['name'] = 'main-menu';

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
    'block_1' => 0,
    'block_2' => 0,
  );
  $handler->display->display_options['attachment_position'] = 'after';
  $handler->display->display_options['inherit_exposed_filters'] = TRUE;
  $export['pickup_games'] = $view;

  return $export;
}
