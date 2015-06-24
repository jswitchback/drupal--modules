function loadScript() {
  var script = document.createElement('script');
  script.type = 'text/javascript';
  script.src = 'https://maps.googleapis.com/maps/api/js?v=3.exp' +
      '&libraries=geometry&signed_in=false&callback=scriptLoaded';
  document.body.appendChild(script);
}
window.onload = loadScript;

// Alerts script has loaded. Using this to initialize map and act on the script from any js file.
function scriptLoaded() {
  // https://learn.jquery.com/events/introduction-to-custom-events/
  jQuery( document ).trigger( "mapScriptLoaded");
}
