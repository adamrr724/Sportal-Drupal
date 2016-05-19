<?php

/**
 * @file
 * Views handler for weather module.
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
 * Field handler to 
 */
class weather_handler_date extends views_handler_field_date {
  /**
   * Override init function for additional fields to add.
   */
  function init(&$view, &$options) {
    parent::init($view, $options);
    $this->additional_fields['utc_offset'] = array(
      'table' => 'weather_forecast_information',
      'field' => 'utc_offset',
    );
  }

  /**
   * Calculate UNIX timestamp of date.
   */
  function get_value($values, $field = NULL) {
    if (is_null($values->{$this->field_alias})) {
      return;
    }
    $value = parent::get_value($values, $field);
    $utc_offset = parent::get_value($values, 'utc_offset');
    $sign = ($utc_offset < 0) ? '-' : '+';
    $utc_offset = abs($utc_offset);
    $hours = sprintf("%02d", floor($utc_offset / 60));
    $minutes = sprintf("%02d", $utc_offset % 60);
    return strtotime($value . ' ' . $sign . $hours . ':' . $minutes);
  }
}
