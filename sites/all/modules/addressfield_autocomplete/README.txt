Addressfield autocomplete
------------------------------------------------------------------------------
Provides a hook into google maps autocomplete API. Implements a new widget
which utilises the addressfield autocomplete functionality and provides an
easy to use single box for entering an address. 

It also allows you to target addresses within specific countries and search 
for full addresses, establishments or just cities within those countries.

Dependencies
------------------------------------------------------------------------------
This module is dependent on the following drupal modules: Addressfield, GMap 
and Libraries.

It also requires a 3rd party javascript plugin which can be found here:
http://ubilabs.github.io/geocomplete/

Installation
------------------------------------------------------------------------------
1. Make sure you have installed addressfield, GMap and libraries.
2. Download the geocomplete plugin from the following location
   http://ubilabs.github.io/geocomplete/
3. Extract the plugin to your libraries directory and rename the folder
   geocomplete.
4. Navigate to manage fields inside a content type.
5. Create or edit a new or existing address field, change the widget to Address
   autocomplete.
6. Adjust the instance settings of the field to suit your needs.

Addressfield Autocomplete, Geofield and Geocoder work together
------------------------------------------------------------------------------
For more information on integrating these 3 modules please visit:
https://www.drupal.org/node/2359579

Notes
------------------------------------------------------------------------------
Some of the maps settings are inherited from the GMap module settings page.
These include: width, height, center, zoom and map type. The reset of the 
settings are configurable through the instance settings form for that field.
