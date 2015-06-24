<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Contact Grid Block'),
  // 'description' => t('Header large.'),
  'category' => t('Triple Quest Panes'),
  'render callback' => 'custom_panes_contact_render',
  // 'icon' => 'favicon.ico',
);

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function custom_panes_contact_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();

  $block->title = '';
  $block->content = '';

  $block->content .= '<div class="gridblock__contact">';
  $block->content .= '<div class="gridblock--inner">';
  $block->content .= '<h2 class="gridblock--title">' . t('CONTACT') . '</h2>';

  $block->content .= '<div class="contact--content">';
  $block->content .= l(t('Contact Us'), '/contact' , array('attributes' => array('class' => array('contact'))));

  $block->content .= '</div></div></div>';

  return $block;
}
