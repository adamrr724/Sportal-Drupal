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
 * Field handler to render the wind direction.
 */
class weather_handler_wind_direction extends views_handler_field {
  /**
   * Setup default settings.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['wind_settings'] = array('default' => 'normal');
    return $options;
  }

  /**
   * Provide settings to select for wind direction.
   */
  function options_form(&$form, &$form_state) {
    $form['wind_settings'] = array(
      '#title' => t('Formatting of wind direction display'),
      '#description' => t('Select formatting for wind directions or display only value.'),
      '#type' => 'select',
      '#default_value' => $this->options['wind_settings'],
      '#options' => array(
        'normal' => t('Normal text'),
        'normal_degree' => t('Normal text with degree'),
        'abbreviated' => t('Abbreviated text'),
        'abbreviated_degree' => t('Abbreviated text with degree'),
        'degree' => t('Degree'),
        'degree_value' => t('Degree (only value)'),
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
    $value = $values->{$this->field_alias};
    module_load_include('inc', 'weather', 'weather_theme');
    return weather_format_wind_direction($value, $this->options['wind_settings']);
  }
}
