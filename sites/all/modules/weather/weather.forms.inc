<?php

/**
 * @file
 * Provide forms for configuration of weather displays.
 *
 * Copyright © 2006-2015 Dr. Tobias Quathamer <t.quathamer@mailbox.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/**
 * Show an overview of configured displays and the default display.
 */
function weather_admin_main_page() {
  module_load_include('inc', 'weather', 'weather.common');
  $output = '';
  $path = 'admin/config/user-interface/weather/system-wide/';
  $displays = weather_get_displays_in_use('system-wide');
  if (!empty($displays)) {
    foreach ($displays as $display_number) {
      $header = array(
        l(t('System-wide display (#!number)', array('!number' => $display_number)), $path . $display_number),
        t('Weight'),
      );

      $rows = array();
      $result = db_query("SELECT * FROM {weather_displays_places}
        WHERE display_type='system-wide' AND display_number=:number ORDER BY weight ASC, displayed_name ASC",
        array(':number' => $display_number));
      foreach ($result as $location) {
        $rows[] = array(
          l($location->displayed_name, $path . $display_number . '/' . $location->id . '/edit'),
          $location->weight,
        );
      }
      // Insert link for adding locations into the table as last row.
      $rows[] = array(array(
        'data' => l(t('Add location to this display'), $path . $display_number . '/add'),
        'colspan' => 2,
      ));

      $output .= theme('table', array('header' => $header, 'rows' => $rows));
      if (isset($form['pager']['#value'])) {
        $output .= drupal_render($form['pager']);
      }
    }
  }
  $form = drupal_get_form('weather_admin_main_page_form');
  $output .= drupal_render($form);
  return $output;
}

/**
 * Construct a form for general settings of the Weather module
 */
function weather_admin_main_page_form() {
  // Determine the active theme path.
  $theme_path = drupal_get_path('theme', variable_get('theme_default', NULL));
  $form['weather_image_directory'] = array(
    '#type' => 'textfield',
    '#title' => t('Directory for custom images'),
    '#description' => t('Use custom images for displaying weather conditions. The name of this directory can be chosen freely. It will be searched in your active theme (currently %theme_path).',
      array('%theme_path' => $theme_path)),
    '#default_value' => variable_get('weather_image_directory', ''),
  );
  $form['weather_forecast_days'] = array(
    '#type' => 'select',
    '#title' => t('Number of forecast days'),
    '#description' => t('You can configure the number of days for the forecast displays in blocks.'),
    '#default_value' => variable_get('weather_forecast_days', '2'),
    '#options' => drupal_map_assoc(array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14)),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;
}

/**
 * Handle the submission for general settings of the Weather module
 */
function weather_admin_main_page_form_submit($form, &$form_state) {
  $directory = $form_state['values']['weather_image_directory'];
  // Remove whitespace and directory separators from the string.
  $directory = trim(trim($directory, '/\\'));
  // Replace Windows-style directory separators with Unix separators
  $directory = implode('/', explode('\\', $directory));
  variable_set('weather_image_directory', $directory);
  variable_set('weather_forecast_days', $form_state['values']['weather_forecast_days']);
  drupal_set_message(t('The configuration has been saved.'));
}

/**
 * Show an overview of all modified places.
 */
function weather_admin_places() {
  $output = '';
  // Create form for adding places
  $form = drupal_get_form('weather_admin_places_form');
  $output .= drupal_render($form);
  // Create tables for modified places
  $tables = array(
    'added' => t('Added places'),
    'modified' => t('Modified places'),
  );
  foreach ($tables as $status => $caption) {
    $header = array(t('GeoID'), t('Latitude'), t('Longitude'),
      t('Country'), t('Name'), t('Link')
    );
    $rows = array();
    $result = db_query('SELECT * FROM {weather_places}
      WHERE status = :status ORDER BY country ASC, name ASC',
      array(':status' => $status)
    );
    foreach ($result as $place) {
      $rows[] = array(
        $place->geoid,
        $place->latitude,
        $place->longitude,
        $place->country,
        $place->name,
        $place->link,
      );
    }
    $output .= theme('table', array(
      'header' => $header,
      'rows' => $rows,
      'caption' => $caption,
      'empty' => t('No places.'),
    ));
  }
  return $output;
}

/**
 * Construct a form for place additions of the Weather module
 */
function weather_admin_places_form() {
  $form['weather_yrno_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL of English weather forecast on yr.no'),
    '#description' => t('Example: http://www.yr.no/place/Germany/Hamburg/Hamburg/.'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save place'),
  );
  return $form;
}

/**
 * Handle the submission of a new place
 */
function weather_admin_places_form_submit($form, &$form_state) {
  module_load_include('inc', 'weather', 'weather_parser');
  $url = $form_state['values']['weather_yrno_url'];
  // Remove whitespace from the string.
  $url = trim($url);
  // Check for the english version
  if (substr($url, 0, 23) != 'http://www.yr.no/place/') {
    drupal_set_message(t('Please make sure to use the English version of the forecast, starting with "http://www.yr.no/<strong>place</strong>/".'), 'error');
    return;
  }
  // Ensure that the link is not known yet.
  // Remove "http://www.yr.no/place/" from the URL
  $link = substr($url, 23);
  // Remove trailing slash
  $link = trim($link, '/');
  // Split by slashes and remove country (first item)
  $link_parts = explode('/', $link);
  // Remove country
  $country = array_shift($link_parts);
  $link = implode('/', $link_parts);
  $result = db_query('SELECT * FROM {weather_places} WHERE country = :country AND link = :link',
    array(':country' => $country, ':link' => $link))->fetchObject();
  if ($result) {
    drupal_set_message(t('The place is already in the database.'), 'error');
    return;
  }
  $url .= 'forecast.xml';
  // Try to fetch the forecast, timeout 10 seconds.
  $response = drupal_http_request($url, array('timeout' => 10));
  // Extract XML data from the received forecast.
  if (!isset($response->error)) {
    if (_weather_parse_forecast($response->data)) {
      drupal_set_message(t('The new place has been saved.'));
      return;
    }
  }
  drupal_set_message(t('The download from the given URL did not succeed.'), 'error');
}

/**
 * Show an overview of configured places for a user.
 *
 * @param int $uid
 *   The ID of the user.
 *
 * @return string
 *   Themed output of all places for the given user.
 */
function weather_user_main_page($uid) {
  $header = array(
    t('Displayed name'),
    t('Weight')
  );
  $path = 'user/' . $uid . '/weather/';
  $rows = array();
  $result = db_query('SELECT * FROM {weather_displays_places}
    WHERE display_type=:type AND display_number=:number ORDER BY weight ASC, displayed_name ASC',
    array(':type' => 'user', ':number' => $uid));
  foreach ($result as $location) {
    $rows[] = array(
      l($location->displayed_name, $path . $location->id),
      $location->weight
    );
  }
  // Insert link for adding locations into the table as last row.
  $rows[] = array(array(
    'data' => l(t('Add location to this display'), $path . 'add'),
    'colspan' => 2,
  ));
  $output = theme('table', array('header' => $header, 'rows' => $rows));
  if (isset($form['pager']['#value'])) {
    $output .= drupal_render($form['pager']);
  }
  $output .= '<p>' . l(t('Edit configuration of display'),
    $path . 'display') . '</p>';
  return $output;
}

/**
 * Create a configuration form for a weather display.
 *
 * @param string $display_type
 *   Type of the display (for example, system-wide, user, location, ...).
 * @param string $display_number
 *   Number of the display or NULL.
 *
 * @return array
 *   Form array for the weather display.
 */
function weather_display_config_form($form, &$form_state, $display_type, $display_number=NULL) {
  module_load_include('inc', 'weather', 'weather.common');
  $mode = 'edit';
  if ($display_number == 'add') {
    // Preserve the mode for this form.
    $mode = 'add';
    $display_number = NULL;
  }
  if ($display_type == 'default') {
    $mode = 'default';
    $display_number = 1;
  }
  $config = weather_get_display_config($display_type, $display_number);
  // Prevent users from entering arbitrary system-wide display numbers:
  // If the user entered a non-existant number, $config->number will be empty.
  if ($display_type == 'system-wide' and empty($config->number)) {
    $mode = 'add';
    $display_number = NULL;
  }
  $form['config'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display configuration'),
    '#description' => t('Customize the weather display.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  );
  $form['config']['temperature'] = array(
    '#type' => 'select',
    '#title' => t('Temperature'),
    '#description' => t('Unit for displaying temperatures.'),
    '#default_value' => $config->config['temperature'],
    '#options' => array('celsius' => t('Celsius'), 'fahrenheit' => t('Fahrenheit'),
      'celsiusfahrenheit' => t('Celsius / Fahrenheit'),
      'fahrenheitcelsius' => t('Fahrenheit / Celsius'),
    ),
  );
  $form['config']['windspeed'] = array(
    '#type' => 'select',
    '#title' => t('Wind speed'),
    '#description' => t('Unit for displaying wind speeds.'),
    '#default_value' => $config->config['windspeed'],
    '#options' => array('kmh' => t('km/h'), 'mph' => t('mph'), 'knots' => t('Knots'),
      'mps' => t('meter/s'), 'beaufort' => t('Beaufort'),
    ),
  );
  $form['config']['pressure'] = array(
    '#type' => 'select',
    '#title' => t('Pressure'),
    '#description' => t('Unit for displaying pressure.'),
    '#default_value' => $config->config['pressure'],
    '#options' => array('hpa' => t('hPa'), 'kpa' => t('kPa'), 'inhg' => t('inHg'), 'mmhg' => t('mmHg'),
    ),
  );
  $form['config']['distance'] = array(
    '#type' => 'select',
    '#title' => t('Distance'),
    '#description' => t('Unit for displaying distances.'),
    '#default_value' => $config->config['distance'],
    '#options' => array('kilometers' => t('Kilometers'), 'miles' => t('UK miles')),
  );
  $form['config']['show_sunrise_sunset'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show times of sunrise and sunset'),
    '#default_value' => $config->config['show_sunrise_sunset'],
    '#description' => t('Displays the times of sunrise and sunset. This is always the local time.'),
  );
  $form['config']['show_windchill_temperature'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show windchill temperature'),
    '#default_value' => $config->config['show_windchill_temperature'],
    '#description' => t('Displays the windchill temperature. This is how the temperature <q>feels like</q>. Note that windchill temperature is only defined for temperatures below 10 °C (50 °F) and wind speeds above 1.34 m/s (3 mph).'),
  );
  $form['config']['show_abbreviated_directions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show abbreviated wind directions'),
    '#default_value' => $config->config['show_abbreviated_directions'],
    '#description' => t('Displays abbreviated wind directions like N, SE, or W instead of North, Southeast, or West.'),
  );
  $form['config']['show_directions_degree'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show degrees of wind directions'),
    '#default_value' => $config->config['show_directions_degree'],
    '#description' => t('Displays the degrees of wind directions, for example, North (20°).'),
  );
  $form['type'] = array(
    '#type' => 'value',
    '#value' => $display_type,
  );
  $form['number'] = array(
    '#type' => 'value',
    '#value' => $display_number,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  // Do not show the 'delete' button if not in 'edit' mode.
  if ($mode == 'edit') {
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('weather_display_delete_submit'),
    );
  }
  // Show a 'reset' button if editing the default display.
  if ($mode == 'default') {
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Reset'),
      '#submit' => array('weather_display_delete_confirm_submit'),
    );
  }
  return $form;
}

/**
 * Implement hook_form_submit().
 */
function weather_display_config_form_submit($form, &$form_state) {
  if ($form_state['values']['number'] == NULL) {
    module_load_include('inc', 'weather', 'weather.common');
    // The number does not exist, so insert a new entry.
    $used_numbers = weather_get_displays_in_use($form_state['values']['type']);
    $free_number = 1;
    foreach ($used_numbers as $number) {
      if ($number > $free_number) {
        break;
      }
      else {
        $free_number++;
      }
    }
    db_insert('weather_displays')
      ->fields(array(
        'type' => $form_state['values']['type'],
        'number' => $free_number,
        'config' => serialize($form_state['values']['config']),
      ))
      ->execute();
  }
  else {
    // The number already exists, so overwrite the entry.
    db_merge('weather_displays')
      ->key(array(
        'type' => $form_state['values']['type'],
        'number' => $form_state['values']['number']
      ))
      ->fields(array(
        'config' => serialize($form_state['values']['config']),
      ))
      ->execute();
  }
  if ($form_state['values']['type'] == 'user') {
    $path = 'user/' . $form_state['values']['number'] . '/weather';
  }
  else {
    $path = 'admin/config/user-interface/weather';
  }
  $form_state['redirect'] = $path;
}

/**
 * Implement hook_form_submit().
 */
function weather_display_delete_submit($form, &$form_state) {
  if ($form_state['values']['type'] == 'user') {
    $path = 'user/' . $form_state['values']['number'] . '/weather/display/delete';
  }
  else {
    $path = 'admin/config/user-interface/weather/system-wide/' . $form_state['values']['number'] . '/delete';
  }
  $form_state['redirect'] = $path;
}

/**
 * Generate a confirmation form before deleting.
 */
function weather_display_delete_confirm($form, &$form_state, $display_type, $display_number) {
  $form['type'] = array(
    '#type' => 'value',
    '#value' => $display_type,
  );
  $form['number'] = array(
    '#type' => 'value',
    '#value' => $display_number,
  );
  if ($display_type == 'user') {
    $question = t('Are you sure you want to delete your custom display?');
    $return_path = 'user/' . $display_number . '/weather';
  }
  else {
    $question = t('Are you sure you want to delete display #@number?',
      array('@number' => $display_number));
    $return_path = 'admin/config/user-interface/weather';
  }
  return confirm_form($form, $question, $return_path, NULL, t('Delete'));
}

/**
 * Implement actual deletion of display.
 */
function weather_display_delete_confirm_submit($form, &$form_state) {
  // Delete associated locations.
  db_delete('weather_displays_places')
    ->condition('display_type', $form_state['values']['type'])
    ->condition('display_number', $form_state['values']['number'])
    ->execute();
  // Delete actual display.
  db_delete('weather_displays')
    ->condition('type', $form_state['values']['type'])
    ->condition('number', $form_state['values']['number'])
    ->execute();
  if ($form_state['values']['type'] == 'user') {
    $path = 'user/' . $form_state['values']['number'] . '/weather';
  }
  else {
    $path = 'admin/config/user-interface/weather';
  }
  $form_state['redirect'] = $path;
}

/**
 * Return location settings for a specific id.
 *
 * If there are no settings yet, get the default settings instead.
 *
 * @param int $id
 *   ID of table weather_displays_places.
 *
 * @return
 *   Location configuration.
 */
function weather_get_location_settings($id) {
  $settings = db_query('SELECT * FROM {weather_displays_places} WHERE id=:id',
    array(':id' => $id))->fetchObject();
  if (empty($settings)) {
    // There are no settings. Get module's default settings.
    $settings = new stdClass();
    $settings->place_geoid = 'geonames_2911298';
    $settings->displayed_name = 'Hamburg';
    $settings->weight = 0;
    $settings->country = 'Germany';
  }
  else {
    module_load_include('inc', 'weather', 'weather.common');
    $info = weather_get_information_about_geoid($settings->place_geoid);
    $settings->country = $info->country;
  }
  return $settings;
}

/**
 * Get all places for a country.
 *
 * @param string $country
 *   Country for which the placed should be returned.
 *
 * @return array
 *   Array of sorted places.
 */
function weather_get_places($country) {
  $result = db_query('SELECT geoid, name FROM {weather_places} WHERE country=:country ORDER BY name ASC',
    array(':country' => $country));
  foreach ($result as $row) {
    $places[$row->geoid] = $row->name;
  }
  return $places;
}

/**
 * Create a form for a weather place.
 *
 * @param string $id
 *   ID of the place in the table weather_displays_places.
 *
 * @return array
 *   Form array.
 */
function weather_location_settings_form($form, &$form_state, $display_type, $display_number, $id=NULL) {
  $mode = 'edit';
  // Handle the addition of a new place.
  if ($id == 'add') {
    $mode = 'add';
    $id = NULL;
  }
  // If the place exists, get the configuration. If it does not exist,
  // get the default place configuration.
  $settings = weather_get_location_settings($id);
  if (!empty($form_state['values']['country'])) {
    $settings->country = $form_state['values']['country'];
  }
  $settings->places = weather_get_places($settings->country);
  $form['country'] = array(
    '#type' => 'select',
    '#title' => t('Country'),
    '#description' => t('Select a country to narrow down your search.'),
    '#default_value' => $settings->country,
    '#options' => drupal_map_assoc(weather_get_countries()),
    '#ajax' => array(
      'callback' => 'weather_location_settings_form_country_callback',
      'wrapper' => 'weather_place_replace',
    ),
  );
  $form['place'] = array(
    '#type' => 'select',
    '#title' => t('Place'),
    '#description' => t('Select a place in that country for the weather display.'),
    '#default_value' => $settings->place_geoid,
    '#options' => $settings->places,
    '#prefix' => '<div id="weather_place_replace">',
    '#ajax' => array(
      'callback' => 'weather_location_settings_form_place_callback',
      'wrapper' => 'weather_displayed_name_replace',
    ),
  );
  $form['displayed_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Displayed name for the selected place'),
    '#default_value' => $settings->displayed_name,
    '#description' => t('You may enter another name for the place selected above.'),
    '#required' => TRUE,
    '#size' => '30',
    '#prefix' => '<div id="weather_displayed_name_replace">',
    '#suffix' => '</div></div>',
  );
  $form['weight'] = array(
    '#type' => 'weight',
    '#title' => t('Weight'),
    '#default_value' => $settings->weight,
    '#description' => t('Optional. In the block, the heavier locations will sink and the lighter locations will be positioned nearer the top. Locations with equal weights are sorted alphabetically.'),
  );
  $form['id'] = array(
    '#type' => 'value',
    '#value' => $id,
  );
  $form['display_type'] = array(
    '#type' => 'value',
    '#value' => $display_type,
  );
  $form['display_number'] = array(
    '#type' => 'value',
    '#value' => $display_number,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  // Do not show the 'delete' button if not in 'edit' mode.
  if ($mode == 'edit') {
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('weather_location_delete_submit'),
    );
  }
  // If the form is regenerated during an AJAX callback, get the
  // country selected by the user.
  if (isset($form_state['triggering_element'])) {
    $settings->country = $form_state['values']['country'];
    if ($form_state['triggering_element']['#title'] == t('Country')) {
      $settings->places = weather_get_places($settings->country);
      $settings->place_geoid = key($settings->places);
      $settings->displayed_name = $settings->places[$settings->place_geoid];
      $form['place']['#options'] = $settings->places;
      $form['place']['#value'] = $settings->place_geoid;
      $form['displayed_name']['#value'] = $settings->displayed_name;
    }
    if ($form_state['triggering_element']['#title'] == t('Place')) {
      $settings->displayed_name = $settings->places[$form_state['values']['place']];
      $form['displayed_name']['#value'] = $settings->displayed_name;
    }
  }
  return $form;
}

/**
 * AJAX callback for location settings form.
 */
function weather_location_settings_form_country_callback($form, $form_state) {
  $ret['place'] = $form['place'];
  $ret['displayed_name'] = $form['displayed_name'];
  return $ret;
}

/**
 * AJAX callback for location settings form.
 */
function weather_location_settings_form_place_callback($form, $form_state) {
  return $form['displayed_name'];
}

/**
 * Implement hook_form_validate().
 */
function weather_location_settings_form_validate($form, &$form_state) {
  module_load_include('inc', 'weather', 'weather.common');
  // Make sure the GeoID is supported by the module.
  if (weather_get_information_about_geoid($form_state['values']['place']) == FALSE) {
    form_set_error('place', t('The place is not supported by this module.'));
  }
}

/**
 * Implement hook_form_submit().
 */
function weather_location_settings_form_submit($form, &$form_state) {
  // Determine whether to insert or update a location.
  $location = (object) $form_state['values'];
  $location->place_geoid = $location->place;
  if ($location->id == NULL) {
    drupal_write_record('weather_displays_places', $location);
  }
  else {
    drupal_write_record('weather_displays_places', $location, 'id');
  }
  if ($location->display_type == 'user') {
    $form_state['redirect'] = 'user/' . $location->display_number . '/weather';
  }
  else {
    $form_state['redirect'] = 'admin/config/user-interface/weather';
  }
}

/**
 * Implement hook_form_submit().
 */
function weather_location_delete_submit($form, &$form_state) {
  if ($form_state['values']['display_type'] == 'user') {
    $path = 'user/' . $form_state['values']['display_number'] . '/weather/' .
      $form_state['values']['id'] . '/delete';
  }
  else {
    $path = 'admin/config/user-interface/weather/system-wide/' .
    $form_state['values']['display_number'] .
    '/' .
    $form_state['values']['id'] .
    '/delete';
  }
  $form_state['redirect'] = $path;
}

/**
 * Generate a confirmation form before deleting.
 */
function weather_location_delete_confirm($form, &$form_state, $location_id) {
  $location = db_query('SELECT * FROM {weather_displays_places} WHERE id=:id',
    array(':id' => $location_id))->fetchObject();
  $form['id'] = array(
    '#type' => 'value',
    '#value' => $location_id,
  );
  $form['display_type'] = array(
    '#type' => 'value',
    '#value' => $location->display_type,
  );
  $form['display_number'] = array(
    '#type' => 'value',
    '#value' => $location->display_number,
  );
  if ($location->display_type == 'user') {
    $return_path = 'user/' . $location->display_number . '/weather';
  }
  else {
    $return_path = 'admin/config/user-interface/weather';
  }
  return confirm_form($form,
    t('Are you sure you want to delete the location %name?',
      array('%name' => $location->displayed_name)),
    $return_path,
    NULL,
    t('Delete')
  );
}

/**
 * Implement actual deletion of location.
 */
function weather_location_delete_confirm_submit($form, &$form_state) {
  db_delete('weather_displays_places')
    ->condition('id', $form_state['values']['id'])
    ->execute();
  if ($form_state['values']['display_type'] == 'user') {
    $path = 'user/' . $form_state['values']['display_number'] . '/weather';
  }
  else {
    $path = 'admin/config/user-interface/weather';
  }
  $form_state['redirect'] = $path;
}

/**
 * Get all countries.
 *
 * @return array
 *   Array of sorted countries.
 */
function weather_get_countries() {
  $result = db_query('SELECT country FROM {weather_places} GROUP BY country ORDER BY country ASC');
  foreach ($result as $row) {
    $countries[] = $row->country;
  }
  return $countries;
}

/**
 * Search for a given location.
 *
 * Searches for the specified location, whether it is a place, country,
 * or part of the link (usually region/province).
 *
 * @param string $search
 *   The argument passed in the URL that specifies the
 *   location which should be searched for.
 */
function weather_search_location($search = NULL) {
  if ($search == NULL) {
    // The user did not enter a search string in the URL, so just
    // display the search form.
    return drupal_get_form('weather_search_form');
  }
  else {
    // Do some sanity checks first.
    if (drupal_strlen($search) < 3) {
      drupal_set_message(t('The string to search for must have at least three characters.'), 'error');
      drupal_goto('weather');
    }
    // Convert input spaces to underscores.
    $search = str_replace(' ', '_', $search);
    // Try to match on GeoID, name, country, or part of the link.
    $locations = array();
    // In this query we search for names, countries, and link parts of locations.
    $sql = db_select('weather_places')
      ->fields('weather_places', array('geoid', 'country', 'name', 'link'))
      ->orderBy('name', 'ASC');
    $or = db_or()
      ->where('UPPER(country) LIKE UPPER(:search)', array(':search' => "%$search%"))
      ->where('UPPER(name) LIKE UPPER(:search)', array(':search' => "%$search%"))
      ->where('UPPER(link) LIKE UPPER(:search)', array(':search' => "%$search%"));
    $sql->condition($or);
    $result = $sql->execute();
    foreach ($result as $location) {
      $locations[] = $location;
    }
    // If there are no results, notify user
    if (empty($locations)) {
      drupal_set_message(t('Your search did not return any results.'), 'error');
      drupal_goto('weather');
    }
    else {
      module_load_include('inc', 'weather', 'weather.common');
      if (count($locations) == 1) {
        $location = $locations[0];
        // There's only one search result, so show the weather by
        // redirecting to the correct URL.
        drupal_goto(_weather_get_link_for_geoid($location->geoid, 'default'));
      }
      else {
        // There is more than one result, so show all of them
        // to let the user decide.
        $links = array();
        foreach ($locations as $location) {
          $search_link = _weather_get_link_for_geoid($location->geoid, 'default');
          $links[] = l($location->name, $search_link);
        }
        $title = t('Search results for <q>@search</q>', array('@search' => $search));
        $output = theme('item_list', array('items' => $links, 'title' => $title));
        $form = drupal_get_form('weather_search_form');
        $output .= drupal_render($form);
        return $output;
      }
    }
  }
}

/**
 * Display a form for the user to search for weather locations.
 */
function weather_search_form($form, &$form_state) {
  $form['search'] = array(
    '#type' => 'textfield',
    '#title' => t('Search for a location'),
    '#description' => t('Type in a name or country to search for weather conditions at that location.'),
    '#autocomplete_path' => 'weather/autocomplete',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
  );
  return $form;
}

/**
 * Validate the input from the weather search form.
 */
function weather_search_form_validate($form, &$form_state) {
  if (drupal_strlen($form_state['values']['search']) < 3) {
    form_set_error('search', t('The string to search for must have at least three characters.'));
  }
}

/**
 * Submission handler for the weather search form.
 *
 * Redirect to the weather URL with the search term added to the end.
 */
function weather_search_form_submit($form, &$form_state) {
  $form_state['redirect'] = 'weather/' . $form_state['values']['search'];
}

/**
 * Search for a place, country, or link parts matching a partial string.
 *
 * @param string $input
 *   The partial text to search for.
 */
function weather_search_autocomplete($input) {
  module_load_include('inc', 'weather', 'weather.common');
  // Convert input spaces to underscores. Note that this is also
  // the wildcard for a single character in SQL.
  $input = str_replace(' ', '_', $input);
  $matches = array();
  // In this query we search for names, countries, and link parts of locations.
  $sql = db_select('weather_places')
    ->fields('weather_places', array('geoid', 'country', 'name', 'link'))
    ->orderBy('name', 'ASC');
  $or = db_or()
    ->where('UPPER(country) LIKE UPPER(:search)', array(':search' => "%$input%"))
    ->where('UPPER(name) LIKE UPPER(:search)', array(':search' => "%$input%"))
    ->where('UPPER(link) LIKE UPPER(:search)', array(':search' => "%$input%"));
  $sql->condition($or);
  $sql->range(0, 10);
  $result = $sql->execute();
  foreach ($result as $match) {
    // Construct a URL for the location.
    $search_link = _weather_get_link_for_geoid($match->geoid, 'autocomplete');
    $matches[$search_link] = $search_link;
  }
  drupal_json_output($matches);
}
