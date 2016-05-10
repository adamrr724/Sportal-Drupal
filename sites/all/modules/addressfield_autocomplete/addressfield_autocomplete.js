/**
 * @file
 * The addressfield autocomplete js.
 *
 * Js to allow user to pick an autocompleted address from
 */

(function($) {
  /**
   * Initialise the geocomplete js
   */
  var addressfieldAutocompleteInit = function(o, settings) {
    var gmapSettings = Drupal.settings.addressfield_autocomplete.gmap,
            widget = o.closest('.form-item').siblings('div[id^="addressfield-wrapper"]:first'),
            reveal = o.closest('.form-item').prev('.addressfield-autocomplete-hidden-reveal'),
            link = o.closest('.form-item').siblings('.addressfield-autocomplete-link:first').find('a'),
            lat = widget.find('.latitude').val(),
            lng = widget.find('.longitude').val(),
            zoom = parseInt(widget.find('.zoom').val()),
            location = gmapSettings.latlong.split(','),
            center = new google.maps.LatLng(location[0], location[1]),
            options = {};

    if (settings.map) {
      var map = o.closest('.form-item').siblings('.autocomplete-map');
      settings.map_id = map.attr('id');
    }

    /*
     * Set data inside the object so it can be used in other functions.
     */
    o.data({
      'settings': settings,
      'widget': widget,
      'reveal': reveal,
      'link': link,
      'map': map
    });

    if (lat != 0 && lng != 0) {
      location = [lat, lng];
    }

    /*
     * Set the default options for google maps, places and geocomplete.
     */
    options = {
      map: !!settings.map ? "#" + settings.map_id : false,
      mapOptions: {
        center: center,
        mapTypeId: gmapSettings.maptype,
        zoom: location && zoom ? zoom : parseInt(gmapSettings.zoom),
        disableDefaultUI: gmapSettings.controltype == 'None',
        panControl: !!gmapSettings.pancontrol
      },
      markerOptions: {
        draggable: !!settings.draggable,
        visible: !!settings.visible_markers
      },
      maxZoom: parseInt(gmapSettings.maxzoom),
      location: location ? location : gmapSettings.latlong.split(','),
      types: [ settings.types ]
    };

    if (Object.size(settings.available_countries) == 1) {
      /**
       * For now the google api only accepts one country, because the available
       * countries are inside an object we had to use a loop to get the first
       * item in that object.
       */
      for (var country in settings.available_countries) {
        break;
      }

      var componentRestrictions = {
        componentRestrictions: {
          country: settings.available_countries[country]
        }
      };
      $.extend(options, componentRestrictions);
    }

    o.geocomplete(options).bind("geocode:result", function(event, result) {
      /*
       * Reveal the standard addressfield widget.
       * Update the widget, we have to do it this way instead
       * of the method provided by geocomplete because the
       * addressfield widget has a select for country.
       */
      $(this).data('result', result);
      $(this).addClass('complete');
      addressfieldAutocompleteToggleWidget($(this));
      addressfieldAutocompleteUpdateAddress($(this));
    }).bind("geocode:dragged", function(event, result) {
      var widget = $(this).data('widget'),
              latlng = new google.maps.LatLng(result.lat(), result.lng());
      widget.find('.latitude').val(result.lat());
      widget.find('.longitude').val(result.lng());

      /*
       * Reverse geocode setting must be enabled to activate this.
       * As moving the marker and changing the address can be an annoying 
       * ux if you are not expecting it.
       */
      if (!!settings.reverse_geocode) {
        o.geocomplete('geocoder').geocode({'latLng': latlng}, function(results, status) {
          if (status == google.maps.GeocoderStatus.OK) {
            if (results[1]) {
              var map = o.geocomplete('map');
              map.setCenter(latlng);
              o.data('result', results[1]);
              o.addClass('complete reverse-geocode');
              addressfieldAutocompleteToggleWidget(o);
              addressfieldAutocompleteUpdateAddress(o);
            }
          }
        });
      }
    });

    /*
     * If states hide this field to begin with we may have issues with the map
     * needing to be resized. So we need to bind the change.
     */
    o.closest('.form-wrapper').bind('state:visible', function(e) {
      if (e.trigger) {
        var isVisible = o.closest('.form-wrapper').is(':visible');
        $(e.target).closest('.form-item, .form-submit, .form-wrapper').toggle(e.value);
        if (!isVisible) {
          addressfieldAutocompleteResetMap(o);
        }
      }
    });
    /*
     * If the map is inside a fieldset then we need to register events to make
     * sure the map resizes itself when that fieldset is revealed.
     */
    if (!!settings.map) {
      var fieldsets = o.closest('fieldset.collapsible').find('legend a'),
              verticalTabs = o.closest('.vertical-tabs').find('.vertical-tabs-list a'),
              collapsedDiv = o.closest('div.collapsible').find('.field-group-format-toggler a'),
              accordion = o.closest('.ui-accordion');
      fieldsets.add(verticalTabs).add(collapsedDiv).add(accordion).bind('click', function() {
        addressfieldAutocompleteResetMap(o);
      });
      /*
       * If the lat lng is zero let's try a reverse geocode to see if we
       * can put a point on the map but only do this if the first input
       * has a value.
       */
      if (lat == 0 && lng == 0 && widget.find('input[type="text"]:first').val() != '') {
        addressfieldAutocompleteManualAddressGeocode(widget.find('input[type="text"]:first'));
      }
    }
    /*
     * If the widget contains the class error we want to reveal the widget so
     * that they can see the fields that are missing.
     */
    if ($('.form-item .error', widget).length > 0) {
      reveal.val(1);
    }
    /**
     * Upon addressfieldAutocompleteInitalisation if reveal is set it to 1, set
     * it to 0 and toggle widget to trigger reset link.
     */
    if (reveal.val() == 1) {
      reveal.val(0);
      o.addClass('complete');
      addressfieldAutocompleteToggleWidget(o);
    }
  };
  /**
   * Set map defaults
   */
  var addressfieldAutocompleteResetMap = function(o) {
    var map = o.geocomplete('map'),
            marker = o.geocomplete('marker');

    if (map) {
      var center = map.getCenter();
      google.maps.event.trigger(map, 'resize');
      map.setCenter(center);
      map.setZoom(map.getZoom());
      if (marker) {
        marker.setPosition(center);
      }
    }

  };
  /**
   * Reveal the addressfield widget
   */
  var addressfieldAutocompleteToggleWidget = function(o) {
    var reveal = o.data('reveal'),
            widget = o.data('widget'),
            settings = o.data('settings'),
            link = o.data('link');
    /*
     * If the reveal value is set to 0 the widget is not shown.
     */
    if (!!settings.reveal) {
      widget.find('.addressfield-autocomplete-reveal').remove();

      if (reveal.val() == 0) {
        reveal.val(1);
        reveal.trigger('change');
      }
      else if (o.hasClass('manual-remove')) {
        // Reset all values back to zero
        o.removeClass('manual-add manual-remove').val('');
        o.removeData('result');
        widget.find('input,select.state').val('');
        addressfieldAutocompleteResetMap(o);
        reveal.val(0);
        reveal.trigger('change');
      }

      /*
       * Add a reset link to a manual address.
       */
      if (o.hasClass('manual-add') || o.hasClass('complete')) {
        o.removeClass('complete');
        link = link.clone(true).text(Drupal.t('Reset address'));
        link.attr('id', o.attr('id')).appendTo(widget);
      }
    }
    return widget;
  };
  var addressfieldAutocompleteManualAddressGeocode = function(o, data) {
    var widget = o.closest('div[id^="addressfield-wrapper"]'),
            input = widget.prevAll('.form-item').find('.addressfield-autocomplete-input'),
            address = [];
    if (data === undefined) {
      input.removeClass('reverse-geocode').addClass('manual-add');
    }
    if (input.hasClass('manual-add') && !input.hasClass('reverse-geocode')) {
      /*
       * If we manually add an address and we change the country
       * then we want to remove all other fields
       */
      if (o.hasClass('country')) {
        widget.find('input,select.state').val('');
      }
      /*
       * Take all of the values out of the address fields and insert
       * them comma separated into the geocomplete box. Then call
       * geocomplete find, this will hopefully return a result and
       * updated our latitude, longitude and zoom values.
       */
      widget.find('input[type="text"],select').each(function() {
        if ($(this).val().length > 0) {
          if ($(this).is('input')) {
            address.push($(this).val());
          }
          else {
            address.push($(this).find('option:selected').text());
          }
        }
      });
      input.val(address);
      input.geocomplete('find');
    }
  };
  var addressfieldAutocompleteUpdateAddress = function(o) {
    var data = {},
            settings = o.data('settings'),
            widget = o.data('widget'),
            map = o.data('map'),
            result = o.data('result');
    /*
     * Load all of the address details obtained by the geocomplete
     * into a data array to be used later.
     */
    $.each(result.address_components, function(index, object) {
      var name = object.types[0];
      data[name] = object.long_name;
      data[name + "_short"] = object.short_name;
    });
    if (result.geometry.location !== undefined) {
      data['lat'] = result.geometry.location.lat();
      data['lng'] = result.geometry.location.lng();
    }
    if (result.name !== undefined) {
      data['organisation_name'] = result.name;
    }
    /*
     * If reverse geocode is switched on then we always want to update the
     * autocomplete formatted address.
     */
    if (!!settings.reverse_geocode) {
      o.val(result.formatted_address);
    }
    /*
     * Only update if not manually adding an address or reverse geocoding
     */
    if (!o.hasClass('manual-add') || o.hasClass('reverse-geocode')) {
      /*
       * Clear all data before commencing the update
       */
      widget.find('input,select.state').val('');
      /*
       * Check that the country in the result is the same as widget
       * If not we need to trigger the change.
       */
      var country = widget.find('select.country:first');
      if (data.country_short !== country.val()) {
        country.val(data.country_short);
        country.trigger('change', [{
            update: true
          }]);
      }
      /*
       * If the change has been triggered because the addressfield
       * module uses ajax to change the widget we will need to come
       * in this function again to update the rest of the values
       * as the postcode and county field are not always in the
       * widget. To update we loop through all fields inside the
       * widget that have an attribute with data-geo. We then explode
       * the data-geo value on a space because we sometimes wish to
       * add multiple values to the same field. We then replace the
       * value with the data value.
       */
      $.each(widget.find('[data-geo]'), function() {
        var object = $(this);
        var geo = object.data('geo').split(" ");
        for (var i = 0; i < geo.length; i++) {
          // If no data in result then continue
          if (data[geo[i]] === undefined) {
            continue;
          }
          // Handle subpremise
          if (geo[i] === 'subpremise' && geo[(i+1)] === 'street_number') {
            $(this).val(data[geo[i]] + '/' + data[geo[(i+1)]]);
            i++;
          }
          // Hanlde rest of thoroughfare
          else if (geo[i] === 'street_number' || geo[i] === 'route') {
            $(this).val() ? $(this).val($(this).val() + " " + data[geo[i]]) : $(this).val(data[geo[i]]);
          }
          else {
            $(this).val(data[geo[i]]);
            // If select and value is not empty
            if ($(this).is('select') && $(this).val().length > 0) {
              break;
            }
          }
        }
      });
    }

    /*
     * The information below will be updated regardless of what method we are
     * using.
     */
    widget.find('[data-geo="lat"]').val(data['lat']);
    widget.find('[data-geo="lng"]').val(data['lng']);
    if (settings.map) {
      var mapObject = o.geocomplete('map');
      widget.find('.zoom').val(mapObject.getZoom());
      /*
       * Show the map if hidden, also need to run place changed because
       * otherwise the map can have visibility problems.
       */
      if (!map.is(':visible')) {
        map.show();
        o.geocomplete('placeChanged');
      }
    }
  };

  Drupal.behaviors.addressfield_autocomplete = {
    attach: function(context, settings) {
      for (var key in settings.addressfield_autocomplete.fields) {
        var field = settings.addressfield_autocomplete.fields[key];
        if (field.hasOwnProperty('map')) {
          $('.addressfield-autocomplete-input[name^="' + key + '["]').each(function() {
            addressfieldAutocompleteInit($(this), field);
          });
        }
      }

      /*
       * We need to give the user the option to manually add an
       * address if they can't find one using the addressfield
       * autocomplete widget.
       */
      $('.addressfield-autocomplete-reveal').once().bind('mousedown', function(e) {
        e.stopPropagation();
        var o;
        if ($(this).attr('id')) {
          o = $("#" + $(this).attr('id'));
          if ($(this).hasClass('manual-add')) {
            /*
             * This is to provide manual addition of an anddress from
             * the link inside the pac container.
             */
            o.addClass('manual-add');
          }
          else {
            /*
             * This is to reset back to the geocomplete field.
             */
            o.removeClass('manual-add').addClass('manual-remove');
          }
        }
        else {
          o = $(this).parent().prev('.form-item').find('.addressfield-autocomplete-input');
          o.addClass('manual-add');
          /*
           * We want to trigger a change to the map position updates,
           * this is only really necessary for fields that have chosen
           * to display the map.
           */
          o.data('widget').find('select.country').trigger('change');
          /*
           * HTML 5 navigator geolocate method. We use the built in browser
           * functionality to then provide geocomplete with latitude and
           * longitude values which it can then process into an address.
           */
          if (!!o.data('settings').html5_geocode && navigator.geolocation) {
            navigator.geolocation.getCurrentPosition(function(position) {
              var lat = position.coords.latitude;
              var lng = position.coords.longitude;
              o.addClass('reverse-geocode');
              o.geocomplete('find', lat + ',' + lng);
            });
          }
        }
        addressfieldAutocompleteToggleWidget(o);
      });
      /*
       * If manual entry has been chosen on blur of each field
       * we want to geocode the entire address but not update
       * the fields apart from latitude, longitude and zoom.
       * As we want this information even if people are entering
       * their addresses manually.
       */
      $('[id^="addressfield-wrapper"] input[type="text"]').once().blur(function() {
        addressfieldAutocompleteManualAddressGeocode($(this));
      });
      $('[id^="addressfield-wrapper"] select').once().change(function(e, data) {
        addressfieldAutocompleteManualAddressGeocode($(this), data);
      });
      /*
       * This allows the user to click a link inside the widget
       * dropdown to enter an address manullay.
       */
      $(document).delegate('.addressfield-autocomplete-input', 'keydown', function() {
        $(".pac-container").find(".addressfield-autocomplete-reveal").remove();
        var link = $(this).data('link');
        link = link.clone(true).text(Drupal.t($(this).data('settings').manual_text));
        link.addClass('manual-add');
        link.attr('id', $(this).attr('id')).appendTo(".pac-container");
      });
      /*
       * Methods to update the address after an ajax callback.
       */
      if (context.length) {
        /*
         * When we trigger a change on the addressfield country
         * select this will be returned. As new fields may have
         * been added we need to update the address.
         */
        if (context[0] !== undefined && context.has('[id^="addressfield-wrapper"]')) {
          var input = context.prevAll('.form-item').find('.addressfield-autocomplete-input');
          if (input[0] !== undefined && input.data('result') !== undefined) {
            addressfieldAutocompleteUpdateAddress(input);
          }
        }
      }
    }
  };

  /**
   * Resize map if inside a conditional field.
   */
  $(document).bind('state:visible-fade state:visible-slide state:visible', function(e) {
    if (e.trigger) {
      var o = $(e.target).find('.addressfield-autocomplete-input');
      if (o.length && o.data('settings') !== undefined && o.data('settings').map) {
        addressfieldAutocompleteResetMap(o);
      }
    }
  });

  /**
   * Get length of object.
   */
  Object.size = function(obj) {
    var size = 0, key;
    for (key in obj) {
      if (obj.hasOwnProperty(key)) {
        size++;
      }
    }
    return size;
  };

})(jQuery);
