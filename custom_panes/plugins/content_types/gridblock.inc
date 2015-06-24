<?php

$plugin = array(
  'single' => FALSE,
  'title' => t('Grid Block'),
  'description' => t('Large home page image and tag lines.'),
  'category' => t('Triple Quest Panes'),
  'edit form' => 'custom_panes_gridblock_edit_form',
  'render callback' => 'custom_panes_gridblock_render',
  'icon' => 'favicon.ico',
  'defaults' => array( // Array of defaults for the settings form.
    'url' => '',
    'pane_classes' => '',
    'pane_style_options' => 'style_1',
    'pane_image' => '',
    'image_style' => '',
    'title' => '',
    'subtitle' => '',
    'pane_description' => '',
    'show_button' => TRUE,
    'button_path' => '',
    'button_text' => 'Learn more',
    'button_style' => 'style1',
  ),
  'admin info' => 'custom_panes_gridblock_admin_info',
);

/**
 * 'admin info' callback for panel pane.
 */
function custom_panes_gridblock_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = !empty($conf['title']) ? $conf['title'] : t('Grid Block');
    // $block->content = t('@title', array(
    //   '@title' => $conf['title'],
    // ));
    return $block;
  }
}

/**
 * 'Edit form' callback for the content type.
 */
function custom_panes_gridblock_edit_form($form, &$form_state) {
  $form['#attributes']['enctype'] = array("multipart/form-data");
  form_load_include($form_state, 'inc', 'custom_panes','plugins/content_types/gridblock');
  $conf = $form_state['conf'];

  // dpm($form_state['pane']);

  // We don't want to use standard pane title functionallity.
  $form['override_title']['#access'] = FALSE;
  $form['override_title_text']['#access'] = FALSE;
  $form['override_title_markup']['#access'] = FALSE;
  $form['override_title_heading']['#access'] = FALSE;


  $pane_style_options = array(
    'style_1' => t('Default'),
    'style_2' => t('Slogan plus description'),
    'style_3' => t('Small text plus slogan'),
  );

  $form['pane_style_options'] = array(
    '#type' => 'select',
    '#title' => t('Select text style'),
    '#options' => $pane_style_options,
    '#default_value' => !empty($conf['pane_style_options']) ? $conf['pane_style_options'] : 'style_1',
    // '#states' => array(
    //   'visible' => array(
    //     ':input[name="show_button"]' => array('checked' => TRUE),
    //   ),
    // ),
  );

  $form['pane_image'] = array(
    '#title' => t('Background image'),
    '#type' => 'managed_file',
    '#name' => 'pane_image',
    //'#required' => TRUE,
    '#description' => t('Upload a background image. Square images should be 750px x 750px. Rectangle images should be 370px x 750px.'),
    '#default_value' => !empty($conf['pane_image']) ? $conf['pane_image'] : '',
    '#upload_location' => 'public://gridblock_pane_images/',
    '#upload_validators' => array(
       'file_validate_extensions' => array('gif png jpeg jpg')
     ),
    '#array_parents' => array('pane_image')
  );

  $form['image_style'] = array(
    '#type' => 'select',
    '#title' => t('Image Style'),
    '#description' => t('Choose the appropriate image style for the background image.'),
    '#options' => image_style_options(),
    '#default_value' => (isset($form['image_style'])) ? $form['image_style'] : '',
  );

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title text'),
    '#default_value' =>  !empty($conf['title']) ? $conf['title'] : '',
  );

  $form['subtitle'] = array(
    '#type' => 'textfield',
    '#title' => t('Subtitle text'),
    '#default_value' =>  !empty($conf['subtitle']) ? $conf['subtitle'] : '',
  );

  $form['pane_description'] = array(
    '#title' => t('Content'),
    '#type' => 'text_format',
    '#format' => 'wysiwyg',
    '#description' => t('Please enter the content for the custom pane here.'),
    '#default_value' => !empty($conf['pane_description']['value']) ? $conf['pane_description']['value'] : '',
    '#cols' => 40,
    '#rows' => 6,
    '#resizable' => TRUE,
    // '#required' => TRUE,
  );

  $form['pane_classes'] = array(
    '#type' => 'textfield',
    '#title' => t('Classes for wrapping pane element.'),
    '#description' => t('Use a comma separated list for multiple classes: my-class,my-other-class.'),
    '#default_value' =>  !empty($conf['pane_classes']) ? $conf['pane_classes'] : '',
  );

  $form['url'] = array(
    '#type' => 'textfield',
    '#title' => t('Destination url for button'),
    '#default_value' =>  !empty($conf['url']) ? $conf['url'] : '',
  );

  $form['show_button'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show button'),
    '#default_value' =>  !empty($conf['show_button']) ? TRUE : FALSE,
  );

  $button_options = array(
    'style1' => t('Default'),
    'style2' => t('Outline'),
    'style3' => t('Arrow'),
  );

  $form['button_style'] = array(
    '#type' => 'select',
    '#title' => t('Select button style'),
    '#options' => $button_options,
    '#default_value' => !empty($conf['button_style']) ? $conf['button_style'] : 'style1',
    '#states' => array(
      'visible' => array(
        ':input[name="show_button"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['button_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Button text'),
    '#default_value' =>  !empty($conf['button_text']) ? $conf['button_text'] : 'Learn more',
    '#states' => array(
      'visible' => array(
        ':input[name="show_button"]' => array('checked' => TRUE),
      ),
    ),
  );

  return $form;
}

/**
 * Validate handler for example block edit form.
 */
// function custom_panes_gridblock_edit_form_validate($form, &$form_state) {
// }

/**
 * The submit form stores the data in $conf.
 */
function custom_panes_gridblock_edit_form_submit($form, &$form_state) {
  // $form_state appears to be empty unless click submit twice. First submit gets sequel error,
  // Second submit gets 'The file used in the Background image field may not be referenced.' error.
  // I think '$form_state['pane']->pid' is empty in call to file_usage_add
  form_load_include($form_state, 'inc', 'custom_panes','plugins/content_types/gridblock');
  // dpm($form_state['pane']->pid);

  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      switch ($key) {
        case 'pane_image':
          // Saving the file, setting it to a permanent state, setting a FID variable
          $file = file_load($form_state['values'][$key]);
          $file->status = FILE_STATUS_PERMANENT;
          file_save($file);
          file_usage_add($file, 'custom_panes', 'gridblock_edit_form', $form_state['pane']->pid);
          break;
      }
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

/**
 * Run-time rendering of the body of the block.
 *
 * @param $subtype
 * @param $conf
 *   Configuration as done at admin time.
 * @param $args
 * @param $context
 *   Context - in this case we don't have any.
 *
 * @return
 *   An object with at least title and content members.
 */
function custom_panes_gridblock_render($subtype, $conf, $panel_args, $context = NULL) {
  // You can get the node entity from the $context via $context->data.
  $block = new stdClass();
  $block->content = '';
  $image_url = NULL;
  $style_attributes = NULL;
  $image = array();
  $button_text = '';
  $button_style = '';
  $title = '';
  $subtitle = '';
  $classes = array();


  if (!empty($conf['pane_classes'])) {
    $classes['class'] = explode(',', $conf['pane_classes']);
  }
  // General styling class
  $classes['class'][] = 'gridblock-item';

  if (!empty($conf['pane_style_options'])) {

    switch ($conf['pane_style_options']) {
      case 'style_1':
        $classes['class'][] = 'gridblock-style__default';
        break;
      case 'style_2':
        $classes['class'][] = 'gridblock-style__long';
        break;
      case 'style_3':
        $classes['class'][] = 'gridblock-style__short';
        break;
      default:
        $classes['class'][] = 'gridblock-style__default';
        break;
    }

  } else {
    $classes['class'][] = 'gridblock-style__default';
  }

  if (!empty($conf['pane_image'])) {
    // Capture the image file path and form into HTML with attributes
    $image_file = file_load($conf['pane_image'], '');
    $image_path = '';

    if (isset($image_file->uri)) {
      $image_uri = $image_file->uri;
      $image_style = $conf['image_style'];

      if ($image_style == '') {
        // If no image style is selected, use the original image.
        $image_url = file_create_url($image_uri);
        // $image_info = getimagesize($image_url); // If we want to add height in style attribute.
      } else {
        // Image style is provided in the settings form.
        $image_style_url = image_style_url($image_style, $image_uri);
        $image_url = $image_style_url;
        // $image_info = image_get_info($image_uri);
      }

      $style_attributes = 'style="background-image: url(' . $image_url . ')";';
      // $style_attributes['style'] = 'background-image: url(' . $image_url . ');height:' . $image_info[1] .'px;';
      $classes['class'][] = 'has-background-image';
    }
  }

  if (!empty($conf['url'])) {
    $path = trim($conf['url']);
  }

  $block->content = '<div ' . drupal_attributes($classes) . '><div class="gridblock--inner"' . $style_attributes . '>';

  // $inline_css .= '.pane-hero {height:' . $image_info2['height'] . 'px' . ';background-image: url('. file_create_url($image_uri2) .');}';
  // drupal_add_css(
  //  $inline_css,
  //   array(
  //     'group' => CSS_THEME,
  //     'type' => 'inline',
  //   )
  // );

  $block->content .= '<div class="gridblock--text">';

  if (!empty($conf['title'])) {
    $title = t($conf['title']);
    $block->content .= '<h2 class="gridblock--title">' . $title . '</h2>';
  }

  if (!empty($conf['subtitle'])) {
    $subtitle = t($conf['subtitle']);
    $block->content .= '<h3 class="gridblock--subtitle">' . $subtitle . '</h3>';
  }

  if (!empty($conf['pane_description']['value'])) {
    $title = t($conf['title']);
    $block->content .= '<div class="gridblock--description">' . $conf['pane_description']['value'] . '</div>';
  }

  $block->content .= '</div>';

  if (isset($conf['show_button']) && $conf['show_button'] && !empty($conf['url'])) {
    $button_style= $conf['button_style'];
    $button_text = t($conf['button_text']);

    switch ($button_style) {
      case 'style2':
        $btn_class = 'btn__outline';
        break;
      case 'style3':
        $btn_class = 'btn__arrow';
        break;
      default:
        $btn_class = 'btn__default';
        break;
    }

    $block->content .= l($button_text, $path , array('attributes' => array('class' => array($btn_class))));

  }

  $block->content .= '</div></div>';

  return $block;
}
