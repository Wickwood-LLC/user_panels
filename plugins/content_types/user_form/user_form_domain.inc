<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'icon' => 'icon_node_form.png',
  'title' => t('User form domain access'),
  'description' => t('Domain access settings on user edit form.'),
  'required context' => new ctools_context_required(t('Form'), 'user_edit_form'),
  'category' => t('Form'),
);

function user_panels_user_form_domain_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = t('user_form');

  $block->title = '';
  $block->delta = 'domain';

  if (isset($context->form)) {
    $block->content = array();
    $block->content['domain'] = isset($context->form['domain']) ? $context->form['domain'] : NULL;
    unset($context->form['domain']);
  }
  else {
    $block->content = t('User form domain access.');
  }
  return $block;
}

function user_panels_user_form_domain_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" user form domain access', array('@s' => $context->identifier));
}

function user_panels_user_form_domain_content_type_edit_form($form, &$form_state) {
  // provide a blank form so we have a place to have context setting.
  return $form;
}
