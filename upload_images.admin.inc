<?php
function upload_images_admin_settings() {
	$form = array();
	$form['#redirect'] = '';
	$form['upload_images_path'] = array(
		'#type' => 'textfield',
		'#title' => t('Path to dir'),
		'#description' => t('Path to the directory'),
		'#default_value' => variable_get('upload_images_path',''),
		'#required' => TRUE,
	);
	$form['upload_images_accepts'] = array(
		'#type' => 'textfield',
		'#title' => t('Allowed extensions'),
		'#description' => t('Type a list comma-separated of allowed extensions'),
		'#default_value' => variable_get('upload_images_accepts','jpg'),
		'#required' => TRUE,
	);
	return system_settings_form($form);
}

function upload_images_admin_settings_validate() {
	//validate function for config form!
	// form_set_error('upload_images_path','example text');
}
