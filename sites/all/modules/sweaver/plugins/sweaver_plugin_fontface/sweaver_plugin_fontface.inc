<?php

/**
 * @file
 * @font-face plugin.
 */
class sweaver_plugin_fontface extends sweaver_plugin {

  /**
   * Sweaver dependencies.
   */
  public function sweaver_dependencies() {
    return array('fontyourface');
  }

  /**
   * Sweaver objects alter.
   */
  public function sweaver_objects_alter(&$objects) {
    $extra_fonts = array();
    $used_fonts = fontyourface_get_fonts('enabled = 1');

    foreach ($used_fonts as $font) {
      if (module_exists($font->provider)) {

        if (function_exists('fontyourface_font_css')) {
          $extra_fonts[$font->css_family] = $font->name;
        }
        else {
          $css_function = $font->provider . '_fontyourface_css';
          $font_css = $css_function($font);
          $extra_fonts[$font_css['font-family']] = $font->group_name;
        }
      }
    }

    // Unserialize first, serialize after.
    if (!is_array($objects->property->all['font-family']->property_options)) {
      $objects->property->all['font-family']->property_options = unserialize($objects->property->all['font-family']->property_options);
    }
    $objects->property->all['font-family']->property_options += $extra_fonts;
    $objects->property->all['font-family']->property_options = serialize($objects->property->all['font-family']->property_options);
    if (isset($objects->property->enabled['font-family'])) {
      if (!is_array($objects->property->all['font-family']->property_options)) {
        $objects->property->enabled['font-family']->property_options = unserialize($objects->property->enabled['font-family']->property_options);
      }
      $objects->property->enabled['font-family']->property_options += $extra_fonts;
      $objects->property->enabled['font-family']->property_options = serialize($objects->property->enabled['font-family']->property_options);
    }
  }

}
