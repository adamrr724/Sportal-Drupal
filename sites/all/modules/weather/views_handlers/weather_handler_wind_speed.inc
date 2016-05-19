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
 * Field handler to render the wind speed.
 */
class weather_handler_wind_speed extends views_handler_field {
  /**
   * Setup default unit for wind speed.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['unit'] = array('default' => 'kmh');
    return $options;
  }

  /**
   * Provide units to select for wind speed.
   */
  function options_form(&$form, &$form_state) {
    $form['unit'] = array(
      '#title' => t('Unit for wind speed display'),
      '#description' => t('Select unit for formatted wind speeds or display only value.'),
      '#type' => 'select',
      '#default_value' => $this->options['unit'],
      '#options' => array(
        'kmh' => t('km/h'),
        'kmh_value' => t('km/h (only value)'),
        'mph' => t('mph'),
        'mph_value' => t('mph (only value)'),
        'knots' => t('Knots'),
        'knots_value' => t('Knots (only value)'),
        'mps' => t('meter/s'),
        'mps_value' => t('meter/s (only value)'),
        'beaufort' => t('Beaufort'),
        'beaufort_value' => t('Beaufort (only value)'),
      ),
    );
    parent::options_form($form, $form_state);
  }

  /**
   * Render wind speed with selected unit.
   */
  function render($values) {
    if (is_null($values->{$this->field_alias})) {
      return;
    }
    $value = $values->{$this->field_alias};
    module_load_include('inc', 'weather', 'weather_theme');
    return weather_format_wind_speed($value, $this->options['unit']);
  }
}
