<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'icon' => 'icon_node_form.png',
  'title' => t('User form submit buttons'),
  'description' => t('Submit buttons for the user form.'),
  'required context' => new ctools_context_required(t('Form'), 'user_edit_form'),
  'category' => t('Form'),
);

function user_panels_user_form_buttons_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = t('user_form');

  $block->title = '';
  $block->delta = 'buttons';

  if (isset($context->form)) {
    $block->content = array();
    foreach (array('actions', 'form_token', 'form_build_id', 'form_id') as $element) {
      $block->content[$element] = isset($context->form[$element]) ? $context->form[$element] : NULL;
      unset($context->form[$element]);
    }
  }
  else {
    $block->content = t('User form buttons.');
  }
  return $block;
}

function user_panels_user_form_buttons_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" user form submit buttons', array('@s' => $context->identifier));
}

function user_panels_user_form_buttons_content_type_edit_form($form, &$form_state) {
  // provide a blank form so we have a place to have context setting.
  return $form;
}
