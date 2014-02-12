<?php
/**
 * @file
 * Views integration for List style toggle.
 */

/**
 * Implements hook_views_data_alter().
 */
function views_toggle_list_style_views_data_alter(&$data) {
  // Toggle List Styles
  $data['views']['toggle_list_style'] = array(
    'title' => t('Toggle Result Style'),
    'help' => t('Choose a page display from this View to provide a link to.'),
    'area' => array(
      'handler' => 'views_handler_toggle_list_style',
    ),
  );
}