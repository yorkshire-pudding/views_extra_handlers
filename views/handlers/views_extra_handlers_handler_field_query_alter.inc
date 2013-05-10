<?php

/**
 * @file
 * Views field handler for the views_system module.
 */

class views_extra_handlers_handler_field_query_alter extends views_handler_field {

 function query() {
  if(!empty($this->options['veh_join']['veh_table'])){
   $def = $this->definition;
   $def['table'] = $this->options['veh_join']['veh_table'];
   $def['field'] = $this->options['veh_join']['veh_column'];
   //$def['left_table'] = "node_og_membership";
   //$def['left_field'] = "nid";
   $def['type'] = $this->options['veh_join']['veh_join_type'];
   $def['left_query'] = $this->options['veh_join']['veh_join_condition'];
 
   if (!empty($def['join_handler']) && class_exists($def['join_handler'])) {
    $join = new $def['join_handler'];
   }
   else {
    $join = new views_join_subquery();
   }
 
   $join->definition = $def;
   $join->construct();
   $join->adjusted = TRUE;
 
   // use a short alias for this:
   $alias = $this->options['veh_join']['veh_table_alias'];
 
 
   $this->alias = $this->query->add_relationship($alias, $join, $this->definition['base']);
  }
  if(!empty($this->options['veh_field']['veh_table'])){  
    $this->field_alias = $this->query->add_field($this->options['veh_field']['veh_table'], $this->options['veh_field']['veh_column'], '');
  }
 }

 function option_definition() {
  $options = parent::option_definition();
  $options['veh_field']['veh_table'] = array('default' => '', 'translatable' => FALSE);
  $options['veh_field']['veh_column'] = array('default' => '', 'translatable' => FALSE);

  $options['veh_join']['veh_table'] = array('default' => '', 'translatable' => FALSE);
  $options['veh_join']['veh_table_alias'] = array('default' => '', 'translatable' => FALSE);
  $options['veh_join']['veh_column'] = array('default' => '', 'translatable' => FALSE);
  $options['veh_join']['veh_join_type'] = array('default' => '', 'translatable' => FALSE);
  $options['veh_join']['veh_join_condition'] = array('default' => '', 'translatable' => FALSE);
  
  $options['veh_groupby']['veh_add'] = array('default' => '', 'translatable' => FALSE);
  $options['veh_groupby']['veh_remove'] = array('default' => '', 'translatable' => FALSE);  
  return $options;
 }

 function options_form(&$form, &$form_state) {
  parent::options_form($form, $form_state);
  $form['veh_field'] = array(
    '#type' => 'fieldset',
    '#title' => t('Field'),
    '#collapsible' => TRUE,
  );
  $form['veh_field']['veh_table'] = array(
    '#type' => 'textfield',
    '#title' => t('Table'),
    '#default_value' => $this->options['veh_field']['veh_table'],
  );
  $form['veh_field']['veh_column'] = array(
    '#type' => 'textfield',
    '#title' => t('Field'),
    '#default_value' => $this->options['veh_field']['veh_column'],
  );

  $form['veh_join'] = array(
    '#type' => 'fieldset',
    '#title' => t('Join'),
    '#collapsible' => TRUE,
  );
  $form['veh_join']['veh_join_type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#options' => array(
      'INNER' => t('INNER'),
      'LEFT' => t('LEFT'),
      'RIGHT' => t('RIGHT'),
    ),
    '#default_value' => $this->options['veh_join']['veh_join_type'],
    '#description' => t('Type of Join.'),
  );
  $form['veh_join']['veh_table'] = array(
    '#type' => 'textfield',
    '#title' => t('Join Table'),
    '#default_value' => $this->options['veh_join']['veh_table'],
  );
  $form['veh_join']['veh_table_alias'] = array(
    '#type' => 'textfield',
    '#title' => t('Join Table Alias'),
    '#default_value' => $this->options['veh_join']['veh_table_alias'],
  );
  $form['veh_join']['veh_column'] = array(
    '#type' => 'textfield',
    '#title' => t('Join Field'),
    '#default_value' => $this->options['veh_join']['veh_column'],
  );
  $form['veh_join']['veh_join_condition'] = array(
    '#type' => 'textfield',
    '#title' => t('Join Condition'),
    '#default_value' => $this->options['veh_join']['veh_join_condition'],
  );
  $form['veh_groupby'] = array(
    '#type' => 'fieldset',
    '#title' => t('Groupby'),
    '#collapsible' => TRUE,
  );
  $form['veh_groupby']['veh_add'] = array(
    '#type' => 'textarea',
    '#title' => t('Add'),
    '#default_value' => $this->options['veh_groupby']['veh_add'],
    '#rows' => 2,
    '#description' => t('Seperate multiple entries by ,'),    
  );
  $form['veh_groupby']['veh_remove'] = array(
    '#type' => 'textarea',
    '#title' => t('Remove'),
    '#default_value' => $this->options['veh_groupby']['veh_remove'],
    '#rows' => 2,
    '#description' => t('Seperate multiple entries by ,'),
  );
 }
 /*
  function options_submit(&$form, &$form_state) {
 $form_state['values']['options']['format'] = $form_state['values']['options']['content']['format'];
 $form_state['values']['options']['content'] = $form_state['values']['options']['content']['value'];
 parent::options_submit($form, $form_state);
 }
 */
 function render($values) {
  $data = '';
  if(isset($this->field_alias) && !empty($this->field_alias) && $this->field_alias != "unknown"){
    $data = $values->{$this->field_alias};
  }
  return $data;
 }
}