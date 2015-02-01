<?php

/**
 * USES A TAXONOMY REFERENCE TO SET PAGE TEMPLATE SUGGESTIONS
 */

function THEMENAME_preprocess_html(&$variables, $hook) {
  // Check if it's a node page
  if ($node = menu_get_object()) {
    // Body class for Custom Layouts on Page and Services node pages.
    if ($node->type == 'CONTENTTYPE') {
      $taxonomy_reference_field = $node->FIELD_MACHINE_NAME;

      if (!empty($taxonomy_reference_field)) {

        // Return an array of taxonomy term ID's.
        $termids = field_get_items('node', $node, $taxonomy_reference_field);
        // Load all the terms to get the name and vocab.
        foreach ($termids as $termid) {
          $terms[] = taxonomy_term_load($termid['tid']);
        }
        // Assign the taxonomy values.
        foreach ($terms as $term) {
          $tid = strtolower(drupal_clean_css_identifier($term->tid));
          $vocabulary = drupal_clean_css_identifier($term->vocabulary_machine_name);
          $variables['classes_array'][] = 'page-layout-' . $tid;
        }
      }
    }
  }

}

/**
 * Override or insert variables into the page template.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("page" in this case.)
 */

function THEMENAME_preprocess_page(&$variables, $hook) {

  if (isset($variables['node']->type)) {
    $taxonomy_reference_field = $variables['node']->FIELD_MACHINE_NAME;

    // Custom Layouts variables for Page and Services nodes. Output in page template
    // Note: this preprocess does not work in the Lawndale Page Layouts module, so it is here
    if ($variables['node']->type == 'CONTENTTYPE') {

      if (!empty($taxonomy_reference_field)) {
       $page_type = $taxonomy_reference_field[LANGUAGE_NONE][0]['tid']; // MAY VARY
       
       // Custom page template suggestion if needed. Note: must begin with "page__" or does not work.
       $variables['theme_hook_suggestions'][] = 'page__layout__' . $page_type; 

       // Example of the things you can do. This site had varying header image styles per page layout type
       // $image_uri = $variables['node']->field_header_image[LANGUAGE_NONE][0]['uri'];
       // // Raw image path fallback
       // $image_path = file_create_url($image_uri);

       // if ($page_type == 124) {
       //   // Run it through an image style to get banner style
       //   $image_path = image_style_url('page_header_banner', $image_uri);

       //   $variables['header_banner'] = array(
       //     '#markup' => '<div class="header-background" style="background-image:url(' . $image_path . ');background-repeat:no-repeat;">' . $variables['title'] .'</div>',
       //   );
       // } else {
       //   // Run it through an image style to get the background style
       //   $image_path = image_style_url('page_header_background', $image_uri);

       //   $variables['header_background'] = 'style="background-image:url(' . $image_path . ');background-repeat:no-repeat;"';
       // } 
      }
    }
  }
}
