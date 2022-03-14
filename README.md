Insert
======

Insert is a utility that makes inserting images and links to files into
textareas or WYSIWYGs much easier. It adds a simple JavaScript-based button to
File and Image fields. Images may be inserted into textareas with a specific
image style.

Installation
------------

1. Install this module using the official Backdrop CMS instructions at
   https://backdropcms.org/guide/modules.

1. If planning to use Insert with Images, make sure the core Image module is
   enabled.

1. Add or configure a File or Image field under Administer > Structure > Content
   types > [TYPE] > Manage fields (admin/structure/types/manage/[type]/fields).
   When configuring a field, there is a new section in the Field options for
   "Insert". You can then configure the field to include an Insert button and
   choose what templates you would like to have.

1. Create a piece of content with the configured field. After uploading a file,
   an "Insert" button will appear. Click this button to send the file or image
   into the Body field.

   Insert should work on multiple fields (the last field that was active will
   receive the file), and with most popular WYSIWYG editors.

Theming
-------

Insert can be configured to work with non-HTML filters like BBCode or Markdown.
To do this, copy the template file you would like to change from the "templates"
directory to your active theme's directory. Then clear your caches.

The Image templates may also be used per Image style. You can copy the
`image-insert-image.tpl.php` file to your theme directory and then rename it to
`image-insert-image--[style-name].tpl.php`, where `[style-name]` is the name of
the Image style. Change underscores to hyphens in the style name.

Issues
------

Bugs and Feature requests should be reported in the Issue Queue:
https://github.com/backdrop-contrib/insert/issues.

Current Maintainers
-------------------

John Romine (https://github.com/jromine)

Credits
-------

- Ported to Backdrop by Herb v/d Dool (https://github.com/herbdool).
- Originally written for Drupal by Nate Haug (https://github.com/quicksketch).

License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.

