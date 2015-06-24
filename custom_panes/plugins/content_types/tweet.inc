<?php

/**
* This plugin array is more or less self documenting
*/
$plugin = array(
  'single' => FALSE,
  'title' => t('Twitter Timeline pane'),
  'description' => t('Single Tweet display.'),
  'category' => t('Triple Quest Panes'),
  'edit form' => 'custom_panes_tweet_edit_form',
  'render callback' => 'custom_panes_tweet_render',
  // 'icon' => 'favicon.ico',
  'defaults' => array( // Array of defaults for the settings form.
    'twitter_username' => 'Hydraid',
    'twitter_widget_id' => '601751339924852736',
    'tweet_count' => '1',
  ),
  'admin info' => 'custom_panes_tweet_admin_info',

);

// /**
//  * 'admin info' callback for panel pane.
//  */
function custom_panes_tweet_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = $conf['override_title'] ? $conf['override_title_text'] : '';
    $block->content = t('Showing tweets from <em>@@username</em>.', array(
      '@username' => $conf['twitter_username'],
    ));
    return $block;
  }
}


/**
 * 'Edit form' callback for the content type.
 */
function custom_panes_tweet_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  // We don't want to use standar pane title functionallity.
  $form['override_title']['#access'] = FALSE;
  $form['override_title_text']['#access'] = FALSE;
  $form['override_title_markup']['#access'] = FALSE;
  $form['override_title_heading']['#access'] = FALSE;

  $form['twitter_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter username'),
    '#description' => t('A valid twitter username.'),
    '#default_value' =>  !empty($conf['twitter_username']) ? $conf['twitter_username'] : '',
  );

  $form['twitter_widget_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter widget ID'),
    '#description' => t('Widget ID configured on Twitter in the account settings.'),
    '#default_value' =>  !empty($conf['twitter_widget_id']) ? $conf['twitter_widget_id'] : '',
  );

  $form['tweet_count'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum Tweets to show'),
    // '#description' => t(''),
    '#default_value' =>  !empty($conf['tweet_count']) ? $conf['tweet_count'] : '1',
  );

  return $form;
}


/**
* Submit function, note anything in the formstate[conf] automatically gets saved
*/
function custom_panes_tweet_edit_form_submit(&$form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
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
function custom_panes_tweet_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();
  $block->content = '';
  $block->content = '<div class="twitter"><div class="tweet" id="tweet">';

  // Twitter Embedded Timeline
  // https://dev.twitter.com/web/embedded-timelines#creating
  $block->content .= '<a class="twitter-timeline"
    width="100%"
    height="100%"
    data-chrome="noheader noborders transparent nofooter"
    data-link-color="#8e1d08"
    data-tweet-limit="' . $conf['tweet_count'] . '"
    data-dnt="true"
    data-widget-id="' . $conf['twitter_widget_id'] . '"
    data-screen-name="' . $conf['twitter_username'] . '"
    data-show-replies="false"
    href="https://twitter.com/' . $conf['twitter_username'] . '">Follow @' . $conf['twitter_username'] . ' on Twitter</a>';

  // Exposing Twitter info via Drupal.settings on the front end
  // $tweet_settings = array(
  //   'username' => $conf['twitter_username'],
  //   'widget_id' => $conf['twitter_widget_id']
  // );
  // drupal_add_js(array('custom_panes' => $tweet_settings), 'setting');

  $twitter_script = 'window.twttr = (function(d, s, id) {var js, fjs = d.getElementsByTagName(s)[0],t = window.twttr || {};if (d.getElementById(id)) return t;js = d.createElement(s);js.id = id;js.src = "https://platform.twitter.com/widgets.js";fjs.parentNode.insertBefore(js, fjs);t._e = [];t.ready = function(f) {t._e.push(f);};return t;}(document, "script", "twitter-wjs"))';
  drupal_add_js($twitter_script, array('type' => 'inline','scope' => 'footer'));

  // drupal_add_js(drupal_get_path('module', 'custom_panes') .'/plugins/js/twitter-widget.js', array('scope' => 'footer'));
  // drupal_add_js(drupal_get_path('module', 'custom_panes') .'/plugins/js/tweet-pane.js', array('scope' => 'footer'));

  $block->content .= '</div></div>';

  return $block;
}

