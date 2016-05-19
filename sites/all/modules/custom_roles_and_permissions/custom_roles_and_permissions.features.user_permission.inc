<?php
/**
 * @file
 * custom_roles_and_permissions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function custom_roles_and_permissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer profile types'.
  $permissions['administer profile types'] = array(
    'name' => 'administer profile types',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'profile2',
  );

  // Exported permission: 'administer profiles'.
  $permissions['administer profiles'] = array(
    'name' => 'administer profiles',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'profile2',
  );

  // Exported permission: 'edit any main profile'.
  $permissions['edit any main profile'] = array(
    'name' => 'edit any main profile',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'profile2',
  );

  // Exported permission: 'edit any organization_profile profile'.
  $permissions['edit any organization_profile profile'] = array(
    'name' => 'edit any organization_profile profile',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'profile2',
  );

  // Exported permission: 'edit own main profile'.
  $permissions['edit own main profile'] = array(
    'name' => 'edit own main profile',
    'roles' => array(
      'Moderator' => 'Moderator',
      'Player' => 'Player',
      'administrator' => 'administrator',
    ),
    'module' => 'profile2',
  );

  // Exported permission: 'edit own organization_profile profile'.
  $permissions['edit own organization_profile profile'] = array(
    'name' => 'edit own organization_profile profile',
    'roles' => array(
      'Moderator' => 'Moderator',
      'Organization' => 'Organization',
      'administrator' => 'administrator',
    ),
    'module' => 'profile2',
  );

  // Exported permission: 'view any main profile'.
  $permissions['view any main profile'] = array(
    'name' => 'view any main profile',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'profile2',
  );

  // Exported permission: 'view any organization_profile profile'.
  $permissions['view any organization_profile profile'] = array(
    'name' => 'view any organization_profile profile',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'profile2',
  );

  // Exported permission: 'view own main profile'.
  $permissions['view own main profile'] = array(
    'name' => 'view own main profile',
    'roles' => array(
      'Moderator' => 'Moderator',
      'Player' => 'Player',
      'administrator' => 'administrator',
    ),
    'module' => 'profile2',
  );

  // Exported permission: 'view own organization_profile profile'.
  $permissions['view own organization_profile profile'] = array(
    'name' => 'view own organization_profile profile',
    'roles' => array(
      'Moderator' => 'Moderator',
      'Organization' => 'Organization',
      'administrator' => 'administrator',
    ),
    'module' => 'profile2',
  );

  return $permissions;
}
