<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('User status'),
  'icon' => 'icon_user.png',
  'description' => t('The status of a user.'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);

/**
 * Render the user profile content type.
 */
function user_panels_user_status_content_type_render($subtype, $conf, $panel_args, $context) {
  $account = isset($context->data) ? clone($context->data) : NULL;
  if (!$account) {
    return NULL;
  }

  $statuses = array(t('Blocked'), t('Active'));
  $build = array(
    '#markup' => $statuses[$account->status],
  );

  $block = new stdClass();
  $block->module = 'user-status';
  $block->title = t('Status');
  $block->content = $build;

  return $block;
}

/**
 * Display the administrative title for a panel pane in the drag & drop UI.
 */
function user_panels_user_status_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" user status', array('@s' => $context->identifier));
}

function user_panels_user_status_content_type_edit_form($form, &$form_state) {
  return $form;
}

function user_panels_user_status_content_type_edit_form_submit($form, &$form_state) {

}

