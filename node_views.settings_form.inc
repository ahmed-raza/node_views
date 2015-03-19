<?php

function node_views_config(){
  dsm(node_type_get_types());
  return drupal_get_form('node_views_configuration_form');
}

function node_views_configuration_form($node, &$form_state){
  $types = node_type_get_types();
  foreach ($types as $type) {
    $options[$type->type] = array(
      'type' => t($type->name),
    );
    dsm($options);
  }
  $form = array();
  $values = array(
    'article'=>t('Article'),
    'page'=>t('Basic Page'),
    );
  $form['content_type'] = array(
    '#type'=>'checkboxes',
    '#title'=>t('Select the content types'),
    '#default_value'=>0,
    '#options'=>drupal_map_assoc($values),
    '#description'=>t('Select the content types for which you want the views to store.'),
    '#access'=>TRUE,
    );
  $form['config_submit'] = array(
    '#type'=>'submit',
    '#value'=>'Save configuration',
    );
  return $form;
}

function node_views_configuration_form_validate(&$form, &$form_state){
  dsm($form_state);
}
