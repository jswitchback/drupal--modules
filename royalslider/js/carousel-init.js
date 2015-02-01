(function ($) {
  
$(window).load(function() {


  ////////////////////////
  // HOMEPAGE BANNER
  ///////////////////////

  $('.rs-slideshow .field-items').royalSlider({
    autoScaleSlider: true,
    autoScaleSliderHeight: 336,
    // arrowsNavAutoHide: false,
    arrowsNav: false,
    autoHeight: true,
    numImagesToPreload: 2,
    autoPlay: {
      enabled: true,
      pauseOnHover: true,
      delay: 5000
    },
    sliderDrag: false,
    transitionType: 'fade',
    addActiveClass: true,
    navigateByClick: false,
    controlNavigation: 'bullets',
    controlsInside: true,
    block: {
      // animated blocks options go here
      fadeEffect: true,
      moveEffect: 'bottom',
      moveOffset: 40,
      speed: 400
    }
  });

}); // END .load()


// $(window).resize(function() {

//   // Throttle resize event
//   on_resize(function() {
//   })();

// });



// debulked onresize handler // https://github.com/louisremi/jquery-smartresize
// function on_resize(c,t){
//   onresize = function() {
//     clearTimeout(t);
//     t=setTimeout(c,100);
//   };
//   return c;
// };

} (jQuery));