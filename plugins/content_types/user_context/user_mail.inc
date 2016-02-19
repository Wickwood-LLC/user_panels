<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('User mail'),
  'icon' => 'icon_user.png',
  'description' => t('The mail of a user.'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
  'defaults' => array('label' => 'title'),
);

/**
 * Render the user profile content type.
 */
function user_panels_user_mail_content_type_render($subtype, $conf, $panel_args, $context) {
  $account = isset($context->data) ? clone($context->data) : NULL;
  if (!$account) {
    return NULL;
  }

  if (empty($conf['label']) || $conf['label'] == 'title') {
    $label = 'hidden';
    $conf['label'] = 'title';
  }
  else {
    $label = $conf['label'];
  }

  // Take overriden title if any or set to Mail.
  $title = !empty($conf['override_title']) ? filter_xss_admin($conf['override_title_text']) : t('Mail');

  // Prepare field label.
  $label_markup = in_array($label, array('above', 'inline'))
    ? '<div class="field-label">' . t('@label:&nbsp;', array('@label' => $title)) . '</div>'
    : '';

  // Determine the field calsses to be used.
  $attributes = array(
    'class' => array('field'),
  );
  $attributes['class'][] = in_array($label, array('above', 'inline')) ? 'field-label-' . $label : '';
  if ($label == 'inline') {
    $attributes['class'][] = 'clearfix';
  }

  $build = array(
    '#markup' => "<div " . drupal_attributes($attributes) . ">$label_markup"
    . "<div class='field-items'><div class='field-item'>"
    . l($account->mail, 'mailto:' . $account->mail)
    . '</div></div></div>',
  );

  $block = new stdClass();
  $block->module = 'user-mail';
  if ($conf['label'] == 'title') {
    $block->title = $title;
  }
  $block->content = $build;

  return $block;
}

/**
 * Display the administrative title for a panel pane in the drag & drop UI.
 */
function user_panels_user_mail_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" user mail', array('@s' => $context->identifier));
}

function user_panels_user_mail_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $field_label_options = array(
    'title' => t('Pane title'),
    'above' => t('Above'),
    'inline' => t('Inline'),
    'hidden' => t('Hidden'),
  );
  $form['label'] = array(
    '#type' => 'select',
    '#title' => t('Label'),
    '#options' => $field_label_options,
    '#default_value' => $conf['label'],
  );
  return $form;
}

function user_panels_user_mail_content_type_edit_form_submit($form, &$form_state) {
  $form_state['conf']['label'] = $form_state['values']['label'];
}

