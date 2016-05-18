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
 * Field handler to render the wind condition.
 */
class weather_handler_wind extends views_handler_field {
  /**
   * Override init function for additional fields to add.
   */
  function init(&$view, &$options) {
    parent::init($view, $options);
    $this->additional_fields['wind_speed'] = 'wind_speed';
  }

  /**
   * Setup default options for wind formatting.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['wind_settings'] = array('default' => 'normal');
    $options['unit'] = array('default' => 'kmh');
    return $options;
  }

  /**
   * Provide settings to select for wind formatting.
   */
  function options_form(&$form, &$form_state) {
    $form['wind_settings'] = array(
      '#title' => t('Formatting of wind direction display'),
      '#description' => t('Select formatting for wind directions.'),
      '#type' => 'select',
      '#default_value' => $this->options['wind_settings'],
      '#options' => array(
        'normal' => t('Normal text'),
        'normal_degree' => t('Normal text with degree'),
        'abbreviated' => t('Abbreviated text'),
        'abbreviated_degree' => t('Abbreviated text with degree'),
      ),
    );
    $form['unit'] = array(
      '#title' => t('Unit for wind speed display'),
      '#description' => t('Select unit for formatted wind speeds.'),
      '#type' => 'select',
      '#default_value' => $this->options['unit'],
      '#options' => array(
        'kmh' => t('km/h'),
        'mph' => t('mph'),
        'knots' => t('Knots'),
        'mps' => t('meter/s'),
        'beaufort' => t('Beaufort'),
      ),
    );
    parent::options_form($form, $form_state);
  }

  /**
   * Render wind information with selected unit.
   */
  function render($values) {
    if (is_null($values->{$this->field_alias})) {
      return;
    }
    $wind_direction = $values->{$this->field_alias};
    $wind_speed = $this->get_value($values, 'wind_speed');
    // Check whether to use abbreviated directions.
    $abbreviated = (strpos($this->options['wind_settings'], 'abbreviated') !== FALSE);
    // Check whether to use exact degrees.
    $exact_degree = (strpos($this->options['wind_settings'], 'degree') !== FALSE);
    module_load_include('inc', 'weather', 'weather_theme');
    return weather_format_wind($wind_direction, $wind_speed, $this->options['unit'], $abbreviated, $exact_degree);
  }
}
