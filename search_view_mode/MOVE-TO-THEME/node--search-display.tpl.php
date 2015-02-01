<?php
/**
 * Custom template for nodes using the view mode Search Display
 * You can also use template per content type node--CONTENT-TYPE--search-display.tpl.php
 * Template suggestions found in Search View Mode module. 
 *
 * THE INTENT IS TO FOLLLOW SEARCH RESULT MARKUP FROM CORE'S search-result.tpl.php.
 * All typical variables from Core's node.tpl.php are available.
 *
 */
?>
<div class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php print render($title_prefix); ?>
  <h3 class="title"><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h3>
  <?php print render($title_suffix); ?>
  <?php print render($content); ?>
</div><!-- /.node -->