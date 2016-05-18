<?php

/**
 * @file
 * Views integration for uc_node_checkout module.
 *
 * Creates a relationship between the created node and the associated order
 * line number.
 */


/**
 * Implements hook_views_data().
 */
function uc_node_checkout_views_data() {

  // Definition for the uc_node_checkout_order_products bridge table.
  $data['uc_node_checkout_order_products']['table']['group'] = t('UC Node Checkout');
  $data['uc_node_checkout_order_products']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
      'type' => 'LEFT',
    ),
    'uc_order_products' => array(
      'left_field' => 'order_product_id',
      'field' => 'order_product_id',
      'type' => 'LEFT',
    ),
  );

  $data['uc_node_checkout_order_products']['order_product_id'] = array(
    'title' => t('Ordered product'),
    'help' => t('Relate a purchased node to the ordered product it was purchased with.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'uc_order_products',
      'base field' => 'order_product_id',
      'field' => 'order_product_id',
      'label' => t('product'),
    ),
  );

  $data['uc_node_checkout_order_products']['nid'] = array(
    'title' => t('UC Node Checkout node'),
    'help' => t('Relate an order product to UC Node Checkout created node.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'node',
      'base field' => 'nid',
      'field' => 'nid',
      'label' => t('UC Node Checkout node'),
    ),
  );

  return $data;
}
