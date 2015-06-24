/** @constructor */

// Expecting an object to initiate "new MCMap":
// var map = new MCMap({mapCanvasId: 'mcmap--canvas', data: data});
// {
//   mapCanvasId: '', // HTML ID
//   data: data  // GeoJson
// }

function Map (options) {
  var self = this,
      geoLocateControl;

  self.setMapData(options.data);

  if (!(typeof window.google === 'object' && window.google.maps)) {
    throw 'Google Maps API is required. Please register the following JavaScript library http://maps.google.com/maps/api/js?sensor=true.';
  }

  this.mapOptions = {
    // scrollwheel: false, // Disable scroll zoom feature.
    mapTypeId: 'roadmap',
    zoom: 6,
    panControl: false,
    zoomControl: false,
    mapTypeControl: true,
    scaleControl: false,
    streetViewControl: false,
    overviewMapControl: false,
    center: self.getLatLng(42.9563584,-85.660089),
    mapTypeControlOptions: {
      mapTypeIds: [google.maps.MapTypeId.ROADMAP, 'map_style']
    }
  };

  this.map = new google.maps.Map(document.getElementById(options.mapCanvasId),this.mapOptions);
  this.styles = [{featureType:"all",elementType:"all",stylers:[{saturation:"-100"}]},{featureType:"landscape",elementType:"labels",stylers:[{visibility:"off"}]},{featureType:"poi",elementType:"labels",stylers:[{visibility:"off"}]},{featureType:"road",elementType:"geometry",stylers:[{lightness:57}]},{featureType:"road",elementType:"labels.text.fill",stylers:[{visibility:"on"},{lightness:24}]},{featureType:"road",elementType:"labels.icon",stylers:[{visibility:"off"}]},{featureType:"transit",elementType:"labels",stylers:[{visibility:"off"}]},{featureType:"water",elementType:"labels",stylers:[{visibility:"off"}]}];

  var styledMapOptions = {name: 'McSports'};

  // Create styled map object to pass in to map
  var styledMap = new google.maps.StyledMapType(self.styles, styledMapOptions);

  // Associate the styled map with the MapTypeId and set it to display.
  this.map.mapTypes.set('map_style', styledMap);
  self.map.setMapTypeId('map_style');

  // Quick and dirty to plot points except infowindows don't auto load
  // self.map.data.loadGeoJson('http://mcsports/api/locations');

  // Parse data & add Markers
  this.addMarkers(this.getMapData());

  // Add Gelocation control
  if (navigator.geolocation) {
    this.createGeolocateControl();
  }

  /* Private Utility Functions */

  this.metersToMiles = function(meters) {
    return (parseInt(meters, 10) / 1609.344);
  };
}


/** @prototype / Public methods */


// MCMap.prototype.init = function(options, data) {
// };

MCMap.prototype.setMapData = function(data) {
  this.locationData = data;
};

MCMap.prototype.getMapData = function() {
  return this.locationData;
};

MCMap.prototype.setCenter = function(position) {
  var self = this;
  self.map.setCenter(position);
};

MCMap.prototype.setZoom = function(value) {
  var self = this;
  self.map.setZoom(value);
};

MCMap.prototype.getLatLng = function(lat, lng) {
  return new google.maps.LatLng(lat, lng);
};

// EXAMPLE GEOJSON
// {
//   type: "FeatureCollection",
//   features: [{
//     type: "Feature",
//     geometry: {
//     type: "Point",
//     coordinates: [-93.578207,41.713349]
//   },
//   properties: {
//   name: "Interstate Shopping Center",
//   description: "<article class="node-7906 node node-store node-teaser contextual-links-region clearfix"> <header> <h2 class="node__title"><a href="/interstate-shopping-center">Interstate Shopping Center</a></h2> <div class="contextual-links-wrapper"><ul class="contextual-links"><li class="node-edit first"><a href="/node/7906/edit?destination=api/locations">Edit</a></li> <li class="node-delete last"><a href="/node/7906/delete?destination=api/locations">Delete</a></li> </ul></div> <p class="submitted"> by <span class="author"><a href="/users/rdg-admin" title="View user profile." class="username">rdg-admin</a></span> on <span class="list-date"><time>December 31, 2011</span> </p> </header> <ul class="links inline"><li class="node-readmore first last"><a href="/interstate-shopping-center" rel="tag" title="Interstate Shopping Center">Read more<span class="element-invisible"> about Interstate Shopping Center</span></a></li> </ul> </article> "
//   }
// },
MCMap.prototype.addMarkers = function(data) {
  var self = this,
      length = data.features.length;

  for (var i = 0; i < length; i++) {

      var lat = data.features[i].geometry.coordinates[1],
          lng = data.features[i].geometry.coordinates[0],
          content = data.features[i].properties.description;

      self.addMarker(lat, lng, content);
  }
};

MCMap.prototype.addMarker = function(lat, lng, content) {
  var self = this,
      latLng = this.getLatLng(lat, lng),
      marker = new google.maps.Marker({
        position: latLng,
        icon: {
            url: 'sites/all/modules/custom/mc_stores/images/marker@2x.png',
            size : new google.maps.Size(30, 54),
            scaledSize : new google.maps.Size(15, 27)
            // origin:  new google.maps.Point(0,0),
            // anchor:  new google.maps.Point(0,0)
        }
        // title: 'Hello World!' // Rollover title
      }),

      infowindow = new google.maps.InfoWindow({
        content: content
      });

  marker.setMap(self.map);

  google.maps.event.addListener(marker, 'click', function() {
    infowindow.open(self.map, marker);
  });
};

MCMap.prototype.createGeolocateControl = function(options) {
  var self = this;

  geoLocateControl = document.createElement('div');

  geoLocateControl.style.cursor = 'pointer';
  geoLocateControl.style.fontFamily = 'Roboto, Arial, sans-serif';
  geoLocateControl.style.fontSize = '14px';
  geoLocateControl.style.marginTop = '25px';
  geoLocateControl.style.marginLeft = '25px';
  geoLocateControl.style.padding = '4px 8px';
  geoLocateControl.style.backgroundColor = '#ffffff';
  geoLocateControl.style.boxShadow = 'rgba(0, 0, 0, 0.298039) 0px 1px 4px -1px';
  geoLocateControl.title = 'Click to center map around your location';
  geoLocateControl.id = 'geolocate';
  geoLocateControl.classes = 'icon-compass';
  geoLocateControl.innerHTML = '<span class="icon icon-compass">Geolocate</span>';
  self.map.controls[google.maps.ControlPosition.TOP_LEFT].push(geoLocateControl);

  google.maps.event.addDomListener(geoLocateControl, 'click', function(){
    self.setCurrentLocation();
    geoLocateControl.className = "geolocating";
  });
};

MCMap.prototype.setCurrentLocation = function() {
  var self = this;

  if (navigator.geolocation) {
    navigator.geolocation.getCurrentPosition(function(position) {
      var currentPosition = self.getLatLng(position.coords.latitude, position.coords.longitude);
      var infowindow = new google.maps.InfoWindow({
        map: self.map,
        position: currentPosition,
        content: 'You are about here.'
      });

      self.fitToClosestMarker(currentPosition, 3);

      geoLocateControl.className = "";

    }, function() {
      self.handleNoGeolocation(true, status);
    });

  } else {
    // Browser doesn't support Geolocation
    self.handleNoGeolocation(false, status);
  }
};

MCMap.prototype.handleNoGeolocation = function(errorFlag, status) {
  var self = this;

  if (errorFlag) {
    alert('You must allow geolocation to use this feature.');
  } else {
    alert('Error: Your browser doesn\'t support geolocation.');
  }
  geoLocateControl.className = "";
};

MCMap.prototype.fitToClosestMarker = function(originLatLng, pointCount) {
  var self = this,
      data = self.getMapData(),
      length = data.features.length,
      distance,
      shortestDistance,
      latLng,
      closestMarker = self.mapOptions.center,
      markerArray = [],
      fitToInteger = pointCount ? pointCount : 2;

  // Build array of markers and their distances from the origin point.
  for (var i = 0; i < length; i++) {
    latLng = self.getLatLng(data.features[i].geometry.coordinates[1], data.features[i].geometry.coordinates[0]);
    distance = self.metersToMiles(google.maps.geometry.spherical.computeDistanceBetween(originLatLng, latLng));

    markerArray.push({point: latLng, distance: distance });
  }

  // Sort array by distance. Shortest to farthest
  markerArray.sort(function(a, b){
    var distanceA = a.distance,
        distanceB = b.distance;
    if(distanceA < distanceB) return -1;
    if(distanceA > distanceB) return 1;
    return 0;
  });

  latLngBounds = new google.maps.LatLngBounds();
  latLngBounds.extend(originLatLng);

  // Add marker points to fit bounds
  for (var p = fitToInteger - 1; p >= 0; p--) {
    latLngBounds.extend(markerArray[p].point);
  }

  self.map.fitBounds(latLngBounds);

};

MCMap.prototype.alertModalMessage = function(message) {
  if (Drupal.behaviors.magnific_popup) {
    var modalHTML = '<div class="map-message">' + message + '</div>';

    // Extending options given in Magnific Popup module
    var options = {
      mainClass: 'mfp-fade mfp-map-alert',
      items: {
        type: 'inline',
        src: modalHTML // can be a HTML string, jQuery object, or CSS selector
      }
    };
    jQuery.magnificPopup.open(options);

  } else {
    alert(message);
  }
};

// Geocode zip
MCMap.prototype.geocodeAddress = function(options) {
  var self = this,
      geocoder = new google.maps.Geocoder();

  geocoder.geocode( { 'address': options.address}, function(results, status) {
    options.callback(results, status);
  });
};
