<?php

/**
 * @file
 *
 * Plugin to provide a user_add_form context
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('User add form'),
  'description' => t('A user add form.'),
  'context' => 'ctools_context_create_user_add_form',
  'edit form' => 'ctools_context_user_add_form_settings_form',
  'defaults' => array('type' => 'user'),
  'keyword' => 'user_add_form',
  'context name' => 'user_add_form',
  'convert list' => array('type' => t('User type')),
  'convert' => 'ctools_context_user_add_form_convert',
  'placeholder form' => array(
    '#type' => 'textfield',
    '#description' => t('Enter the user type this context.'),
  ),
);

/**
 * It's important to remember that $conf is optional here, because contexts
 * are not always created from the UI.
 */
function ctools_context_create_user_add_form($empty, $data = NULL, $conf = FALSE) {
  static $creating = FALSE;
  $context = new ctools_context(array('form', 'user_add', 'user_add_form', 'user_form', 'entity:user'));
  $context->plugin = 'user_add_form';

  if ($empty || ($creating)) {
    return $context;
  }
  $creating = TRUE;

  if ($conf && (isset($data['types']) || isset($data['type']))) {
    // Holdover from typo'd config.
    $data = isset($data['types']) ? $data['types'] : $data['type'];
  }

  if (!empty($data)) {
    $types = array();
    $entity_info = entity_get_info('user');
    foreach($entity_info['bundles'] as $bundle_system_name => $bundle) {
      $types[] = $bundle_system_name;
    }

    $type = str_replace('-', '_', $data);

    $form_id = 'user_register_form';
    $form_state = array(
      'want form' => TRUE,
      'build_info' => array(
        'args' => array()
      )
    );

    $form = drupal_build_form($form_id, $form_state);
    $context->data     = $form['#user'];
    $context->title    = "User add";
    $context->argument = $type;

    // These are specific pieces of data to this form.
    // All forms should place the form here.
    $context->form       = $form;
    $context->form_id    = $form_id;
    $context->form_title = t('Submit user');
    $context->user_type  = $type;
    $context->restrictions['type'] = array($type);
    $context->restrictions['form'] = array('form');

    $creating = FALSE;
    return $context;
  }
  $creating = FALSE;
}

function ctools_context_user_add_form_settings_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $types = array();
  $entity_info = entity_get_info('user');
  foreach($entity_info['bundles'] as $bundle_system_name => $bundle) {
    $types[$bundle_system_name] = $bundle['label'];
  }

  $form['type'] = array(
    '#title' => t('User type'),
    '#type' => 'select',
    '#options' => $types,
    '#default_value' => $conf['type'],
    '#description' => t('Select the user type for this form.'),
  );

  return $form;
}

function ctools_context_user_add_form_settings_form_submit($form, &$form_state) {
  $form_state['conf']['type'] = $form_state['values']['type'];
}

/**
 * Convert a context into a string.
 */
function ctools_context_user_add_form_convert($context, $type) {
  switch ($type) {
    case 'type':
      return $context->data->type;
  }
}
