<?php

// Override to achieve custom file images
// https://api.drupal.org/api/drupal/modules%21file%21file.module/function/theme_file_icon/7.x
function file_icons_theme_file_icon($variables) {
  $file = $variables['file'];
  $alt = $variables['alt'];
  $icon_directory = drupal_get_path('module', 'file_icons') . '/icons';;

  $mime = check_plain($file->filemime);
  $icon_url = file_icon_url($file, $icon_directory);
  return '<img class="file-icon" alt="' . check_plain($alt) . '" title="' . $mime . '" src="' . $icon_url . '" />';
}
