<?php
/**
 * @file
 * Contains implementation of admin settings form for the sticky navigation
 */

/**
 * Admin form to set up the sticky nav logic.
 */
function stickynav_admin_form() {
  $form = array();
  $themes = list_themes();
  foreach ($themes as $name => $data) {
    // Only getting settings for enabled themes.
    if ($data->status == 1) {
      $form['stickynav-enabled-' . $name] = array(
        '#type' => 'checkbox',
        '#title' => check_plain($data->info['name']),
        '#default_value' => variable_get('stickynav-enabled-' . $name, FALSE),
      );
      // Selector is only visible when you activate sticky nav for the theme.
      $form['stickynav-selector-' . $name] = array(
        '#type' => 'textfield',
        '#title' => t('Selector'),
        '#description' => t('Place your selector for your menu that will be sticky on your theme. Use jquery format.'),
        '#default_value' => variable_get('stickynav-selector-' . $name, ''),
        '#states' => array(
          'visible' => array(
            ':input[name="stickynav-enabled-' . $name . '"]' => array('checked' => TRUE),
          ),
          'invisible' => array(
            ':input[name="stickynav-enabled-' . $name . '"]' => array('checked' => FALSE),
          ),
        ),
      );
      $form['stickynav-roles-' . $name] = array(
        '#type' => 'checkboxes',
        '#title' => t('Excluded Roles'),
        '#description' => t("Exclude specific roles from using sticky navigation."),
        '#options' => user_roles(),
        '#default_value' => variable_get('stickynav-roles-' . $name, array()),
        '#states' => array(
          'visible' => array(
            ':input[name="stickynav-enabled-' . $name . '"]' => array('checked' => TRUE),
          ),
          'invisible' => array(
            ':input[name="stickynav-enabled-' . $name . '"]' => array('checked' => FALSE),
          ),
        ),
      );
      // Offset settings.
      $offset_selector = variable_get('stickynav-offset-selector-' . $name, '');
      $custom_offset = variable_get('stickynav-custom-offset-' . $name, '');
      $form['stickynav-offsets-' . $name] = array(
        '#type' => 'fieldset',
        '#title' => t('Offsets'),
        '#description' => t("Set custom offsets to prevent the sticky element to overlap with other elements on the page."),
        '#collapsible' => TRUE,
        '#collapsed' => empty($offset_selector) && empty($custom_offset),
        '#states' => array(
          'visible' => array(
            ':input[name="stickynav-enabled-' . $name . '"]' => array('checked' => TRUE),
          ),
          'invisible' => array(
            ':input[name="stickynav-enabled-' . $name . '"]' => array('checked' => FALSE),
          ),
        ),
      );
      $form['stickynav-offsets-' . $name]['stickynav-offset-selector-' . $name] = array(
        '#type' => 'textfield',
        '#title' => t('Selector'),
        '#description' => t('Element to use as an offset. For multiple elements on the page separate them with a comma. Use jquery format.'),
        '#default_value' => $offset_selector,
      );
      $form['stickynav-offsets-' . $name]['stickynav-custom-offset-' . $name] = array(
        '#type' => 'textfield',
        '#title' => t('Custom offset'),
        '#description' => t('Custom offset in pixels. This will be added to the elements offsets if they are set.'),
        '#default_value' => $custom_offset,
      );
    }
  }

  return system_settings_form($form);
}

/**
 * Validation callback for stickynav_admin_form().
 */
function stickynav_admin_form_validate($form, &$form_state) {
  $themes = list_themes();
  foreach ($themes as $name => $data) {
    $name = 'stickynav-custom-offset-' . $name;
    if ($data->status == 1 && !empty($form_state['values'][$name]) && !is_numeric($form_state['values'][$name])) {
      form_set_error($name, t('The custom offset value has to be a number.'));
    }
  }
}