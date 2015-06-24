(function ($, Drupal, window, document, undefined) {


  $(document).ready(function($) {
    var username = Drupal.settings.triplequest_panes.username;



    // Wait for the asynchronous resources to load
    twttr.ready(function (twttr) {

    console.log('twitter ready');

      twttr.widgets.load(
        document.getElementById("tweet")
      );
      // Now bind our custom intent events
      // twttr.events.bind('click', clickEventToAnalytics);
      // twttr.events.bind('tweet', tweetIntentToAnalytics);
      // twttr.events.bind('retweet', retweetIntentToAnalytics);
      // twttr.events.bind('favorite', favIntentToAnalytics);
      // twttr.events.bind('follow', followIntentToAnalytics);
    });

    console.log(username);


  });

  // new TWTR.Widget({
  //   version:2,
  //   type:'profile',
  //   rpp:3,
  //   interval:6000,
  //   width:'auto',
  //   height:'auto',
  //   theme:{shell:{background:'#ffffff',color:'#000000'},
  //   tweets:{background:'#ffffff',color:'#000000',links:'#227eb3'}
  // },
  // features:{scrollbar:false,loop:false,live:false,hashtags:true,timestamp:true,avatars:false,behavior:'all'}
  // }).render().setUser(username).start();

})(jQuery, Drupal, this, this.document);
