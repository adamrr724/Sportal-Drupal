<?php

/**
 * @file
 * Prepare themed weather output.
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
 * Custom theme function for preprocessing the weather display.
 */
function theme_weather_forecast_preprocess($variables) {
  $weather = $variables['weather'];
  $display = $variables['display'];
  // Create a result array.
  foreach ($weather as $idx => $place) {
    // Use a day counter to prepend "today" and "tomorrow" to forecast dates.
    $day_counter = 0;
    $forecasts = array();
    foreach ($place['forecasts'] as $date => $time_ranges) {
      $formatted_date = format_date(strtotime($date), 'weather');
      if ($day_counter == 0) {
        $formatted_date = t('Today, @date', array('@date' => $formatted_date));
      }
      elseif ($day_counter == 1) {
        $formatted_date = t('Tomorrow, @date', array('@date' => $formatted_date));
      }
      $forecasts[$date]['formatted_date'] = $formatted_date;
      // Calculate sunrise and sunset information, if desired.
      if ($display->config['show_sunrise_sunset']) {
        $forecasts[$date]['sun_info'] = _weather_calculate_sun_info($date, $place['utc_offset'], $place['geoid']);
      }
      foreach ($time_ranges as $time_range => $data) {
        $condition = weather_format_condition($data['symbol']);
        $forecasts[$date]['time_ranges'][$time_range]['condition'] = $condition;
        $forecasts[$date]['time_ranges'][$time_range]['symbol'] = weather_format_image($data['symbol'], $condition);
        $forecasts[$date]['time_ranges'][$time_range]['temperature'] = weather_format_temperature(
          $data['temperature'], $display->config['temperature']);
        if ($display->config['show_windchill_temperature']) {
          $forecasts[$date]['time_ranges'][$time_range]['windchill'] = weather_format_windchill_temperature(
            $data['temperature'], $data['wind_speed'], $display->config['temperature']);
        }
        $forecasts[$date]['time_ranges'][$time_range]['precipitation'] = t('!precipitation mm',
          array('!precipitation' => $data['precipitation']));
        $forecasts[$date]['time_ranges'][$time_range]['pressure'] = weather_format_pressure(
          $data['pressure'], $display->config['pressure']);
        $forecasts[$date]['time_ranges'][$time_range]['wind'] = weather_format_wind(
          $data['wind_direction'],
          $data['wind_speed'],
          $display->config['windspeed'],
          $display->config['show_abbreviated_directions'],
          $display->config['show_directions_degree']
        );
      }
      $day_counter++;
    }
    $weather[$idx]['forecasts'] = $forecasts;
    if (isset($weather[$idx]['station'])) {
      $weather[$idx]['station'] = weather_format_nearest_station($weather[$idx]['station'], $display);
    }
  }
  if ($display->detailed) {
    return theme('weather_detailed_forecast', array('weather' => $weather));
  }
  else {
    return theme('weather', array('weather' => $weather));
  }
}

/**
 * Returns weather condition as translated text from yr.no symbol number.
 * 
 * @param $condition_no
 * The weather condition number from yr.no
 * 
 * @return $string
 * Translated text with corresponding weather condition
 */
function weather_format_condition($condition_no) {
  // Strip the suffix "d", "n", and "m".
  // (day, night, mørketid -> polar night)
  $condition_no = substr($condition_no, 0, 2);
  switch ($condition_no) {
    case 1:
      $txt = t('Clear sky');
      break;
    case 2:
      $txt = t('Fair');
      break;
    case 3:
      $txt = t('Partly cloudy');
      break;
    case 4:
      $txt = t('Cloudy');
      break;
    case 5:
      $txt = t('Rain showers');
      break;
    case 6:
      $txt = t('Rain showers and thunder');
      break;
    case 7:
      $txt = t('Sleet showers');
      break;
    case 8:
      $txt = t('Snow showers');
      break;
    case 9:
      $txt = t('Rain');
      break;
    case 10:
      $txt = t('Heavy rain');
      break;
    case 11:
      $txt = t('Heavy rain and thunder');
      break;
    case 12:
      $txt = t('Sleet');
      break;
    case 13:
      $txt = t('Snow');
      break;
    case 14:
      $txt = t('Snow and thunder');
      break;
    case 15:
      $txt = t('Fog');
      break;
    case 20:
      $txt = t('Sleet showers and thunder');
      break;
    case 21:
      $txt = t('Snow showers and thunder');
      break;
    case 22:
      $txt = t('Rain and thunder');
      break;
    case 23:
      $txt = t('Sleet and thunder');
      break;
    case 24:
      $txt = t('Light rain showers and thunder');
      break;
    case 25:
      $txt = t('Heavy rain showers and thunder');
      break;
    case 26:
      $txt = t('Light sleet showers and thunder');
      break;
    case 27:
      $txt = t('Heavy sleet showers and thunder');
      break;
    case 28:
      $txt = t('Light snow showers and thunder');
      break;
    case 29:
      $txt = t('Heavy snow showers and thunder');
      break;
    case 30:
      $txt = t('Light rain and thunder');
      break;
    case 31:
      $txt = t('Light sleet and thunder');
      break;
    case 32:
      $txt = t('Heavy sleet and thunder');
      break;
    case 33:
      $txt = t('Light snow and thunder');
      break;
    case 34:
      $txt = t('Heavy snow and thunder');
      break;
    case 40:
      $txt = t('Light rain showers');
      break;
    case 41:
      $txt = t('Heavy rain showers');
      break;
    case 42:
      $txt = t('Light sleet showers');
      break;
    case 43:
      $txt = t('Heavy sleet showers');
      break;
    case 44:
      $txt = t('Light snow showers');
      break;
    case 45:
      $txt = t('Heavy snow showers');
      break;
    case 46:
      $txt = t('Light rain');
      break;
    case 47:
      $txt = t('Light sleet');
      break;
    case 48:
      $txt = t('Heavy sleet');
      break;
    case 49:
      $txt = t('Light snow');
      break;
    case 50:
      $txt = t('Heavy snow');
      break;
    default:
      $txt = t('No data');
  }
  return $txt;
}

/**
 * Returns the <img> tag for the weather image to use for the current condition.
 * 
 * @param $symbol
 *   The weather condition number from yr.no
 * @param $condition
 *   The translated condition text.
 * 
 * @return $string
 *   Ready formatted HTML <img> tag
 */
function weather_format_image($symbol, $condition) {
  // Support a custom image directory. If the variable is not set or the specified
  // file is not available, fall back to the default images of the module.
  // Determine the active theme path.
  $theme_path = drupal_get_path('theme', variable_get('theme_default', NULL));
  $custom_path = $theme_path . '/' . variable_get('weather_image_directory', '') . '/';
  // Construct the filename
  $image = $custom_path . $symbol . '.png';
  if (!is_readable($image)) {
    $default_path = drupal_get_path('module', 'weather') . '/images/';
    $image = $default_path . $symbol . '.png';
  }
  $size = getimagesize($image);
  // Prepare the <img> tag
  return theme('image', array(
    'path' => $image,
    'width' => $size[0],
    'height' => $size[1],
    'alt' => $condition,
    'title' => $condition,
    'attributes' => array('class' => 'weather-image')
  ));
}

/**
 * Converts temperatures.
 *
 * @param int $temperature
 *   Temperature in degree celsius.
 * @param string $unit
 *   Unit to be returned (celsius, fahrenheit, ...).
 *
 * @return string
 *   Formatted representation in the desired unit.
 */
function weather_format_temperature($temperature, $unit) {
  // Do the calculation
  $fahrenheit = (int) ($temperature * 9 / 5) + 32;
  // Format the temperature
  if ($unit == 'fahrenheit') {
    $result = t('!temperature&thinsp;°F', array('!temperature' => $fahrenheit));
  }
  elseif ($unit == 'celsiusfahrenheit') {
    $result = t('!temperature_c&thinsp;°C / !temperature_f&thinsp;°F',
      array(
        '!temperature_c' => $temperature,
        '!temperature_f' => $fahrenheit
      )
    );
  }
  elseif ($unit == 'fahrenheitcelsius') {
    $result = t('!temperature_f&thinsp;°F / !temperature_c&thinsp;°C',
      array(
        '!temperature_f' => $fahrenheit,
        '!temperature_c' => $temperature
      )
    );
  }
  elseif ($unit == 'celsius_value') {
    $result = $temperature;
  }
  elseif ($unit == 'fahrenheit_value') {
    $result = $fahrenheit;
  }
  else {
    // Default to metric units.
    $result = t('!temperature&thinsp;°C', array('!temperature' => $temperature));
  }
  return preg_replace("/([^ ]*)&thinsp;([^ ]*)/",
    '<span style="white-space:nowrap;">\1&thinsp;\2</span>', $result);
}

/**
 * Calculates windchill temperature.
 *
 * Windchill temperature is only defined for temperatures at or below
 * 10 °C (50 °F) and wind speeds above 1.34 m/s (3 mph). Bright sunshine
 * may increase the wind chill temperature.
 * @link http://en.wikipedia.org/wiki/Wind_chill
 *
 * @param int $temperature
 *   Temperature in degree celsius.
 * @param int $wind_speed
 *   Wind speed in m/s.
 * @param string $unit
 *   Unit to be returned (celsius, fahrenheit, ...).
 *
 * @return string
 *   Formatted representation in the desired unit. If the windchill is not
 *   defined for the current conditions, returns NULL.
 */
function weather_format_windchill_temperature($temperature, $wind_speed, $unit) {
  // Set up the empty result, if windchill temperature is not defined
  // for current conditions.
  $result = NULL;
  // First, check conditions for windchill temperature.
  if ($temperature <= 10 and $wind_speed >= 1.34) {
    // Convert wind speed to km/h for formula.
    $wind_speed = $wind_speed * 3.6;
    // Calculate windchill (in degree Celsius).
    // The integer cast is necessary to avoid a result of '-0°C'.
    $windchill = (int) round(13.12 + 0.6215 * $temperature -
      11.37 * pow($wind_speed, 0.16) +
      0.3965 * $temperature * pow($wind_speed, 0.16));
    $result = weather_format_temperature($windchill, $unit);
  }
  return $result;
}

/**
 * Convert wind.
 *
 * @param string $wind_direction
 *   Wind direction (Compass bearings, for example, '080')
 * @param int $wind_speed
 *   Wind speed in m/s.
 * @param string $unit
 *   Unit to be returned (km/h, knots, meter/s, ...).
 * @param array $abbreviated
 *   Whether or not to show abbreviated directions (E, NE, SSW).
 * @param array $exact_degree
 *   Whether or not to show exact compass bearings.
 *
 * @return string
 *   Formatted representation in the desired unit.
 */
function weather_format_wind($wind_direction, $wind_speed, $unit, $abbreviated, $exact_degree) {
  $direction = weather_bearing_to_text($wind_direction, $abbreviated);
  $beaufort = weather_calculate_beaufort($wind_speed);
  // Set up the wind speed.
  $speed = weather_format_wind_speed($wind_speed, $unit);
  if ($exact_degree) {
    $result = t('!description, !speed from !direction (!degree°)',
      array(
        '!description' => $beaufort['description'],
        '!speed' => $speed,
        '!direction' => $direction,
        '!degree' => $wind_direction
      )
    );
  }
  else {
    $result = t('!description, !speed from !direction',
      array(
        '!description' => $beaufort['description'],
        '!speed' => $speed,
        '!direction' => $direction
      )
    );
  }
  return $result;
}

/**
 * Convert wind speed.
 *
 * @param int $wind_speed
 *   Wind speed in m/s.
 * @param string $unit
 *   Unit to be returned (km/h, knots, meter/s, ...).
 *
 * @return string
 *   Formatted representation in the desired unit.
 */
function weather_format_wind_speed($wind_speed, $unit) {
  if ($unit == 'mph') {
    $result = t('!speed&thinsp;mph',
      array('!speed' => round($wind_speed * 2.23694, 1)));
  }
  elseif ($unit == 'mph_value') {
    $result = round($wind_speed * 2.23694, 1);
  }
  elseif ($unit == 'knots') {
    $result = t('!speed&thinsp;knots',
      array('!speed' => round($wind_speed * 1.94384, 1)));
  }
  elseif ($unit == 'knots_value') {
    $result = round($wind_speed * 1.94384, 1);
  }
  elseif ($unit == 'kmh') {
    $result = t('!speed&thinsp;km/h',
      array('!speed' => round($wind_speed * 3.6, 1)));
  }
  elseif ($unit == 'kmh_value') {
    $result = round($wind_speed * 3.6, 1);
  }
  elseif ($unit == 'beaufort') {
    $beaufort = weather_calculate_beaufort($wind_speed);
    $result = t('Beaufort !number',
      array('!number' => $beaufort['number']));
  }
  elseif ($unit == 'beaufort_value') {
    $beaufort = weather_calculate_beaufort($wind_speed);
    $result = $beaufort['number'];
  }
  elseif ($unit == 'mps_value') {
    $result = $wind_speed;
  }
  else {
    // Default to m/s.
    $result = t('!speed&thinsp;meter/s', array('!speed' => $wind_speed));
  }
  return preg_replace("/([^ ]*)&thinsp;([^ ]*)/",
    '<span style="white-space:nowrap;">\1&thinsp;\2</span>', $result);
}

/**
 * Convert wind direction.
 *
 * @param string $wind_direction
 *   Wind direction (Compass bearings, for example, '080')
 * @param array $settings
 *   From views handler: use normal or abbreviated text, show degree.
 *
 * @return string
 *   Formatted representation in the desired unit.
 */
function weather_format_wind_direction($wind_direction, $settings) {
  switch ($settings) {
    case 'normal_degree':
      $result = t('!direction (!degree°)', array(
        '!direction' => weather_bearing_to_text($wind_direction),
        '!degree' => $wind_direction,
      ));
      break;
    case 'abbreviated':
      $result = weather_bearing_to_text($wind_direction, TRUE);
      break;
    case 'abbreviated_degree':
      $result = t('!direction (!degree°)', array(
        '!direction' => weather_bearing_to_text($wind_direction, TRUE),
        '!degree' => $wind_direction,
      ));
      break;
    case 'degree':
      $result = t('!degree°', array('!degree' => $wind_direction));
      break;
    case 'degree_value':
      $result = $wind_direction;
      break;
    default:
      $result = weather_bearing_to_text($wind_direction);
  }
  return $result;
}

/**
 * Converts a compass bearing to a text direction.
 *
 * This function can be used to get a text representation of a compass
 * bearing (for example, 0° North, 86° East, ...).
 *
 * @param string $bearing
 *   Compass bearing in degrees.
 * @param boolean $abbreviated
 *   If true, return abbreviated directions (N, NNW) instead of
 *   full text (North, North-Northwest). Defaults to full text directions.
 *
 * @return string
 *   Formatted representation.
 */
function weather_bearing_to_text($bearing, $abbreviated=FALSE) {
  // Determine the sector. This works for 0° up to 348.75°
  // If the bearing was greater than 348.75°, perform a wrap (%16)
  $sector = floor(($bearing + 11.25) / 22.5) % 16;

  if (!$abbreviated) {
    $direction = array(
      t('North'),
      t('North-Northeast'),
      t('Northeast'),
      t('East-Northeast'),
      t('East'),
      t('East-Southeast'),
      t('Southeast'),
      t('South-Southeast'),
      t('South'),
      t('South-Southwest'),
      t('Southwest'),
      t('West-Southwest'),
      t('West'),
      t('West-Northwest'),
      t('Northwest'),
      t('North-Northwest')
    );
  }
  else {
    $direction = array(
      t('N'),
      t('NNE'),
      t('NE'),
      t('ENE'),
      t('E'),
      t('ESE'),
      t('SE'),
      t('SSE'),
      t('S'),
      t('SSW'),
      t('SW'),
      t('WSW'),
      t('W'),
      t('WNW'),
      t('NW'),
      t('NNW')
    );
  }
  return $direction[$sector];
}

/**
 * Calculate Beaufort wind scale for given wind speed.
 *
 * @link http://en.wikipedia.org/wiki/Beaufort_scale
 *
 * @param int $wind_speed
 *   Wind speed in m/s.
 *
 * @return array
 *   Beaufort number and description.
 */
function weather_calculate_beaufort($wind_speed) {
  // Set up an array of wind descriptions according to Beaufort scale.
  $description = array(
    t('Calm'),
    t('Light air'),
    t('Light breeze'),
    t('Gentle breeze'),
    t('Moderate breeze'),
    t('Fresh breeze'),
    t('Strong breeze'),
    t('Near gale'),
    t('Gale'),
    t('Strong gale'),
    t('Storm'),
    t('Violent storm'),
    t('Hurricane'),
  );
  $number = 0;
  if ($wind_speed >= 0.3) $number = 1;
  if ($wind_speed >= 1.6) $number = 2;
  if ($wind_speed >= 3.5) $number = 3;
  if ($wind_speed >= 5.5) $number = 4;
  if ($wind_speed >= 8.0) $number = 5;
  if ($wind_speed >= 10.8) $number = 6;
  if ($wind_speed >= 13.9) $number = 7;
  if ($wind_speed >= 17.2) $number = 8;
  if ($wind_speed >= 20.8) $number = 9;
  if ($wind_speed >= 24.5) $number = 10;
  if ($wind_speed >= 28.5) $number = 11;
  if ($wind_speed >= 32.7) $number = 12;
  return array('number' => $number, 'description' => $description[$number]);
}

/**
 * Convert pressure.
 *
 * @param int $pressure
 *   Pressure in hPa.
 * @param string $unit
 *   Unit to be returned (for example, inHg, mmHg, hPa, kPa).
 *
 * @return string
 *   Formatted representation.
 */
function weather_format_pressure($pressure, $unit) {
  if ($unit == 'inhg') {
    $result = t('!pressure&thinsp;inHg',
      array('!pressure' => round($pressure * 0.02953, 2)));
  }
  elseif ($unit == 'inhg_value') {
    $result = round($pressure * 0.02953, 2);
  }
  elseif ($unit == 'mmhg') {
    $result = t('!pressure&thinsp;mmHg',
      array('!pressure' => round($pressure * 0.75006, 0)));
  }
  elseif ($unit == 'mmhg_value') {
    $result = round($pressure * 0.75006, 0);
  }
  elseif ($unit == 'kpa') {
    $result = t('!pressure&thinsp;kPa',
      array('!pressure' => round($pressure / 10, 1)));
  }
  elseif ($unit == 'kpa_value') {
    $result = round($pressure / 10, 1);
  }
  elseif ($unit == 'hpa_value') {
    $result = $pressure;
  }
  else {
    // default to metric units
    $result = t('!pressure&thinsp;hPa', array('!pressure' => $pressure));
  }
  return preg_replace("/([^ ]*)&thinsp;([^ ]*)/",
    '<span style="white-space:nowrap;">\1&thinsp;\2</span>', $result);
}

/**
 * Format information about nearest weather station.
 *
 * @param array $station
 *   Information about distance and bearing of weather station.
 * @param object $display
 *   Display configuration (for example, UK miles, km).
 *
 * @return string
 *   Formatted representation.
 */
function weather_format_nearest_station($station, $display) {
  $bearing = weather_bearing_to_text($station['bearing'], $display->config['show_abbreviated_directions']);
  if ($display->config['distance'] == 'miles') {
    $distance = round($station['distance'] / 1.609344, 1);
    if ($display->config['show_directions_degree']) {
      $result = t('!distance&thinsp;mi !bearing (!degree°)', array(
        '!distance' => $distance,
        '!bearing' => $bearing,
        '!degree' => $station['bearing'],
      ));
    }
    else {
      $result = t('!distance&thinsp;mi !bearing', array(
        '!distance' => $distance,
        '!bearing' => $bearing,
      ));
    }
  }
  else {
    // Default to metric units.
    $distance = $station['distance'];
    if ($display->config['show_directions_degree']) {
      $result = t('!distance&thinsp;km !bearing (!degree°)', array(
        '!distance' => $distance,
        '!bearing' => $bearing,
        '!degree' => $station['bearing'],
      ));
    }
    else {
      $result = t('!distance&thinsp;km !bearing', array(
        '!distance' => $distance,
        '!bearing' => $bearing,
      ));
    }
  }
  return preg_replace("/([^ ]*)&thinsp;([^ ]*)/",
    '<span style="white-space:nowrap;">\1&thinsp;\2</span>', $result);
}

/**
 * Calculate the times of sunrise and sunset.
 *
 * @param string $date
 *   The date for which the calculation should be made.
 * @param int $utc_offset
 *   UTC offset of local time in minutes.
 * @param string $geoid
 *   The GeoID of a place.
 *
 * @return array or string
 *   An array with sunrise and sunset times in the local timezone.
 *   If a string is returned, this is the special case for polar
 *   day or polar night without sunrise and sunset.
 */
function _weather_calculate_sun_info($date, $utc_offset, $geoid) {
  module_load_include('inc', 'weather', 'weather.common');
  // Get the coordinates for sunrise and sunset calculation.
  $coordinates = weather_get_information_about_geoid($geoid);
  // Calculate the timestamp for the local time zone
  $time = strtotime($date . ' 12:00:00 UTC') - 60 * $utc_offset;
  $sun_info = date_sun_info($time, $coordinates->latitude, $coordinates->longitude);
  // Handle special cases (no sunrise or sunset at all).
  if ($sun_info['sunrise'] == 0 and $sun_info['sunset'] == 0) {
    // Sun is always below the horizon.
    $result = t('No sunrise, polar night');
  }
  elseif ($sun_info['sunrise'] == 1 and $sun_info['sunset'] == 1) {
    // Sun is always above the horizon.
    $result = t('No sunset, polar day');
  }
  else {
    // There is a sunrise and a sunset.
    // We don't need the exact second of the sunrise and sunset.
    // Therefore, the times are rounded to the next minute.
    $time = round($sun_info['sunrise'] / 60) * 60;
    $time = gmdate('H:i', $time + 60 * $utc_offset);
    $result['sunrise'] = $time;
    $time = round($sun_info['sunset'] / 60) * 60;
    $time = gmdate('H:i', $time + 60 * $utc_offset);
    $result['sunset'] = $time;
  }
  return $result;
}
