<?php
/**
 * @file
 * custom_roles_and_permissions.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function custom_roles_and_permissions_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autoassignrole_user_active';
  $strongarm->value = '1';
  $export['autoassignrole_user_active'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autoassignrole_user_description';
  $strongarm->value = array(
    'value' => 'Please select the type of user you would like to sign up as:
<br>
<br>
<strong>Players</strong> are users who want to sign up for pickups, and find leagues, runs and races, and places to play!<br>
<strong>Organizations</strong> are users who plan to add leagues, runs and races, and places to play to the site!',
    'format' => 'filtered_html',
  );
  $export['autoassignrole_user_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autoassignrole_user_fieldset_title';
  $strongarm->value = 'User Type';
  $export['autoassignrole_user_fieldset_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autoassignrole_user_multiple';
  $strongarm->value = '0';
  $export['autoassignrole_user_multiple'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autoassignrole_user_required';
  $strongarm->value = '1';
  $export['autoassignrole_user_required'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autoassignrole_user_roles';
  $strongarm->value = array(
    7 => '7',
    6 => '6',
    5 => 0,
    4 => 0,
    3 => 0,
  );
  $export['autoassignrole_user_roles'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autoassignrole_user_selection';
  $strongarm->value = '0';
  $export['autoassignrole_user_selection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autoassignrole_user_sort';
  $strongarm->value = 'SORT_ASC';
  $export['autoassignrole_user_sort'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autoassignrole_user_title';
  $strongarm->value = 'User';
  $export['autoassignrole_user_title'] = $strongarm;

  return $export;
}
