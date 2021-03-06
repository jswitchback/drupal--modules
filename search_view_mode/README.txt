DESCRIPTION
-----------

This module provides a custom view mode for search results of type 'node' & 'user'.


INSTALLATION
------------

1) Place this module directory in your "modules" folder (this will usually be
   "sites/all/modules/"). Don't install your module in Drupal core's "modules"
   folder, since that will cause problems and is bad practice in general. If
   "sites/all/modules" doesn't exist yet, just create it.

2) Enable the module.


TIPS
----

The view mode <em>Search Result Display</em> is disabled by default. Turn on in Manage Display settings. Template suggestions have been added in place of Drupal core's <em>search-result.tpl.php</em>.

search-result--svm.tpl.php

These can be overridden specific to the search type:

search-result--svm--SEARCHTYPE.tpl.php
Example: search-result--svm--node.tpl.php
Example: search-result--svm--user.tpl.php

And even more specific:

search-result--svm--user--ROLE.tpl.php
Example: search-result--svm--user--authenticated-user.tpl.php
search-result--svm--node--NODETYPE.tpl.php
Example: search-result--svm--node--basic-page.tpl.php

The above templates affect wrapping markup. For greater <em>$content</em> variable control, preprocess the <em>search_display</em> view mode or add a template file. The following template suggestions have been added to further customize the search output.

node--svm.tpl.php
node--svm--NODETYPE.tpl.php
Example: node--svm--basic-page.tpl.php

user-profile--svm.tpl.php
user-profile--svm--ROLE.tpl.php
Example: user-profile--svm--authenticated-user.tpl.php



AUTHOR
------

Joe Maag  ~ http://www.rapiddg.com
