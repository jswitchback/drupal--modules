DESCRIPTION
-----------

This module provides the as custom view mode for search results.


INSTALLATION
------------

1) Place this module directory in your "modules" folder (this will usually be
   "sites/all/modules/"). Don't install your module in Drupal core's "modules"
   folder, since that will cause problems and is bad practice in general. If
   "sites/all/modules" doesn't exist yet, just create it.

2) Enable the module.


TIPS
----

The view mode <em>Search Result Display</em> is disabled by default. Template suggestions have also been added: 
node--search-display.tpl.php or, more specifically, 
node--NODETYPEMACHINENAME--search-display.tpl.php. 

These will override Drupal's node.tpl.php. If you need control over the wrapping markup see Drupal's Search module for the "search-results" and "search-result" templates. A template override is also provided by this module: 
search-result--COREMODULENAME--RESULTTYPE.tpl.php. 

Where "search module" is one of Drupal's core modules that are being searched. By default these are taxonomy, user and node. Result type is the content machine name in a Node result. Use devel to output $variables in a hook_preprocess_search_result($variables) to get these. Specifically dpm($variables['result']['type']) & dpm($variables['module']).



AUTHOR
------

Joe Maag  ~ http://www.rapiddg.com
