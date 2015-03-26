<?php

function node_views_config(){
  return drupal_get_form('node_views_configuration_form');
  dsm($form);
}

function node_views_configuration_form($node, &$form_state){

  $form = array();

  $form['markup'] = array(
    '#type'=>'markup',
    '#markup'=>t('<p>Select a content type for which you want to count the views.</p>'),
    );

  $types = node_type_get_types();
  $total_types = count($types);

  foreach ($types as $type) {
    $form['content'][$type->type] = array(
      '#type'=>'checkbox',
      '#title'=>t($type->name),
      '#default_value'=>0,
      '#access'=>TRUE,
      );
  }

  $form['config_submit'] = array(
    '#type'=>'submit',
    '#value'=>'Save configuration',
    );

  return $form;
}

function node_views_configuration_form_submit(&$form, &$form_state){
  $types = node_type_get_types();
  $total_types = count($types);
  $sliced_array = array_slice($form_state['values'], 0, $total_types);
  foreach ($sliced_array as $key => $value) {
    if ($value == 1) {
      dsm($key);
    }
    else{
      drupal_set_message(t('No option selected.'), 'error');
    }
  }
}
