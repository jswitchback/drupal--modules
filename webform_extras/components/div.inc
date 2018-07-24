<?php

/**
 * @file
 * Webform module div component.
 */

/**
 * Implements _webform_defaults_component().
 */
function _webform_defaults_div() {
  return array(
      'name' => '',
      'form_key' => NULL,
      'pid' => 0,
      'weight' => 0,
      'extra' => array(
        'title_display' => 0,
        'private' => FALSE,
      ),
  );
}

/**
 * Generate the form for editing a component.
 *
 * Create a set of form elements to be displayed on the form for editing this
 * component. Use care naming the form items, as this correlates directly to the
 * database schema. The component "Name" and "Description" fields are added to
 * every component type and are not necessary to specify here (although they
 * may be overridden if desired).
 *
 * @param $component
 *   A Webform component array.
 *
 * @return array
 *   An array of form items to be displayed on the edit component page
 */
function _webform_edit_div($component) {
    $form = array();

    // Disabling the description.
    $form['description'] = array();

    // Most options are stored in the "extra" array, which stores any settings
    // unique to a particular component type.
    // $form['extra']['options'] = array(
    //   '#type' => 'textarea',
    //   '#title' => t('Options'),
    //   '#default_value' => $component['extra']['options'],
    //   '#description' => t('Key-value pairs may be entered separated by pipes. i.e. safe_key|Some readable option') . ' ' . theme('webform_token_help'),
    //   '#cols' => 60,
    //   '#rows' => 5,
    //   '#weight' => -3,
    //   '#required' => TRUE,
    // );
    return $form;
}



/**
 * Implements _webform_render_component().
 */
function _webform_render_div($component, $value = NULL, $filter = TRUE, $submission = NULL) {
    $node = isset($component['nid']) ? node_load($component['nid']) : NULL;
  
    $element = array(
      '#type' => 'div',
      // '#title' => $filter ? webform_filter_xss($component['name']) : $component['name'], // Prevents display of nested elements. Need custom theme function to prevent this
      '#title_display' => $component['extra']['title_display'] ? $component['extra']['title_display'] : NULL,
      '#weight' => $component['weight'],
      // '#attributes' => array('class' => array('webform-component-div')),
      '#theme_wrappers' => array('webform_element'),
      '#translatable' => array('title'),
    );

    return $element;
  }

/**
 * Display the result of a submission for a component.
 *
 * The output of this function will be displayed under the "Results" tab then
 * "Submissions". This should output the saved data in some reasonable manner.
 *
 * @param $component
 *   A Webform component array.
 * @param $value
 *   An array of information containing the submission result, directly
 *   correlating to the webform_submitted_data database table schema.
 * @param $format
 *   Either 'html' or 'text'. Defines the format that the content should be
 *   returned as. Make sure that returned content is run through check_plain()
 *   or other filtering functions when returning HTML.
 * @param $submission
 *   The submission. Used to generate tokens.
 *
 * @return array
 *   A renderable element containing at the very least these properties:
 *    - #title
 *    - #weight
 *    - #component
 *    - #format
 *    - #value
 *   Webform also uses #theme_wrappers to output the end result to the user,
 *   which will properly format the label and content for use within an e-mail
 *   (such as wrapping the text) or as HTML (ensuring consistent output).
 */
function _webform_display_div($component, $value, $format = 'html', $submission = array()) {
    return array(
      '#title' => $component['name'],
      '#weight' => $component['weight'],
      // '#theme' => 'webform_display_div', // Has not been implemented
      '#theme_wrappers' => $format == 'html' ? array('webform_element') : array('webform_element_text'),
      // '#post_render' => array('webform_element_wrapper'),
      // '#field_prefix' => $component['extra']['field_prefix'],
      // '#field_suffix' => $component['extra']['field_suffix'],
      '#component' => $component,
      '#format' => $format,
      '#value' => isset($value[0]) ? $value[0] : '',
    );
  }