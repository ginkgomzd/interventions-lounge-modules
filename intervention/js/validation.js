(function ($) {
  Drupal.behaviors.intervention = {
    attach: function (context, settings) {
      /**
       * For multiselect fields which offer an "all" option, remove any other
       * selections if the "all" option is selected. The fields are explicity
       * named by ID in the selector below; there is no
       * magic selection of fields.
       *
       * This script assumes that the value for the "all" option is zero.
       */
      $('#edit-field-target-population-und, #edit-field-target-race-und', context).change(function () {
        if ($.inArray('0', $(this).val()) != -1) {
          $(this).val(['0']);
        }
      });
    }
  };
})(jQuery);