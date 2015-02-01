(function ($) {
  Drupal.settings.magnific_popup = Drupal.settings.magnific_popup || {};
  Drupal.settings.magnific_popup_api = Drupal.settings.magnific_popup_api || {};
  Drupal.settings.magnific_popup.common_options = {
    disableOn: 300,
    mainClass: 'mfp-fade',
    removalDelay: 160,
    preloader: false,
    fixedContentPos: 'auto',
    closeBtnInside: false,
    callbacks: {
      // Add custom class from target element data-modal-class attribute 
      // <a href="#some-inline-div" class="mfp-inline-init" data-modal-class="mfp-login">Login</a>
      beforeOpen: function() {
          var $triggerEl = $(this.st.el),
              newClass = $triggerEl.data("modal-class");

              if (newClass) {
                this.st.mainClass = this.st.mainClass + ' ' + newClass;
              }
      }
    }
  };
  Drupal.settings.magnific_popup.common_options_iframe = {
    type: 'iframe',
    iframe: {
      markup: '<div class="mfp-iframe-scaler"><div class="mfp-close"></div><iframe class="mfp-iframe" id="mfp-iframe" frameborder="0" seamless="seamless" allowfullscreen="allowfullscreen"></iframe></div>',
      patterns: {}
    }
  };
  Drupal.behaviors.magnific_popup = {
		attach: function (context, settings) {
      settings.magnific_popup = settings.magnific_popup || { common_options: {}, common_options_iframe: {}};
      var common_options = settings.magnific_popup.common_options || {};
      var common_options_iframe = settings.magnific_popup.common_options_iframe || {};
      // Allow modules to extend the set of patterns we support via iframe.
      if (settings.magnific_popup_api.iframe_patterns) {
        jQuery.extend(settings.magnific_popup.common_options_iframe.iframe.patterns, settings.magnific_popup_api.iframe_patterns);
        // There are some bugs around the delete operator, so make sure we never
        // double-up on iframe patterns.
        settings.magnific_popup_api.iframe_patterns = {};
        // Attempt to delete the iframe patterns from our settings object.
        delete settings.magnific_popup_api.iframe_patterns;
      }

      //////////////////////
      // Options presets
      //////////////////////

      var common_options_image = {
        type: 'image',
        // mainClass: 'custom-class'
        image: {
          verticalFit: false
        //   titleSrc: function(item) {
        //     return $('img.mfp-thumbnail', item.el).attr('title') || '';
        //   }
        }
      };

      var common_options_gallery = {
        gallery: {enabled: true},
        type: 'image',
        delegate: 'a'
      };

      ///////////////////
      // Instantiate
      ///////////////////

      // Instantiate no-gallery, images.
      var options = {};
      $.extend(options, common_options, common_options_image);
      $('.mfp-image-init', context).once('magnific_popup').magnificPopup(options);
      // // Instantiate no-gallery, iframes.
      options = {};
      $.extend(options, common_options, common_options_iframe);
      $('.mfp-iframe-init', context).once('magnific_popup').magnificPopup(options);
      // Instantiate inline popup for use with hidden html content
      options = {};
      $.extend(options, common_options);
      $('.mfp-inline-init', context).once('magnific_popup').magnificPopup(options);

      // Hide inline content with Magnific Popup class that's auto removed by plugin.
      inlineHref = $('.mfp-inline-init').attr('href');
      $(inlineHref).addClass('mfp-hide');

      // Instantiate galleries, images.
      options = {};
      $.extend(options, common_options, common_options_image, common_options_gallery);
      $('.mfp-gallery-image-init', context).once('magnific_popup').each(function(el, i) {
        $(this).magnificPopup(options);
      });

      // Instantiate galleries, iframes.
      options = {};
      $.extend(options, common_options, common_options_iframe, common_options_gallery);
      $('.mfp-gallery-iframe-init', context).once('magnific_popup').each(function(el, i) {
        $(this).magnificPopup(options);
      });
    }
  };
})(jQuery);
