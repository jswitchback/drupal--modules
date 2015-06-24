<?php

// Plugin definition
$plugin = array(
  // Title and description of the plugin
  'title' => t('Background image'),
  'description' => t('Background image style.'),
  // Theme function for this plugin
  'render region' => 'panels_background_image_style_render_region',
  // Template for rendering
  'hook theme' => array(
    'panels_background_image_style' => array(
      'variables' => array(
        'content' => NULL,
        'style_attributes' => array(),
      ),
      'path' => drupal_get_path('module', 'panels_background_image') . '/plugins/styles',
      'template' => 'panels-background-image',
    ),
  ),
  // Settings form for the plugin
  'settings form' => 'panels_background_image_style_settings_form',
  'defaults' => array( // Array of defaults for the settings form.
    'image' => '%node:field_image',
    'image_style_sd' => '',
    'image_style_hd' => '',
    'class' => '',
  ),
);


/**
 * Settings form callback.
 */
function panels_background_image_style_settings_form($form, $form_state) {
  $form['image'] = array(
    '#type' => 'textfield',
    '#title' => t('Image field'),
    '#description' => t('Enter the image field for the background image. You may use substitutions in this field. E.g. for the default image field attached to articles use "%node:field_image". Substitutions can be found in Panels <em>content</em> configuration page.'),
    '#required' => TRUE,
    '#default_value' => (isset($form['image'])) ? $form['image'] : '%node:field_image',
    '#weight' => 1,
  );
  $form['image_style'] = array(
    '#type' => 'select',
    '#title' => t('Image Style (Standard Definition -1x)'),
    '#description' => t('Choose the appropriate image style for the background image.'),
    '#options' => image_style_options(),
    '#default_value' => (isset($form['image_style'])) ? $form['image_style'] : '',
    '#weight' => 2,
  );
  $form['image_style_hd'] = array(
    '#type' => 'select',
    '#title' => t('Image Style (High Definition - 2x)'),
    '#description' => t('Choose the appropriate image style for the background image.'),
    '#options' => image_style_options(),
    '#default_value' => (isset($form['image_style_hd'])) ? $form['image_style_hd'] : '',
    '#weight' => 3,
  );
  $form['class'] = array(
    '#type' => 'textfield',
    '#title' => t('CSS Classes'),
    '#description' => t('Enter CSS classes for this style. Separate multiple classes by spaces.'),
    '#default_value' => (isset($form['class'])) ? $form['class'] : '',
    '#weight' => 4,
  );

  return $form;
}

/**
 * Render callback.
 */
function theme_panels_background_image_style_render_region($variables) {
  $image_url_sd = NULL;
  $image_url_hd = NULL;
  $inline_css = NULL;
  $content = implode($variables['panes']);
  $variables['display']->has_image = FALSE;

  // Get the absolute path of the original image from the context substitution
  $image_abs_path = ctools_context_keyword_substitute($variables['settings']['image'], array(), $variables['display']->context);

  // Bail if there is no image associated
  if (!$image_abs_path) {
    return $content;
  } else {
    // Add variable to use in template file
    $variables['display']->has_image = TRUE;
  }

  $image_style_sd = (isset($variables['settings']['image_style'])) ? $variables['settings']['image_style'] : '';
  $image_style_hd = (isset($variables['settings']['image_style'])) ? $variables['settings']['image_style'] : '';

  if ($image_style_sd !== '' || $image_style_hd !== '') {
    // Image style is provided in the settings form.
    // We need to get the original image uri to return the URL for an image derivative.
    global $base_url;
    $files_rel_path = variable_get('file_public_path', conf_path() . '/files');
    $image_rel_path = str_replace($base_url . '/' . $files_rel_path, '', $image_abs_path);
    $image_uri = file_build_uri($image_rel_path);
  }

  // Standard Definition image path
  if ($image_style_sd == '') {
    // If no image style is selected, use the original image.
    $image_url_sd = $image_abs_path;
  } else {
    $image_style_url_sd = image_style_url($image_style_sd, $image_uri);
    $image_url_sd = $image_style_url_sd;
    $image_info_sd = image_get_info($image_url_sd);
  }

  // High Definition image path
  if ($image_style_hd == '') {
    $image_url_hd = $image_abs_path;
  } else {
    $image_style_url_hd = image_style_url($image_style_hd, $image_uri);
    $image_url_hd = $image_style_url_hd;
  }

  $style_attributes = array();

  // Add our classes to the attrubutes array, if any defined
  if ($variables['settings']['class']) {
    $style_attributes['class'] = explode(' ', $variables['settings']['class']);
  }

  $style_attributes['class'][] = 'panel-background';

  // @TODO: Maybe tie display id to class for multiple images on one page $variables['display']['did'], depends on how 'dids' get assigned.
  $inline_css = '
    .panel-background {
      background-image: url(' . $image_url_sd . ');
    };
    @media
    only screen and (-webkit-min-device-pixel-ratio: 2),
    only screen and (   min--moz-device-pixel-ratio: 2),
    only screen and (     -o-min-device-pixel-ratio: 2/1),
    only screen and (        min-device-pixel-ratio: 2),
    only screen and (                min-resolution: 192dpi),
    only screen and (                min-resolution: 2dppx) {
      .panel-background {
        background-image: url(' . $image_url_hd . ');
      }
      .no-backgroundsize .panel-background {
        background-image: url(' . $image_url_sd . ');
      }
    };';

  drupal_add_css($inline_css, array('type' => 'inline',));

  return theme('panels_background_image_style', array(
      'content' => $content,
      'style_attributes' => $style_attributes,
    )
  );
}

