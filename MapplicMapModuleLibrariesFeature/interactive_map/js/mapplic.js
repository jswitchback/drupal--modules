Drupal.behaviors.InitializeInteractiveMap = {
  attach: function (context, settings) {
    jQuery("#interactive-map").mapplic(Drupal.settings.interactive_map);
  }
};
