<?php

/**
 * @file
 * Retrieves and parses raw METAR data and stores result in database.
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
 * Try to fetch forecasts from the database.
 *
 * @param string $geoid
 *   GeoID of the place for which the weather is desired.
 * @param string $utc_offset
 *   UTC offset of place in minutes.
 * @param int $days
 *   Return weather for specified number of days (0 = all available days).
 * @param bool $detailed
 *   Return detailed forecasts or just one forecast per day.
 * @param int $time
 *   Timestamp for which the weather should be returned. This is only
 *   needed to enable proper testing of the module.
 * 
 * @return array
 *   Weather array with forecast information.
 */
function weather_get_forecasts_from_database($geoid, $utc_offset, $days, $detailed, $time) {
  // Fetch the first forecast. This must be done separately, because
  // sometimes the first forecast is already on the next day (this can
  // happen e.g. late in the evenings). Otherwise, the calculation of
  // 'tomorrow' would fail.
  $current_local_time = gmdate('Y-m-d H:i:s', $time + $utc_offset * 60);
  $first_forecast = db_query(
    'SELECT * FROM {weather_forecasts} WHERE geoid = :geoid AND time_to >= :current_local_time ORDER BY time_from ASC',
    array(':geoid' => $geoid, ':current_local_time' => $current_local_time))
    ->fetchObject();
  // If there are no forecasts available, return an empty array.
  if ($first_forecast === FALSE) {
    return array();
  }
  $weather = _weather_create_weather_array(array($first_forecast));
  // Calculate tomorrow based on result.
  $first_forecast_day = explode('-', key($weather));
  $tomorrow_local_time = gmdate('Y-m-d H:i:s',
    gmmktime(0, 0, 0, $first_forecast_day[1], $first_forecast_day[2] + 1, $first_forecast_day[0])
  );
  $forecasts_until_local_time = gmdate('Y-m-d 23:59:59',
    gmmktime(23, 59, 59, $first_forecast_day[1], $first_forecast_day[2] + $days - 1, $first_forecast_day[0])
  );
  if ($detailed) {
    // Fetch all available forecasts.
    if ($days > 0) {
      $forecasts = db_query('SELECT * FROM {weather_forecasts} WHERE geoid = :geoid AND time_to >= :current_local_time AND time_from <= :forecasts_until_local_time ORDER BY time_from ASC',
        array(':geoid' => $geoid, ':current_local_time' => $current_local_time, 'forecasts_until_local_time' => $forecasts_until_local_time));
    }
    else {
      $forecasts = db_query('SELECT * FROM {weather_forecasts} WHERE geoid = :geoid AND time_to >= :current_local_time ORDER BY time_from ASC',
        array(':geoid' => $geoid, ':current_local_time' => $current_local_time));
    }
    $weather = _weather_create_weather_array($forecasts);
  }
  else {
    if ($days > 1) {
      $forecasts = db_query(
        'SELECT * FROM {weather_forecasts} WHERE geoid = :geoid AND time_from >= :tomorrow_local_time AND period = \'2\' AND time_from <= :forecasts_until_local_time ORDER BY time_from ASC',
        array(':geoid' => $geoid, ':tomorrow_local_time' => $tomorrow_local_time, 'forecasts_until_local_time' => $forecasts_until_local_time));
      $weather = array_merge($weather, _weather_create_weather_array($forecasts));
    }
    elseif ($days == 0) {
      $forecasts = db_query(
        'SELECT * FROM {weather_forecasts} WHERE geoid = :geoid AND time_from >= :tomorrow_local_time AND period = \'2\' ORDER BY time_from ASC',
        array(':geoid' => $geoid, ':tomorrow_local_time' => $tomorrow_local_time));
      $weather = array_merge($weather, _weather_create_weather_array($forecasts));
    }
  }
  return $weather;
}

/**
 * Create a weather array with the forecast data from database.
 * 
 * @param array $forecasts
 * Raw forecast data from database.
 * 
 * @return array
 * Weather array with forecast information.
 */
function _weather_create_weather_array($forecasts) {
  $weather = array();
  // Cycle through all forecasts and set up a hierarchical array structure
  foreach ($forecasts as $forecast) {
    list($day_from, $time_from) = explode(' ', $forecast->time_from);
    $time_range = substr($time_from, 0, 5);
    list($day_to, $time_to) = explode(' ', $forecast->time_to);
    $time_range .= '-' . substr($time_to, 0, 5);
    $weather[$day_from][$time_range] = array(
      'period' => $forecast->period,
      'symbol' => $forecast->symbol,
      'precipitation' => $forecast->precipitation,
      'wind_direction' => $forecast->wind_direction,
      'wind_speed' => $forecast->wind_speed,
      'temperature' => $forecast->temperature,
      'pressure' => $forecast->pressure,
    );
  }
  return $weather;
}

/**
 * Downloads a new forecast from yr.no.
 * 
 * @param string $geoid
 *   The GeoID for which the forecasts should be downloaded.
 * 
 * @return bool
 *   TRUE on success, FALSE on failure.
 */
function _weather_download_forecast($geoid) {
  // Do not download anything if the variable 'weather_time_for_testing' is set.
  // In this case, we are in testing mode and only load defined
  // forecasts to get always the same results.
  if (variable_get('weather_time_for_testing', REQUEST_TIME) != REQUEST_TIME) {
    $path = drupal_get_path('module', 'weather') . '/tests/data/' . $geoid . '.xml';
    if (is_readable($path)) {
      $xml = file_get_contents($path);
    }
    else {
      $xml = '';
    }
    return _weather_parse_forecast($xml, $geoid);
  }
  // Specify timeout in seconds
  $timeout = 10;
  module_load_include('inc', 'weather', 'weather.common');
  $url = _weather_get_link_for_geoid($geoid, 'yr');
  $response = drupal_http_request($url, array('timeout' => $timeout));
  // Extract XML data from the received forecast.
  if (!isset($response->error)) {
    return _weather_parse_forecast($response->data, $geoid);
  }
  else {
    // Make an entry about this error into the watchdog table.
    watchdog('weather', 'Download of forecast failed: @error',
      array('@error' => $response->error), WATCHDOG_ERROR);
    // Show a message to users with administration priviledges
    if (user_access('administer custom weather block') or user_access('administer site configuration')) {
      drupal_set_message(t('Download of forecast failed: @error',
        array('@error' => $response->error)), 'error');
    }
  }
}

/**
 * Parses an XML forecast supplied by yr.no.
 *
 * @param string $xml
 *   XML to be parsed.
 * @param string $geoid
 *   The GeoID for which the forecasts should be parsed.
 * 
 * @return bool
 *   TRUE on success, FALSE on failure.
 */
function _weather_parse_forecast($xml, $geoid = '') {
  // In case the parsing fails, do not output all error messages.
  $use_errors = libxml_use_internal_errors(TRUE);
  $fc = simplexml_load_string($xml);
  // Restore previous setting of error handling.
  libxml_use_internal_errors($use_errors);
  if ($fc === FALSE) {
    return FALSE;
  }
  // Update weather_places table with downloaded information, if necessary.
  _weather_update_places($fc);
  // Extract meta information.
  // @TODO: Extract GeoID of returned XML data.
  // This might differ from the data we have in the database. An example
  // was Heraklion (ID 261745), which got the forecast for
  // Nomós Irakleíou (ID 261741).
  if ($geoid == '') {
    $geoid = $fc->location->location['geobase'] . "_" . $fc->location->location['geobaseid'];
  }
  $meta['geoid'] = $geoid;
  $meta['utc_offset'] = (int) $fc->location->timezone['utcoffsetMinutes'];
  // Calculate the UTC time.
  $utctime = strtotime((string) $fc->meta->lastupdate . ' UTC') - 60 * $meta['utc_offset'];
  $meta['last_update'] = gmdate('Y-m-d H:i:s', $utctime);
  // Calculate the UTC time.
  $utctime = strtotime((string) $fc->meta->nextupdate . ' UTC') - 60 * $meta['utc_offset'];
  $meta['next_update'] = gmdate('Y-m-d H:i:s', $utctime);
  $meta['next_download_attempt'] = $meta['next_update'];
  // Merge meta information for this location.
  // This prevents an integrity constraint violation, if multiple
  // calls to this function occur at the same time. See bug #1412352
  db_merge('weather_forecast_information')
    ->key(array('geoid' => $meta['geoid']))
    ->fields($meta)
    ->execute();
  // Remove all forecasts for this location.
  db_delete('weather_forecasts')
    ->condition('geoid', $meta['geoid'])
    ->execute();
  // Cycle through all forecasts and write them to the table.
  foreach ($fc->forecast->tabular->time as $time) {
    $forecast = array();
    $forecast['geoid'] = $meta['geoid'];
    $forecast['time_from'] = str_replace('T', ' ', (string) $time['from']);
    $forecast['time_to'] = str_replace('T', ' ', (string) $time['to']);
    $forecast['period'] = (string) $time['period'];
    $forecast['symbol'] = (string) $time->symbol['var'];
    // Remove moon phases, which are not supported.
    // This is in the format "mf/03n.56", where 56 would be the
    // percentage of the moon phase.
    if (strlen($forecast['symbol']) > 3) {
      $forecast['symbol'] = substr($forecast['symbol'], 3, 3);
    }
    $forecast['precipitation'] = (float) $time->precipitation['value'];
    $forecast['wind_direction'] = (int) $time->windDirection['deg'];
    $forecast['wind_speed'] = (float) $time->windSpeed['mps'];
    $forecast['temperature'] = (int) $time->temperature['value'];
    $forecast['pressure'] = (int) $time->pressure['value'];
    // Use db_merge to prevent integrity constraint violation, see above.
    db_merge('weather_forecasts')
      ->key(array('geoid' => $meta['geoid'], 'time_from' => $forecast['time_from']))
      ->fields($forecast)
      ->execute();
  }
  return TRUE;
}

/**
 * Handle updates to the weather_places table.
 */
function _weather_update_places($fc) {
  module_load_include('inc', 'weather', 'weather.common');
  // Extract GeoID and latitude/longitude of returned XML data.
  // This might differ from the data we have in the database. An example
  // was Heraklion (ID 261745), which got the forecast for
  // Nomós Irakleíou (ID 261741).
  // Data to extract are:
  // geoid, latitude, longitude, country, name.
  $place['geoid'] = $fc->location->location['geobase'] . "_" . $fc->location->location['geobaseid'];
  $place['latitude'] = (string) $fc->location->location['latitude'];
  $place['latitude'] = round($place['latitude'], 5);
  $place['longitude'] = (string) $fc->location->location['longitude'];
  $place['longitude'] = round($place['longitude'], 5);
  $place['country'] = (string) $fc->location->country;
  $place['name'] = (string) $fc->location->name;
  $url = (string) $fc->credit->link['url'];
  // Remove "http://www.yr.no/place/" from the URL
  $link = substr($url, 23);
  // Split by slashes and remove country (first item) and "forecast.xml" (last item)
  $link_parts = explode('/', $link);
  // Remove country
  array_shift($link_parts);
  // Remove "forecast.xml"
  array_pop($link_parts);
  $place['link'] = implode('/', $link_parts);
  // Fetch stored information about geoid.
  $info = weather_get_information_about_geoid($place['geoid']);
  // If the geoid is not in the database, add it.
  if ($info === FALSE) {
    $place['status'] = 'added';
    db_insert('weather_places')
      ->fields($place)
      ->execute();
  }
  else {
    // Compare the stored information with the downloaded information.
    // If they differ, update the database.
    $stored_info = (array) $info;
    unset($stored_info['status']);
    $diff = array_diff_assoc($stored_info, $place);
    if (!empty($diff)) {
      $place['status'] = 'modified';
      db_update('weather_places')
        ->condition('geoid', $place['geoid'])
        ->fields($place)
        ->execute();
    }
  }
}
