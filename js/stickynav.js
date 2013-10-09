(function($) {
  Drupal.behaviors.stickynav = {
    attach : function(context) {
      var selector = Drupal.settings.stickynav.selector;
      //only getting the first elmenet in the dom
      var menu = $(selector).eq(0);
      if (menu.length) {
        var breakpoint = menu.offset().top;
        //we need to compensate the element so that the content does not jump up
        var compensation = menu.outerHeight();
        //attaching a scroll event
        $(window).scroll(function () {
          console.log(1);
          if ($(window).scrollTop() > breakpoint) {
            menu.addClass('stickynav-active');
            $('body').css('padding-top', compensation);
          } else {
            menu.removeClass('stickynav-active');
            $('body').css('padding-top', 'inherit');
          }
        });
      }
    }
  }
})(jQuery);
