<?php
/**
 * @file
 * Definition of views_handler_toggle_list_style.
 */

/**
 * Views area handler to switch between Views displays.
 *
 * @ingroup views_area_handlers
 */
class views_handler_toggle_list_style extends views_handler_area {
  
  function option_definition() {
    $options = parent::option_definition();
    $options['link_text'] = array('default' => '');
    $options['view_displays'] = array('default' => '');
    return $options;
  }

  
    /**
   * Default options form that provides the label widget that all fields
   * should have.
   * Also provides a list of displays to link to 
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
     // Link text
     $form['link_text'] = array(
      '#type' => 'textfield',
      '#title' => t('Link Text'),
      '#default_value' => isset($this->options['link_text']) ? $this->options['link_text'] : '',
      '#description' => t('The text which will be used as the hyperlink.'),
    );
    
    // Options for which views display to link to
    $displays = $this->view_displays();
    $form['view_displays'] = array(
      '#type' => 'select',
      '#title' => t('Select a display to link to.'),
      '#default_value' => isset($this->options['view_displays']) ? $this->options['view_displays'] : '',
      '#options' => $displays,
      '#description' => t('This display will provide the link in which we should go to.'),
    );
  
  }

  function render() {
    $view = $this->view;
    $options = $this->options;
    if (count($this->view->result) === 0) {
      return;
    } else {
      $q = drupal_get_query_parameters();
      $path = $view->display[$options['view_displays']]->display_options['path'];
      $text = $options['link_text'];
      $url = url($path, array('query' => $q));
      return "<a class='{$view->current_display} toggle-style-link' href='{$url}'>{$text}</a>";
    }
  }
  
  protected function view_displays() {
    $view = $this->view;
    $displays = array();
    $current = $view->current_display;
    foreach($view->display as $display) {
      $plugin = $display->display_plugin;
      $id = $display->id;
      $title = $display->display_options['title'];
      $status = isset($display->display_options['enabled']) && !$display->display_options['enabled'] ? FALSE : TRUE;
      // If this display is a page and it's not the current display and it's not disabled
      if($plugin == 'page'  && $id != $current && $status) {
	$displays[$id] = $title != '' ? $title . '-' . $id : $id;
      }
    }
    return $displays;
  }
  

}
