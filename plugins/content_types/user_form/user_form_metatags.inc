<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'icon' => 'icon_node_form.png',
  'title' => t('User form metatags'),
  'description' => t('Metatag settings fields on user edit form.'),
  'required context' => new ctools_context_required(t('Form'), 'user_edit_form'),
  'category' => t('Form'),
);

function user_panels_user_form_metatags_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = t('user_form');

  $block->title = '';
  $block->delta = 'metatags';

  if (isset($context->form)) {
    $block->content = array();
    $block->content['metatags'] = isset($context->form['metatags']) ? $context->form['metatags'] : NULL;
    unset($context->form['metatags']);
  }
  else {
    $block->content = t('User form metatags.');
  }
  return $block;
}

function user_panels_user_form_metatags_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" user form metatags', array('@s' => $context->identifier));
}

function user_panels_user_form_metatags_content_type_edit_form($form, &$form_state) {
  // provide a blank form so we have a place to have context setting.
  return $form;
}
