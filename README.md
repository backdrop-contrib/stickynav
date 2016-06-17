# Sticky Navigation

You can use this module to make an element (such as the navigation menu or
the header region) become sticky at the top of the page when a long page
is scrolled.

## How to Install and Configure

1. Copy this module's directory into the **/modules** folder in your 
   Backdrop installation.
2. Enable the module in the **Functionality** page (`admin/modules/list`).
3. Go to **Configuration > User Interface > Sticky Nav Settings** 
   (`admin/config/user-interface/stickynav`) to configure.
4. Activate the module for the themes you want Sticky Navigation to 
   function on.
5. Place a jQuery format selector (e.g. `ul.menu` or `.l-header`) into the 
   Selector field for each activated theme.

Note that this functionality may not look good on every theme out of the box. 
You might have to adjust the styling (such as the background color of the 
element you've selected to make sticky).


> Sticky Navigation was originally created for Haymarket Media Group by DMT team

> Developer: Mihhail Arhipov (drupal.org id: skein)

> Backdrop port: Laryn Kragt Bakker for CEDC.org (github id: laryn)
