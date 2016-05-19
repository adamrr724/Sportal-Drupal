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
 * Field handler to render the weather condition and return an <img> tag.
 */
class weather_handler_condition extends views_handler_field {
  /**
   * Render translated condition or <img> tag.
   */
  function render($values) {
    if (is_null($values->{$this->field_alias})) {
      return;
    }
    module_load_include('inc', 'weather', 'weather_theme');
    $condition = weather_format_condition($values->{$this->field_alias});
    if ($this->field == 'symbol') {
      return weather_format_image($values->{$this->field_alias}, $condition);
    }
    else {
      return $condition;
    }
  }
}
