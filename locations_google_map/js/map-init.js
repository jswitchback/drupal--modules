(function ($) {

jQuery( document ).on( "mapScriptLoaded", function( event ) {

  /////// !!!!! @STEP: Build view with geojson output at route /api/locations

  // Get location and popup data
  // @TODO Could filter the map according to the address in the address field. Would require adding proximity filter to Store GEO JSON View
  // Example decoded urls:
  // 100 miles from zip code 48872
  // http://mcsports/store-locator?field_geofield_distance[distance]=100&field_geofield_distance[unit]=3959&field_geofield_distance[origin]=48872
  // 100 miles from "Grand Rapids, MI"
  // http://mcsports/store-locator?field_geofield_distance[distance]=100&field_geofield_distance[unit]=3959&field_geofield_distance[origin]=grand rapids, mi
  jQuery.ajax({
    url: '/api/locations',
    type: 'GET',
    dataType: 'json',
  })
  .done(function(data) {

    var map = new Map({mapCanvasId: 'map--canvas', data: data});
    handleFormInputs(map);

  })
  .fail(function() {
    alert('Failed to retrieve map data.');
  })
  .always(function() {
  });

  function handleFormInputs(map) {
    var inputText = $('#edit-field-geofield-distance-origin').val().trim();

    if (inputText) {
      map.geocodeAddress({
        address: inputText,
        callback: function(results, status) {
          if (status == google.maps.GeocoderStatus.OK) {

            // Got result, center the map and put it out there
            // self.map.setCenter(results[0].geometry.location);
            // var marker = new google.maps.Marker({
            //     map: self.map,
            //     position: results[0].geometry.location
            // });
            // Parse result & return it
            // formatted_address = results[0].formatted_address,
            // bounds = results[0].geometry.bounds,
            // location = results[0].geometry.location,
            // place_id = results[0].place_id
            // console.log(results);

            map.fitToClosestMarker(results[0].geometry.location, 3 );

          } else {
            // Possible status ZERO_RESULTS
            // google.maps.GeocoderStatus.ZERO_RESULTS

            alert("Geocode was not successful for the following reason: " + status);
          }
        }
      });
    }
  }

}); // END EVENT


})(jQuery, this, this.document);
