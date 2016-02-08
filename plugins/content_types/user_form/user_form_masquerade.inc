<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'icon' => 'icon_node_form.png',
  'title' => t('User form masquerade'),
  'description' => t('Masquerade of use edit form.'),
  'required context' => new ctools_context_required(t('Form'), 'user_edit_form'),
  'category' => t('Form'),
);

function user_panels_user_form_masquerade_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = t('user_form');

  $block->title = '';
  $block->delta = 'masquerade';

  if (isset($context->form)) {
    $block->content = array();
    $block->content['masquerade'] = isset($context->form['masquerade']) ? $context->form['masquerade'] : NULL;
    unset($context->form['masquerade']);
  }
  else {
    $block->content = t('User form masquerade.');
  }
  return $block;
}

function user_panels_user_form_masquerade_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" user form masquerade', array('@s' => $context->identifier));
}

function user_panels_user_form_masquerade_content_type_edit_form($form, &$form_state) {
  // provide a blank form so we have a place to have context setting.
  return $form;
}
