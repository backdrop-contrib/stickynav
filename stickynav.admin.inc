<?php
/**
 * @file
 * Contains implementation of admin settings form for Sticky Nav.
 */

/**
 * Admin form to set up the Sticky Nav logic.
 */
function stickynav_admin_form() {
  $form = array();
  $config = config('stickynav.settings');
  $themes = list_themes();
  $form['theme-settings'] = array(
    '#type' => 'details',
    '#summary' => t('Activate sticky navigation for the following themes'),
    '#open' => TRUE,
  );
  foreach ($themes as $name => $data) {
    // Only getting settings for enabled themes.
    if ($data->status == 1) {
      $form['theme-settings']['stickynav-enabled-' . $name] = array(
        '#type' => 'checkbox',
        '#title' => check_plain($data->info['name']),
        '#default_value' => $config->get('stickynav-enabled-' . $name),
      );
      $form['theme-settings']['theme-settings-' . $name] = array(
        '#type' => 'details',
        '#summary' => t('Theme settings: ' . $data->info['name']),
        '#open' => TRUE,
        '#states' => array(
          'visible' => array(
            ':input[name="stickynav-enabled-' . $name . '"]' => array('checked' => TRUE),
          ),
          'invisible' => array(
            ':input[name="stickynav-enabled-' . $name . '"]' => array('checked' => FALSE),
          ),
        ),
      );
      // Selector is only visible when you activate sticky nav for the theme.
      $form['theme-settings']['theme-settings-' . $name]['stickynav-selector-' . $name] = array(
        '#type' => 'textfield',
        '#title' => t('Selector'),
        '#description' => t('Enter the selector to make sticky for this theme. Use jQuery format (e.g. <strong>.l-header</strong>).'),
        '#default_value' => $config->get('stickynav-selector-' . $name),
        '#states' => array(
          'required' => array(
            ':input[name="stickynav-enabled-' . $name . '"]' => array('checked' => TRUE),
          ),
        ),
      );
      $exclude_role_default = (empty($config->get('stickynav-roles-' . $name))) ? array() : $config->get('stickynav-roles-' . $name);
      $form['theme-settings']['theme-settings-' . $name]['stickynav-roles-' . $name] = array(
        '#type' => 'checkboxes',
        '#title' => t('Excluded Roles'),
        '#description' => t("Exclude specific roles from using sticky navigation for this theme."),
        '#options' => user_roles(),
        '#default_value' => $exclude_role_default,
      );
      // Offset settings.
      $offset_selector = $config->get('stickynav-offset-selector-' . $name);
      $custom_offset = $config->get('stickynav-custom-offset-' . $name);
      $form['theme-settings']['theme-settings-' . $name]['stickynav-offsets-' . $name] = array(
        '#type' => 'details',
        '#summary' => t('Offsets'),
        '#description' => t("Set custom offsets to prevent the sticky element to overlap with other elements on the page."),
        '#open' => (!empty($offset_selector) && !empty($custom_offset)),
        '#weight' => 21,
      );
      $form['theme-settings']['theme-settings-' . $name]['stickynav-offsets-' . $name]['stickynav-offset-selector-' . $name] = array(
        '#type' => 'textfield',
        '#title' => t('Selector'),
        '#description' => t('Element to use as an offset. For multiple elements on the page separate them with a comma. Use jQuery format (e.g. <strong>#admin-bar</strong>).'),
        '#default_value' => $offset_selector,
      );
      $form['theme-settings']['theme-settings-' . $name]['stickynav-offsets-' . $name]['stickynav-custom-offset-' . $name] = array(
        '#type' => 'number',
        '#title' => t('Custom offset'),
        '#description' => t('Custom offset (in pixels). This will be added to the elements offsets if they are set.'),
        '#default_value' => $custom_offset,
        '#min' => 0,
        '#step' => 1,
      );
    }
    // Path include/exclude fields.
    $form['paths'] = array(
      '#type' => 'details',
      '#summary' => t('Global settings: Path visibility'),
      '#open' => FALSE,
      '#weight' => 20,
    );
    $form['paths']['pathvisibility'] = array(
      '#type' => 'radios',
      '#title' => t('Activate on specific paths'),
      '#options' => array(
        0 => t('All paths except those listed'),
        1 => t('Only the listed paths'),
      ),
      '#default_value' => $config->get('pathvisibility'),
    );
    $form['paths']['paths'] = array(
      '#type' => 'textarea',
      '#title' => t('List of paths to activate'),
      '#description' => t("Specify paths, one path per line. The '*' character is a wildcard. %front is the front page.", array('%front' => '<front>')),
      '#default_value' => $config->get('paths'),
    );
  }

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;
}

/**
 * Validation callback for stickynav_admin_form().
 */
function stickynav_admin_form_validate($form, &$form_state) {
  $themes = list_themes();
  foreach ($themes as $name => $data) {
    if ($data->status == 1 && $form_state['values']['stickynav-enabled-' . $name] && empty($form_state['values']['stickynav-selector-' . $name])) {
      form_set_error($name, t('You must enter a selector to activate Sticky Nav.'));
    }
  }
}

/**
 * Submit handler for stickynav_admin_form().
 */
function stickynav_admin_form_submit($form, &$form_state) {
  $config = config('stickynav.settings');
  $values = $form_state['values'];
  $themes = list_themes();
  foreach ($themes as $name => $data) {
    if ($data->status == 1) {
      $config->set('stickynav-enabled-' . $name, $values['stickynav-enabled-' . $name]);
      $config->set('stickynav-selector-' . $name, $values['stickynav-selector-' . $name]);
      $config->set('stickynav-roles-' . $name, $values['stickynav-roles-' . $name]);
      $config->set('stickynav-offset-selector-' . $name, $values['stickynav-offset-selector-' . $name]);
      $config->set('paths', $values['paths']);
      $config->set('pathvisibility', $values['pathvisibility']);
      $config->set('stickynav-custom-offset-' . $name, $values['stickynav-custom-offset-' . $name]);
      $config->save();
    }
  }
  backdrop_set_message(t('Sticky Navigation settings have been saved.'));
}
