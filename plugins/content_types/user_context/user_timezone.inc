<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('User timezone'),
  'icon' => 'icon_user.png',
  'description' => t('The timezone of a user.'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);

/**
 * Render the user profile content type.
 */
function user_panels_user_timezone_content_type_render($subtype, $conf, $panel_args, $context) {
  $account = isset($context->data) ? clone($context->data) : NULL;
  if (!$account) {
    return NULL;
  }

  // Logic copeid from drupal_get_user_timezone().
  if (variable_get('configurable_timezones', 1) && $account->uid && $account->timezone) {
    $timezone = $account->timezone;
  }
  else {
    // Ignore PHP strict notice if time zone has not yet been set in the php.ini
    // configuration.
    $timezone = variable_get('date_default_timezone', @date_default_timezone_get());
  }

  $build = array(
    '#markup' => $timezone,
  );

  $block = new stdClass();
  $block->module = 'user-timezone';
  $block->title = t('Timezone');
  $block->content = $build;

  return $block;
}

/**
 * Display the administrative title for a panel pane in the drag & drop UI.
 */
function user_panels_user_timezone_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" user timezone', array('@s' => $context->identifier));
}

function user_panels_user_timezone_content_type_edit_form($form, &$form_state) {
  return $form;
}

function user_panels_user_timezone_content_type_edit_form_submit($form, &$form_state) {

}

