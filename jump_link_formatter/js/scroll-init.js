(function ($, Drupal, window, document, undefined) {

  $(document).ready(function() {

    var offsetScroll = 0,
        $header = $('#header-wrapper');

        // console.log($header.css('position') === 'fixed');

    // Account for fixed header on desktop
    if ($header.css('position') === 'fixed') { offsetScroll -= $header.height();}

    // https://github.com/kswedberg/jquery-smooth-scroll
    $('a.auto-scroll').smoothScroll({offset: offsetScroll});

  }); // END Ready

})(jQuery, Drupal, this, this.document);

