<?php

/**
 * @file
 * Contains pager theme and related functions.
 */

/**
 * Implements theme_pager().
 *
 * Renders a pager with next format:
 * On page 1: [1] 2 ... 15 ->
 * On page 2: <- 1 [2] 3 ... 15 ->
 * On page 3: <- 1 2 [3] 4 ... 15 ->
 * On page 4: <- 1 ... 3 [4] 5 ... 15 ->
 * On page 15: <- 1 ... 14 [15]
 */
function materialize_pager($variables) {
  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];
  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // Current is the page we are currently paged to.
  $pager_current = $pager_page_array[$element] + 1;
  // First is the first page listed by this pager piece (re quantity).
  $pager_first = $pager_current - $pager_middle + 1;
  // Last is the last page listed by this pager piece (re quantity).
  $pager_last = $pager_current + $quantity - $pager_middle;
  // Max is the maximum page number.
  $pager_max = $pager_total[$element];
  // End of marker calculations.
  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }
  // End of generation loop preparation.
  $li_previous = theme('pager_previous',
    array(
      'text' => (isset($tags[1]) ? $tags[1] : t('‹')),
      'element' => $element,
      'interval' => 1,
      'parameters' => $parameters,
    )
  );
  $li_next = theme('pager_next',
    array(
      'text' => (isset($tags[3]) ? $tags[3] : t('›')),
      'element' => $element,
      'interval' => 1,
      'parameters' => $parameters,
    )
  );

  if ($pager_total[$element] > 1) {
    if ($li_previous) {
      $items[] = array(
        'class' => array('pager-previous'),
        'data' => $li_previous,
      );
    }

    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      if ($i > 1) {
        $items[] = array(
          'class' => array('pager-ellipsis'),
          'data' => '…',
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_previous',
              array(
                'text' => $i,
                'element' => $element,
                'interval' => ($pager_current - $i),
                'parameters' => $parameters,
              )
            ),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array('active'),
            'data' => $i,
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            'class' => array('waves-effect'),
            'data' => theme('pager_next',
              array(
                'text' => $i,
                'element' => $element,
                'interval' => ($i - $pager_current),
                'parameters' => $parameters,
              )
            ),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => array('pager-ellipsis'),
          'data' => '…',
        );
      }
    }
    // End generation.
    if ($li_next) {
      $items[] = array(
        'class' => array('pager-next'),
        'data' => $li_next,
      );
    }
    return '<h2 class="element-invisible">' . t('Pages') . '</h2>' . theme('item_list', array(
      'items' => $items,
      'attributes' => array('class' => array('pagination')),
    ));
  }
}
