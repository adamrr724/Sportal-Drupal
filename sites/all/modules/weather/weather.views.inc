<?php

/**
 * @file
 * Views integration for weather module
 *
 * Copyright © 2013-2015 Dr. Tobias Quathamer <t.quathamer@mailbox.org>
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
 * Implement hook_views_data().
 */
function weather_views_data() {
  return array(
    'weather_places' => array(
      // Definitions for table
      'table' => array(
        'group' => t('Weather'),
        'base' => array(
          'field' => 'geoid',
          'title' => t('Weather'),
          'help' => t('Display weather conditions and forecasts from all over the world.'),
        ),
      ),
      // Following are the definitions for table fields.
      'geoid' => array(
        'title' => t('GeoID'),
        'help' => t('GeoID of the weather station.'),
        'field' => array(
          'handler' => 'views_handler_field',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
      ),
      'latitude' => array(
        'title' => t('Latitude'),
        'help' => t('Latitude of weather station.'),
        'field' => array(
          'handler' => 'views_handler_field_numeric',
        ),
      ),
      'longitude' => array(
        'title' => t('Longitude'),
        'help' => t('Longitude of weather station.'),
        'field' => array(
          'handler' => 'views_handler_field_numeric',
        ),
      ),
      'country' => array(
        'title' => t('Country'),
        'help' => t('Country of weather station.'),
        'field' => array(
          'handler' => 'views_handler_field',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
      ),
      'name' => array(
        'title' => t('Name'),
        'help' => t('Name of weather station.'),
        'field' => array(
          'handler' => 'views_handler_field',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
      ),
    ),
    'weather_forecasts' => array(
      'table' => array(
        'group' => t('Weather'),
        'join' => array(
          'weather_places' => array(
            'left_field' => 'geoid',
            'field' => 'geoid',
          ),
        ),
      ),
      'time_from' => array(
        'title' => t('Start time'),
        'help' => t('The time from when the forecast is valid.'),
        'field' => array(
          'handler' => 'weather_handler_date',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_date',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),
      'time_to' => array(
        'title' => t('End time'),
        'help' => t('The time until when the forecast is valid.'),
        'field' => array(
          'handler' => 'weather_handler_date',
        ),
      ),
      'period' => array(
        'title' => t('Period of day'),
        'help' => t('The day period (0-3) of the forecast.'),
        'field' => array(
          'handler' => 'views_handler_field',
        ),
      ),
      'symbol' => array(
        'title' => t('Symbol'),
        'help' => t('Symbol for weather display, matches the condition.'),
        'field' => array(
          'handler' => 'weather_handler_condition',
        ),
      ),
      'condition' => array(
        'title' => t('Condition'),
        'help' => t('Condition for weather display, matches the symbol.'),
        'real field' => 'symbol',
        'field' => array(
          'handler' => 'weather_handler_condition',
        ),
      ),
      'precipitation' => array(
        'title' => t('Precipitation'),
        'help' => t('Amount of precipitation in mm.'),
        'field' => array(
          'handler' => 'weather_handler_precipitation',
        ),
      ),
      'wind' => array(
        'title' => t('Wind'),
        'help' => t('Wind information (direction and speed).'),
        'real field' => 'wind_direction',
        'field' => array(
          'handler' => 'weather_handler_wind',
        ),
      ),
      'wind_direction' => array(
        'title' => t('Wind direction'),
        'help' => t('Wind direction in degrees.'),
        'field' => array(
          'handler' => 'weather_handler_wind_direction',
        ),
      ),
      'wind_speed' => array(
        'title' => t('Wind speed'),
        'help' => t('Wind speed in m/s.'),
        'field' => array(
          'handler' => 'weather_handler_wind_speed',
        ),
      ),
      'temperature' => array(
        'title' => t('Temperature'),
        'help' => t('Temperature in degree celsius.'),
        'field' => array(
          'handler' => 'weather_handler_temperature',
        ),
      ),
      'pressure' => array(
        'title' => t('Pressure'),
        'help' => t('Pressure in hPa.'),
        'field' => array(
          'handler' => 'weather_handler_pressure',
        ),
      ),
    ),
    'weather_forecast_information' => array(
      'table' => array(
        'group' => t('Weather'),
        'join' => array(
          'weather_places' => array(
            'left_field' => 'geoid',
            'field' => 'geoid'
          ),
        ),
      ),
      'utc_offset' => array(
        'title' => t('UTC offset'),
        'help' => t('UTC offset in minutes.'),
        'field' => array(
          'handler' => 'weather_handler_utc_offset',
        ),
      ),
    ),
  );
}

/**
 * Implement hook_views_pre_execute().
 *
 * @param $view
 */
function weather_views_pre_execute(&$view) {
  // Check if the view uses the weather places table
  if ($view->base_table == 'weather_places') {
    // Clone the current query for modification
    $current_query = &$view->build_info['query'];
    $new_query = clone $current_query;
    // Ensure that the geoid is included in the query. If it was
    // included already, this alias will be changed to weather_places_geoid_2.
    $new_query->addField('weather_places', 'geoid', 'weather_places_geoid');
    $result = $new_query->execute();
    $geoids = array();
    foreach ($result as $row) {
      $geoids[] = $row->weather_places_geoid;
    }
    // Reduce the geoids to unique values
    $geoids = array_unique($geoids);
    sort($geoids);
    // Get all geoids with current forecasts (no download needed).
    $time = variable_get('weather_time_for_testing', REQUEST_TIME);
    $current_utc_time = gmdate('Y-m-d H:i:s', $time);
    $current_forecasts = db_query(
      'SELECT * FROM {weather_forecast_information} WHERE geoid IN (:geoids) AND next_download_attempt > :current_utc_time',
      array(':geoids' => $geoids, ':current_utc_time' => $current_utc_time)
    );
    // Construct an array with geoids with current forecasts
    $no_download_needed = array();
    foreach ($current_forecasts as $current_forecast) {
      $no_download_needed[] = $current_forecast->geoid;
    }
    // Get all geoids which need a download
    $need_downloads = array_diff($geoids, $no_download_needed);
    module_load_include('inc', 'weather', 'weather.common');
    // Use at most three download attempts.
    $download_counter = 0;
    foreach ($need_downloads as $geoid) {
      weather_get_weather($geoid);
      $download_counter++;
      if ($download_counter >= 3) {
        break;
      }
    }
  }
}
