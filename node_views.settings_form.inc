<?php

function node_views_config(){
  return drupal_get_form('node_views_configuration_form');
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
    $default = node_view_get_default($type->type);
    $form['content'][$type->type] = array(
      '#type'=>'checkbox',
      '#title'=>t($type->name),
      '#default_value'=>$default['count_view'],
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
      $save = array('type'=>$key, 'value'=>$value);
      node_view_save($save, $value);
    }
    if ($value == 0) {
      $save = array('type'=>$key, 'value'=>$value);
      node_view_save($save, $value);
    }
  }
  drupal_set_message(t('Settings saved.'));
}

function node_view_save($save, $value){
  if ($value == 1) {
    db_merge('node_views_options')
    ->key(array('content_type' => $save['type']))
    ->fields(array(
      'content_type' => $save['type'],
      'count_view' => $save['value']
    ))
    ->execute();
  }
  if ($value == 0) {
    db_merge('node_views_options')
    ->key(array('content_type' => $save['type']))
    ->fields(array(
      'content_type' => $save['type'],
      'count_view' => $save['value']
    ))
    ->execute();
  }
  return true;
}

function node_view_get_default($type){
  $result = db_select('node_views_options', 'n')
  ->fields('n', array('content_type', 'count_view'))
  ->condition('content_type', $type)
  ->execute()
  ->fetchAssoc();
  return $result;
}
