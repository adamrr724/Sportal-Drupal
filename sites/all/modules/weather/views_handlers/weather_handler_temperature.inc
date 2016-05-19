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
 * Field handler to allow selection of temperature units.
 */
class weather_handler_temperature extends views_handler_field_numeric {
  /**
   * Setup default unit.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['unit'] = array('default' => 'celsius');
    return $options;
  }

  /**
   * Provide unit to select.
   */
  function options_form(&$form, &$form_state) {
    $form['unit'] = array(
      '#title' => t('Unit for temperature display'),
      '#description' => t('Select unit for formatted temperatures or display only value.'),
      '#type' => 'select',
      '#default_value' => $this->options['unit'],
      '#options' => array(
        'celsius' => t('Celsius'),
        'celsius_value' => t('Celsius (only value)'),
        'fahrenheit' => t('Fahrenheit'),
        'fahrenheit_value' => t('Fahrenheit (only value)'),
        'celsiusfahrenheit' => t('Celsius / Fahrenheit'),
        'fahrenheitcelsius' => t('Fahrenheit / Celsius'),
      ),
    );
    parent::options_form($form, $form_state);
  }

  /**
   * Render temperature with selected unit.
   */
  function render($values) {
    if (is_null($values->{$this->field_alias})) {
      return;
    }
    $value = $values->{$this->field_alias};
    module_load_include('inc', 'weather', 'weather_theme');
    return weather_format_temperature($value, $this->options['unit']);
  }
}
