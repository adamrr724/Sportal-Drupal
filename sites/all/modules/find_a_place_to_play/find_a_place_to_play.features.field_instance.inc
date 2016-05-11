<?php
/**
 * @file
 * find_a_place_to_play.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function find_a_place_to_play_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-place_to_play-body'.
  $field_instances['node-place_to_play-body'] = array(
    'bundle' => 'place_to_play',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Tell us about this place!',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'trim_length' => 600,
        ),
        'type' => 'text_summary_or_trimmed',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Notes',
    'required' => 1,
    'settings' => array(
      'display_summary' => 1,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 20,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => 31,
    ),
  );

  // Exported field_instance: 'node-place_to_play-field_address_place'.
  $field_instances['node-place_to_play-field_address_place'] = array(
    'bundle' => 'place_to_play',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'addressfield',
        'settings' => array(
          'format_handlers' => array(
            0 => 'address',
          ),
          'use_widget_handlers' => 1,
        ),
        'type' => 'addressfield_default',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_address_place',
    'label' => 'Address',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'addressfield_autocomplete',
      'settings' => array(
        'available_countries' => array(),
        'default_country' => 'US',
        'draggable' => 1,
        'format_handlers' => array(
          'address' => 'address',
          'address-hide-postal-code' => 0,
          'address-hide-street' => 0,
          'address-hide-country' => 0,
          'organisation' => 0,
          'name-full' => 0,
          'name-oneline' => 0,
          'address-optional' => 0,
        ),
        'geolocation' => TRUE,
        'html5_geocode' => 1,
        'manual_text' => '',
        'map' => 1,
        'restrict_country' => array(),
        'reveal' => 1,
        'reverse_geocode' => 0,
        'types' => 'geocode',
        'visible_markers' => 1,
      ),
      'type' => 'addressfield_autocomplete',
      'weight' => 35,
    ),
  );

  // Exported field_instance: 'node-place_to_play-field_facilities'.
  $field_instances['node-place_to_play-field_facilities'] = array(
    'bundle' => 'place_to_play',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_facilities',
    'label' => 'Facilities',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 33,
    ),
  );

  // Exported field_instance: 'node-place_to_play-field_image_place'.
  $field_instances['node-place_to_play-field_image_place'] = array(
    'bundle' => 'place_to_play',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_image_place',
    'label' => 'Image',
    'required' => FALSE,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => '',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'image',
      'settings' => array(
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => 34,
    ),
  );

  // Exported field_instance: 'node-place_to_play-field_position_place'.
  $field_instances['node-place_to_play-field_position_place'] = array(
    'bundle' => 'place_to_play',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'geofield_map',
        'settings' => array(
          'geofield_map_baselayers_hybrid' => 1,
          'geofield_map_baselayers_map' => 1,
          'geofield_map_baselayers_physical' => 0,
          'geofield_map_baselayers_satellite' => 1,
          'geofield_map_center' => array(
            'lat' => 0,
            'lon' => 0,
          ),
          'geofield_map_controltype' => 'default',
          'geofield_map_draggable' => 0,
          'geofield_map_height' => '300px',
          'geofield_map_maptype' => 'map',
          'geofield_map_max_zoom' => 0,
          'geofield_map_min_zoom' => 0,
          'geofield_map_mtc' => 'standard',
          'geofield_map_overview' => 0,
          'geofield_map_overview_opened' => 0,
          'geofield_map_pancontrol' => 1,
          'geofield_map_scale' => 0,
          'geofield_map_scrollwheel' => 0,
          'geofield_map_streetview_show' => 0,
          'geofield_map_width' => '100%',
          'geofield_map_zoom' => 8,
        ),
        'type' => 'geofield_map_map',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_position_place',
    'label' => 'Position',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'addressfield_autocomplete',
      'settings' => array(
        'addressfield_autocomplete_field' => 'field_address_place',
        'delta_handling' => 'default',
      ),
      'type' => 'addressfield_autocomplete_latlng',
      'weight' => 36,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Address');
  t('Facilities');
  t('Image');
  t('Notes');
  t('Position');
  t('Tell us about this place!');

  return $field_instances;
}
