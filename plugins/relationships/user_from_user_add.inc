<?php

/**
 * @file
 * Plugin to provide an relationship handler for node from user.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('User of user add form'),
  'keyword' => 'user',
  'description' => t('Creates the user of user add form as a user context.'),
  'required context' => new ctools_context_required(t('User add form'), 'user_add_form'),
  'context' => 'user_panels_user_from_user_add_context',
  'no ui' => FALSE,
);

/**
 * Return a new context based on an existing context.
 */
function user_panels_user_from_user_add_context($context, $conf) {
  // If unset it wants a generic, unfilled context, which is just NULL.
  if (empty($context->data) || !isset($context->data->uid)) {
    return ctools_context_create_empty('entity:user', NULL);
  }

  if (isset($context->data->uid)) {
    // Take anonymous user object.
    $account = $context->data;
    // $account = user_load($uid);

    // Send it to ctools.
    return ctools_context_create('entity:user', $account);
  }
}
