<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('User roles'),
  'icon' => 'icon_user.png',
  'description' => t('The roles of a user.'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);

/**
 * Render the user profile content type.
 */
function user_panels_user_roles_content_type_render($subtype, $conf, $panel_args, $context) {
  $account = isset($context->data) ? clone($context->data) : NULL;
  if (!$account) {
    return NULL;
  }

//  $roles = user_roles(TRUE);
  
  $build = array(
    '#theme' => 'item_list',
    '#items' => $account->roles,
    '#type' => 'ul',
  );

  $block = new stdClass();
  $block->module = 'user-roles';
  $block->title = t('Roles');
  $block->content = $build;

  return $block;
}

/**
 * Display the administrative title for a panel pane in the drag & drop UI.
 */
function user_panels_user_roles_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" user roles', array('@s' => $context->identifier));
}

function user_panels_user_roles_content_type_edit_form($form, &$form_state) {
  return $form;
}

function user_panels_user_roles_content_type_edit_form_submit($form, &$form_state) {

}

