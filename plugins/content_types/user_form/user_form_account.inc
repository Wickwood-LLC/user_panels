<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'icon' => 'icon_node_form.png',
  'title' => t('User form account fields'),
  'description' => t('Base user account fields like username, mail, password, etc.'),
  'required context' => new ctools_context_required(t('Form'), 'user_edit_form'),
  'category' => t('Form'),
);

function user_panels_user_form_account_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = t('user_form');

  $block->title = '';
  $block->delta = 'account';

  if (isset($context->form)) {
    $block->content = array();
    $block->content['account'] = isset($context->form['account']) ? $context->form['account'] : NULL;
    unset($context->form['account']);
  }
  else {
    $block->content = t('User form account.');
  }
  return $block;
}

function user_panels_user_form_account_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" user form account', array('@s' => $context->identifier));
}

function user_panels_user_form_account_content_type_edit_form($form, &$form_state) {
  // provide a blank form so we have a place to have context setting.
  return $form;
}
