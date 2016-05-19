<?php
/**
 * @file
 * custom_roles_and_permissions.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function custom_roles_and_permissions_user_default_roles() {
  $roles = array();

  // Exported role: Organization.
  $roles['Organization'] = array(
    'name' => 'Organization',
    'weight' => 4,
  );

  // Exported role: Player.
  $roles['Player'] = array(
    'name' => 'Player',
    'weight' => 3,
  );

  return $roles;
}
