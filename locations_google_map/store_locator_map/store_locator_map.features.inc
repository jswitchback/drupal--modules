<?php
/**
 * @file
 * store_locator_map.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function store_locator_map_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function store_locator_map_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function store_locator_map_node_info() {
  $items = array(
    'store' => array(
      'name' => t('Store'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
