<?php

/**
 * @file
 * Common functions in a separate file to reduce size of weather.module.
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
 * Display a detailed weather forecast for a given place.
 * 
 * @param string $country
 *   Country of place.
 * @param string $link
 *   Link of place, as in the database.
 *   The link may contain an appended slash with more information about
 *   the display configuration.
 */
function weather_show_detailed_forecast($country, $link) {
  global $user;
  // If the last part of the link contains an appended slash
  // and a number, this indicates the display configuration of
  // the system-wide display with the given number.
  $display_type = 'default';
  $display_number = 0;
  $link_parts = explode('/', $link);
  $last_link_element = array_pop($link_parts);
  // Examine the last element of the link.
  if (preg_match('/^[0-9]+$/', $last_link_element)) {
    // Only digits, remove that part from the link.
    $link = join('/', $link_parts);
    // Use the system-wide display with the given number.
    $display_type = 'system-wide';
    $display_number = $last_link_element;
  }
  elseif ($last_link_element == 'u') {
    // Only the letter 'u', remove that part from the link.
    $link = join('/', $link_parts);
    // Use the user's custom display.
    $display_type = 'user';
    $display_number = $user->uid;
  }
  // See if there is a matching place in the database.
  $sql = db_select('weather_places')
    ->fields('weather_places', array('geoid', 'country', 'name', 'link'))
    ->orderBy('name', 'ASC');
  $and = db_and()
    ->where('UPPER(country) LIKE UPPER(:country)', array(':country' => $country))
    ->where('UPPER(link) LIKE UPPER(:link)', array(':link' => $link));
  $sql->condition($and);
  $place = $sql->execute()->fetchObject();
  if ($place !== FALSE) {
    $name = $place->name;
    // Check proper permission for access:
    // If the place is already configured in a display, the user wants
    // to see the detailed forecast of a display and just needs the
    // permission 'access content'. This is checked in weather_menu().
    // If the place is not configured in a display, this equals a
    // search for a place. This need the permission 'access weather search page'.
    $configured = db_query(
      'SELECT * FROM {weather_displays_places} WHERE place_geoid = :geoid',
      array(':geoid' => $place->geoid)
    )->fetchObject();
    if ($configured === FALSE) {
      if (!user_access('access weather search page')) {
        return MENU_ACCESS_DENIED;
      }
    }
    else {
      $name = $configured->displayed_name;
    }
    $display = weather_get_display_config($display_type, $display_number);
    $display->detailed = TRUE;
    $forecasts = weather_get_weather($place->geoid, 0, $display->detailed);
    $weather[0]['forecasts'] = $forecasts['forecasts'];
    $weather[0]['utc_offset'] = $forecasts['utc_offset'];
    $weather[0]['name'] = $name;
    $weather[0]['geoid'] = $place->geoid;
    $weather[0]['yr.no'] = _weather_get_link_for_geoid($place->geoid, 'yr.no');
    return theme('weather_forecast_preprocess',
      array('weather' => $weather, 'display' => $display));
  }
  else {
    // The specified link does not exist in the weather database.
    return MENU_NOT_FOUND;
  }
}

/**
 * Get all currently used displays.
 *
 * @param string $type
 *   Display type.
 *
 * @return array
 *   Array of sorted displays.
 */
function weather_get_displays_in_use($type='system-wide') {
  return db_query('SELECT number FROM {weather_displays} WHERE type=:type ORDER BY number ASC',
    array(':type' => $type))->fetchCol();
}

/**
 * Get all currently used places for a display.
 *
 * @param string $display_type
 *   Display type.
 * @param int $display_number
 *   Display number.
 *
 * @return array
 *   Array of sorted places.
 */
function weather_get_places_in_use($display_type, $display_number) {
  $result = db_query('SELECT * FROM {weather_displays_places}
    WHERE display_type=:type AND display_number=:number ORDER BY weight ASC, displayed_name ASC',
    array(':type' => $display_type, ':number' => $display_number));
  if ($result->rowCount() == 0) {
    $result = NULL;
  }
  return $result;
}

/**
 * Return display configuration for a specific display.
 *
 * If there is no configuration yet, get the default configuration
 * instead.
 *
 * @param string $display_type
 *   Display type.
 * @param int $display_number
 *   Display number.
 *
 * @return
 *   Display configuration.
 */
function weather_get_display_config($display_type, $display_number=NULL) {
  $config = db_query('SELECT * FROM {weather_displays} WHERE type=:type AND number=:number',
    array(':type' => $display_type, ':number' => $display_number))->fetchObject();
  if (empty($config)) {
    // There is no specific configuration. Try to get custom default configuration.
    $config = db_query('SELECT * FROM {weather_displays} WHERE type=\'default\'')
      ->fetchObject();
    if (empty($config)) {
      // There is no custom default configuration. Get module's default configuration.
      $config = new stdClass();
      $config->config = array(
        'temperature' => 'celsius',
        'windspeed' => 'kmh',
        'pressure' => 'hpa',
        'distance' => 'kilometers',
        'show_sunrise_sunset' => FALSE,
        'show_windchill_temperature' => FALSE,
        'show_abbreviated_directions' => FALSE,
        'show_directions_degree' => FALSE,
      );
    }
    else {
      // Convert custom default configuration.
      $config->config = unserialize($config->config);
    }
  }
  else {
    // Convert specified configuration.
    $config->config = unserialize($config->config);
  }
  return $config;
}

/**
 * Get information about a GeoID.
 *
 * @param string $wanted_geoid
 *   GeoID.
 *
 * @return object
 *   The information about the GeoID or FALSE.
 */
function weather_get_information_about_geoid($wanted_geoid) {
  return db_query('SELECT * FROM {weather_places} WHERE geoid=:geoid',
    array(':geoid' => $wanted_geoid))->fetchObject();
}

/**
 * Construct the link for the given GeoID.
 * 
 * @param string $geoid
 *   The GeoID to construct the link for.
 * @param string $destination
 *   Destination to create the link for. Currently supported are
 *   'system-wide', 'default', 'user', 'yr', and 'autocomplete'.
 * @param int $number
 *   Optional number of display. Applies only to 'system-wide'.
 * 
 * @return string
 *   The link for the GeoID.
 */
function _weather_get_link_for_geoid($geoid, $destination, $number=1) {
  $info = weather_get_information_about_geoid($geoid);
  // Conversion rules for all link parts:
  // - Replace all spaces with an underscore.
  // - If the link part ends with a dot, use an underscore.
  $country = str_replace(' ', '_', $info->country);
  if (substr($country, -1) == '.') {
    $country[strlen($country) - 1] = '_';
  }
  $link = $country . '/' . $info->link;
  switch ($destination) {
    case 'system-wide':
      $link = 'weather/' . $link . '/' . $number;
      break;
    case 'default':
      $link = 'weather/' . $link;
      break;
    case 'user':
      $link = 'weather/' . $link . '/u';
      break;
    case 'yr':
      // Encode special characters except the '/' in the URL.
      // Otherwise, the request will fail on yr.no.
      $link = rawurlencode($link);
      $link = str_replace('%2F', '/', $link);
      $link = 'http://www.yr.no/place/' . $link . '/forecast.xml';
      break;
    case 'yr.no':
      $link = 'http://www.yr.no/place/' . $link . '/';
      break;
    case 'autocomplete':
      // Nothing to do here.
      break;
  }
  return $link;
}

/**
 * Return ICAO code of the nearest weather station.
 *
 * The distance calculation is based on the spherical law of cosines.
 * The bearing is converted from radians to degrees and normalized to
 * be between 0 and 360 degress. The returned value will range from
 * -180° to 180°.
 * All angles must be passed in radians for the trigonometry functions.
 *
 * R = Earth's radius (using a mean radius of 6371 km)
 * distance = R * acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2)
 *                     * cos(long2 - long1))
 * bearing = atan2(sin(long2 - long1) * cos(lat2),
 *                 cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2)
 *                 * cos(long2- long1))
 *
 * Note: The radius of the earth is multiplied by 10; afterwards, the
 * distance is divided by 10 again. This is because of an implementation
 * detail of ROUND() in PostgreSQL, see #1268844. On MySQL, this results
 * in four digits after the decimal point, so a truncation is necessary.
 *
 * The CAST(... AS DECIMAL) is necessary for calling the MOD()
 * function in PostgreSQL, see also #1268844.
 *
 * @param float $latitude
 *   Latitude to be searched.
 * @param float $longitude
 *   Longitude to be searched.
 *
 * @return object
 *   Object with ICAO code, name, distance, and bearing.
 */
function weather_get_nearest_station($latitude, $longitude) {
  $sql = "SELECT geoid, name AS displayed_name,
    ROUND(63710 *
      ACOS(
        SIN(RADIANS(:lat)) * SIN(RADIANS(latitude)) +
        COS(RADIANS(:lat)) * COS(RADIANS(latitude)) * COS(RADIANS(longitude - :long))
      )) AS distance,
    MOD(
      CAST(ROUND(
        DEGREES(
          ATAN2(
            SIN(RADIANS(longitude - :long)) * COS(RADIANS(latitude)),
            COS(RADIANS(:lat)) * SIN(RADIANS(latitude)) - SIN(RADIANS(:lat)) * COS(RADIANS(latitude)) * COS(RADIANS(longitude - :long))
          )
        )
      ) AS DECIMAL) + 360, 360
    ) AS bearing
    FROM {weather_places} ORDER BY distance, displayed_name";
  $result = db_query($sql, array(':lat' => $latitude, ':long' => $longitude))->fetchObject();
  // This cannot be done in the SQL query, because MySQL would return
  // four digits after the decimal point, resulting in an ugly display.
  $result->distance = $result->distance / 10;
  return $result;
}

/**
 * Returns a weather object for the specified GeoID.
 * 
 * @param string $geoid
 *   GeoID of the place for which the weather is desired.
 * @param int $days
 *   Return weather for specified number of days (0 = all available days).
 * @param bool $detailed
 *   Return detailed forecasts or just one forecast per day.
 * 
 * @return array
 *   Weather array with forecast information.
 */
function weather_get_weather($geoid, $days=0, $detailed=TRUE) {
  // Support testing of module with fixed times instead of current time.
  $time = variable_get('weather_time_for_testing', REQUEST_TIME);
  module_load_include('inc', 'weather', 'weather_parser');
  // Get the scheduled time of next update. If there is no entry for
  // the specified GeoID, $meta will be FALSE.
  $meta = db_query(
    'SELECT * FROM {weather_forecast_information} WHERE geoid = :geoid',
    array(':geoid' => $geoid)
  )->fetchAssoc();
  $current_utc_time = gmdate('Y-m-d H:i:s', $time);
  // If the next scheduled download is due, try to get forecasts.
  if ($current_utc_time >= $meta['next_download_attempt']) {
    $result = _weather_download_forecast($geoid);
    // If that worked, get the next scheduled update time.
    $meta = db_query(
      'SELECT * FROM {weather_forecast_information} WHERE geoid = :geoid',
      array(':geoid' => $geoid)
    )->fetchAssoc();
    // If there is no entry yet, set up initial values.
    if ($meta === FALSE) {
      $meta['geoid'] = $geoid;
      $meta['last_update'] = $current_utc_time;
      $meta['next_update'] = $current_utc_time;
      $meta['next_download_attempt'] = $current_utc_time;
      $meta['utc_offset'] = 0;
    }
    // The second check is needed if the download did succeed, but
    // the returned forecast is old and the next update is overdue.
    // In that case, the download attempt needs to wait as well,
    // otherwise, a new download will occur on every page load.
    if (($result == FALSE) or ($current_utc_time >= $meta['next_update'])) {
      // The download did not succeed. Set next download attempt accordingly.
      // Calculate the UTC timestamp.
      $next_update = strtotime($meta['next_update'] . ' UTC');
      // Initial retry after 675 seconds (11.25 minutes).
      // This way, the doubling on the first day leads to exactly 86400
      // seconds (one day) update interval.
      $seconds_to_retry = 675;
      while (($next_update + $seconds_to_retry) <= $time) {
        if ($seconds_to_retry < 86400) {
          $seconds_to_retry = $seconds_to_retry * 2;
        }
        else {
          $seconds_to_retry = $seconds_to_retry + 86400;
        }
      }
      // Finally, calculate the UTC time of the next download attempt.
      $meta['next_download_attempt'] = gmdate('Y-m-d H:i:s', $next_update + $seconds_to_retry);
      // Remove meta information for this location.
      db_delete('weather_forecast_information')
        ->condition('geoid', $meta['geoid'])
        ->execute();
      // Write new entry.
      db_insert('weather_forecast_information')
        ->fields($meta)
        ->execute();
    }
  }
  $return_array['forecasts'] = weather_get_forecasts_from_database($geoid, $meta['utc_offset'], $days, $detailed, $time);
  $return_array['utc_offset'] = $meta['utc_offset'];
  return $return_array;
}
