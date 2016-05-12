/**
 * @file
 * Contains helper functions to work with theme.
 */

(function ($) {
  "use strict"

  /**
   * Changes caret icon for fieldset when it is being collapsed or expanded.
   */
  Drupal.behaviors.materializeFieldset = {
    attach: function (context) {
      jQuery('fieldset', context).on('collapsed', function (data) {
        var $caretIcon = jQuery('.fieldset-title i', this);
        if (data.value === true) {
          $caretIcon.removeClass('mdi-hardware-keyboard-arrow-down').addClass('mdi-hardware-keyboard-arrow-right');
        }
        else {
          $caretIcon.removeClass('mdi-hardware-keyboard-arrow-right').addClass('mdi-hardware-keyboard-arrow-down');
        }
      });
    }
  };
  jQuery(".button-collapse").sideNav();
})(jQuery);
