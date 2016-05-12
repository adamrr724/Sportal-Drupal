<?php
/**
 * @file
 * Contains menu related theme functions.
 */

/**
 * Materialize theme wrapper function for the primary menu links.
 */
function materialize_menu_tree__primary(&$variables) {
  return '<ul class="menu">' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_menu_tree().
 */
function materialize_menu_tree(&$variables) {
  return '<div class="collection with-header">' . $variables['tree'] . '</div>';
}

/**
 * Materialize theme wrapper function for the secondary menu links.
 */
function materialize_menu_tree__secondary(&$variables) {
  return '<ul class="menu">' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_menu_tree().
 */
function materialize_menu_tree__shortcut_set(&$variables) {
  return theme_menu_tree($variables);
}

/**
 * Materialize theme wrapper function for the submenu links.
 */
function materialize_menu_tree__submenu(&$variables) {
  return '<div class="menu">' . $variables['tree'] . '</div>';
}

/**
 * Implements theme_menu_local_tasks().
 */
function materialize_menu_local_tasks(&$variables) {
  $primary = isset($variables['primary']) ? $variables['primary'] : NULL;
  $secondary = isset($variables['secondary']) ? $variables['secondary'] : NULL;
  $output = '';
  if (!empty($primary)) {
    $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<ul class="tabs z-depth-1">';
    $variables['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($secondary)) {
    $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<ul class="tabs z-depth-1">';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }
  return $output;
}

/**
 * Implements theme_menu_local_tasks().
 */
function materialize_menu_local_task($variables) {
  $link = $variables['element']['#link'];
  $link_text = $link['title'];

  if (!empty($variables['element']['#active'])) {
    // Add text to indicate active tab for non-visual users.
    $active = '<span class="element-invisible">' . t('(active tab)') . '</span>';

    // If the link does not contain HTML already, check_plain() it now.
    // After we set 'html'=TRUE the link will not be sanitized by l().
    if (empty($link['localized_options']['html'])) {
      $link['title'] = check_plain($link['title']);
    }
    $link['localized_options']['html'] = TRUE;
    $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));
  }

  return '<li' . (!empty($variables['element']['#active']) ? ' class="active tab"' : ' class="tab"') . '>' . l($link_text, $link['href'], $link['localized_options']) . "</li>\n";
}

/**
 * Overrides theme_menu_link().
 */
function materialize_menu_link(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';
  $element['#localized_options']['attributes']['class'][] = 'collection-item';
  if ($element['#below']) {
    $element['#below']['#theme_wrappers'] = array('menu_tree__submenu');
    // Prevent dropdown functions from being added to management menu so it
    // does not affect the navbar module.
    if (($element['#original_link']['menu_name'] == 'management') && (module_exists('navbar'))) {
      $sub_menu = drupal_render($element['#below']);
    }
    elseif ((!empty($element['#original_link']['depth'])) && ($element['#original_link']['depth'] == 1)) {
      // Add our own wrapper.
      unset($element['#below']['#theme_wrappers']);
      $sub_menu = '<ul class="dropdown-content" id="dropdown-menu">' . drupal_render($element['#below']) . '</ul>';
      // Generate as standard dropdown.
      $element['#title'] .= ' <i class="mdi-navigation-arrow-drop-down right"></i>';
      $element['#attributes']['class'][] = 'dropdown';
      $element['#localized_options']['html'] = TRUE;

      // Set dropdown trigger element to # to prevent inadvertent page loading
      // when a submenu link is clicked.
      $element['#localized_options']['attributes']['data-target'] = '#';
      $element['#localized_options']['attributes']['class'][] = 'dropdown-button';
      $element['#localized_options']['attributes']['data-activates'] = 'dropdown-menu';
    }
  }
  // On primary navigation menu, class 'active' is not set on active menu item.
  // @see https://drupal.org/node/1896674
  if (($element['#href'] == $_GET['q'] || ($element['#href'] == '<front>' && drupal_is_front_page())) && (empty($element['#localized_options']['language']))) {
    $element['#attributes']['class'][] = 'active';
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}
