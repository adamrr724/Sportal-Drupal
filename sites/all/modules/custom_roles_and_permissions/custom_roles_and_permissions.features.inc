<?php
/**
 * @file
 * custom_roles_and_permissions.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function custom_roles_and_permissions_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_profile2_type().
 */
function custom_roles_and_permissions_default_profile2_type() {
  $items = array();
  $items['main'] = entity_import('profile2_type', '{
    "userCategory" : false,
    "userView" : false,
    "type" : "main",
    "label" : "My profile",
    "weight" : "0",
    "data" : { "registration" : 1, "use_page" : 1 },
    "rdf_mapping" : []
  }');
  $items['organization_profile'] = entity_import('profile2_type', '{
    "userCategory" : false,
    "userView" : false,
    "type" : "organization_profile",
    "label" : "Organization Profile",
    "weight" : "0",
    "data" : { "registration" : 0, "use_page" : 1 },
    "rdf_mapping" : []
  }');
  return $items;
}
