# Sticky Navigation

You can use this module to make an element (such as the navigation menu or
the header region) become sticky at the top of the page when a long page
is scrolled.

## How to Install and Configure

1. Copy this module's directory into the **/modules** folder in your 
   Backdrop installation.
2. Enable the module in the **Functionality** page (`admin/modules/list`) or
   via the Project Installer. [See the official Backdrop CMS instructions
   for more detail on the install process](https://backdropcms.org/guide/modules).
3. Go to **Configuration > User Interface > Sticky Nav Settings** 
   (`admin/config/user-interface/stickynav`) to configure.
4. Activate the module for the themes you want Sticky Navigation to 
   function on.
5. Place a jQuery format selector (e.g. `ul.menu` or `.l-header`) into the 
   Selector field for each activated theme.

Note that this functionality may not look good on every theme out of the box. 
You might have to adjust the styling (such as the background color of the 
element you've selected to make sticky).

## Current Maintainers

- Laryn Kragt Bakker - CEDC.org (https://github.com/laryn)
- Mihhail Arhipov - DMT team (https://github.com/skein)

## Credits

- Ported to Backdrop CMS by Laryn Kragt Bakker - CEDC.org (https://github.com/laryn).
- Originally written for Drupal by Mihhail Arhipov - DMT team (https://github.com/skein) for Haymarket Media Group.

## License

This project is GPL v2 software. See the [LICENSE.txt](LICENSE.txt) file in this directory for
complete text.
