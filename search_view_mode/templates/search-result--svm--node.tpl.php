<?php
/**
 * Removes submitted which is handled in the node--svm.tpl.php output.
 */
?>
<li class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php print render($title_prefix); ?>
  <h3 class="title"<?php print $title_attributes; ?>>
    <a href="<?php print $url; ?>"><?php print $title; ?></a>
  </h3>
  <?php print render($title_suffix); ?>
  <div class="search-snippet-info">
    <?php if ($snippet): ?>
      <div class="search-snippet"<?php print $content_attributes; ?>><?php print $snippet; ?></div>
    <?php endif; ?>
  </div>
</li>
