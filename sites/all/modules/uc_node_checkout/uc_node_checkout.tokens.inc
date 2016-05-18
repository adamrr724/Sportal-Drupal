<?php

/**
 * @file
 * Token hooks for the uc_node_checkout module.
 */


/**
 * Implements hook_token_values().
 */
function uc_node_checkout_tk_values($type, $object = NULL, $options = array()) {
  if (uc_node_checkout_node_associated($object)) {
    // Load up the corresponding product so we can use the default add to
    // cart quantity.
    if (!empty($object->ucnc_product_nid)) {
      $product = node_load($object->ucnc_product_nid);
    }
    else {
      $order_product_id = db_query('SELECT order_product_id FROM {uc_node_checkout_order_products} WHERE nid = :nid', array(':nid' => $object->nid))->fetchField();
      $nid = db_query('SELECT nid FROM {uc_order_products} WHERE order_product_id = :product_id', array(':product_id' => $order_product_id))->fetchField();
      $product = node_load($nid);
    }
    $tokens = array();
    $tokens['referenced-title'] = $product->title;
    $tokens['model'] = $product->model;
    $tokens['list_price'] = $product->list_price;
    $tokens['cost'] = $product->cost;
    $tokens['sell_price'] = $product->sell_price;
    $tokens['weight_units'] = $product->weight_units;
    $tokens['weight-raw'] = $product->weight;
    $tokens['weight'] = uc_weight_format($product->weight, $product->weight_units);
    $tokens['length_units'] = $product->length_units;
    $tokens['length-raw'] = $product->length;
    $tokens['length'] = uc_length_format($product->length, $product->length_units);
    $tokens['width-raw'] = $product->width;
    $tokens['width'] = uc_length_format($product->width, $product->length_units);
    $tokens['height-raw'] = $product->height;
    $tokens['height'] = uc_length_format($product->height, $product->length_units);
    return $tokens;
  }
}

/**
 * Implements hook_token_info().
 */
function uc_node_checkout_token_info() {
  $types = array(
    'name' => t('Referenced products'),
    'description' => t('Tokens for Ubercart referenced products.'),
    'needs-data' => 'product',
  );

  $tokens = array();

  $tokens['referenced-title'] = array(
    'name' => t('Title'),
    'description' => t("The title of the referenced product."),
  );

  $tokens['model'] = array(
    'name' => t('Model number'),
    'description' => t("The referenced product's model number."),
  );

  $tokens['list_price'] = array(
    'name' => t('List price'),
    'description' => t("The referenced product's list price."),
  );
  $tokens['cost'] = array(
    'name' => t('Cost'),
    'description' => t("The referenced product's cost."),
  );
  $tokens['sell_price'] = array(
    'name' => t('Sell price'),
    'description' => t("The referenced product's sell price."),
  );

  $tokens['weight'] = array(
    'name' => t('Weight'),
    'description' => t("The referenced product's formatted weight."),
  );

  $tokens['weight-value'] = array(
    'name' => t('Weight value'),
    'description' => t("The numerical value of the referenced product's weight."),
  );
  $tokens['weight_units'] = array(
    'name' => t('Weight units'),
    'description' => t("The unit of measurement for the referenced product's weight."),
  );

  $tokens['length'] = array(
    'name' => t('Length'),
    'description' => t("The referenced product's formatted length."),
  );
  $tokens['width'] = array(
    'name' => t('Width'),
    'description' => t("The referenced product's formatted width."),
  );
  $tokens['height'] = array(
    'name' => t('Height'),
    'description' => t("The referenced product's formatted height."),
  );

  $tokens['length-value'] = array(
    'name' => t('Length value'),
    'description' => t("The numerical value of the referenced product's length."),
  );
  $tokens['width-value'] = array(
    'name' => t('Width value'),
    'description' => t("The numerical value of the referenced product's width."),
  );
  $tokens['height-value'] = array(
    'name' => t('Height value'),
    'description' => t("The numerical value of the referenced product's height."),
  );
  $tokens['length_units'] = array(
    'name' => t('Length units'),
    'description' => t("The unit of measurement for the referenced product's length, width, and height."),
  );

  // Inherit all 'node' type tokens
  $nodetokens = node_token_info();

  return array(
    'types' => array('referenced-product' => $types),
    'tokens' => array('referenced-product' => $tokens + $nodetokens['tokens']['node']),
  );
}

/**
 * Implements hook_tokens().
 */
function uc_node_checkout_tokens($type, $tokens, $data = array(), $options = array()) {
  $language_code = NULL;
  if (isset($options['language'])) {
    $language_code = $options['language']->language;
  }
  $sanitize = !empty($options['sanitize']);

  $replacements = array();

  if ($type == 'product'                      &&
      !empty($data['product'])                &&
      uc_product_is_product($data['product'])    ) {

    $product = $data['product'];
    // We want to inherit all 'node' tokens since products are nodes,
    // so treat all tokens as node tokens first, then process them
    // as product tokens so we can add or override what node does.
    $replacements += token_generate('node', $tokens, array('node' => $product), $options);

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'model':
          $replacements[$original] = $sanitize ? check_plain($product->model) : $product->model;
          break;

        case 'list_price':
          $replacements[$original] = uc_currency_format($product->list_price);
          break;

        case 'cost':
          $replacements[$original] = uc_currency_format($product->cost);
          break;

        case 'sell_price':
          $replacements[$original] = uc_currency_format($product->sell_price);
          break;

        case 'list_price-value':
          $replacements[$original] = $product->list_price;
          break;

        case 'cost-value':
          $replacements[$original] = $product->cost;
          break;

        case 'sell_price-value':
          $replacements[$original] = $product->sell_price;
          break;

        case 'weight':
          $replacements[$original] = uc_weight_format($product->weight, $product->weight_units);
          break;

        case 'weight-value':
          $replacements[$original] = $product->weight;
          break;

        case 'weight_units':
          $replacements[$original] = $product->weight_units;
          break;

        case 'length':
          $replacements[$original] = uc_length_format($product->length, $product->length_units);
          break;

        case 'width':
          $replacements[$original] = uc_length_format($product->width, $product->length_units);
          break;

        case 'height':
          $replacements[$original] = uc_length_format($product->height, $product->length_units);
          break;

        case 'length-value':
          $replacements[$original] = $product->length;
          break;

        case 'width-value':
          $replacements[$original] = $product->width;
          break;

        case 'height-value':
          $replacements[$original] = $product->height;
          break;

        case 'length_units':
          $replacements[$original] = $product->length_units;
          break;
      }
    }

    return $replacements;
  }
}
