(function($) {
  Drupal.behaviors.stickynav = {
    breakpoint: 0,
    compensation: 0,
    originalPadding: 0,
    attach : function(context) {
      var selector = Drupal.settings.stickynav.selector;
      //only getting the first elmenet in the dom
      var $menu = $(selector).eq(0);
      var offset = 0;
      if ($menu.length) {
        $menu.once('stickynav', function() {
          // Save original padding on top. 0 timeout to get correct padding.
          setTimeout(function() {
            Drupal.behaviors.stickynav.originalPadding = $('body').css('paddingTop');
          }, 0);
          offset += parseInt(Drupal.settings.stickynav.offsets.custom_offset);
          offset = offset || 0;
          $(Drupal.settings.stickynav.offsets.selector).each(function() {
            offset += $(this).outerHeight();
          });
          Drupal.behaviors.stickynav.breakpoint = $menu.offset().top - offset;
          //we need to compensate the element so that the content does not jump up.
          Drupal.behaviors.stickynav.compensation = $menu.outerHeight();
          $(window).scroll(function () {
            if ($(window).scrollTop() > Drupal.behaviors.stickynav.breakpoint) {
              $menu.addClass('stickynav-active');
              if (offset) {
                $menu.css({'top': offset + 'px'});
              }
              $('body').css('padding-top', Drupal.behaviors.stickynav.compensation);
            }
            else {
              $menu.removeClass('stickynav-active');
              $menu.css({'top': ''});
              $('body').css('padding-top', Drupal.behaviors.stickynav.originalPadding);
            }
          });
        });
      }
    }
  }
})(jQuery);
