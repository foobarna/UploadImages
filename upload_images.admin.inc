<?php
function upload_images_admin_settings() {
	$form['upload_images_path'] = array(
		'#type' => 'textfield',
		'#title' => t('Path to dir'),
		'#description' => t('Path to the directory'),
		//'#value' => t('lorem ipsum'),
		'#default_value' => variable_get('upload_images_path',''),
		'#required' => TRUE,
	);
	$form['upload_images_go'] = array(
		'#title' => t('Create nodes?'),
		'#type' => 'checkbox',
	);
	$form["submit"] = array(
		"#type" => "submit",
		"#value" => "Next",
	);
	return system_settings_form($form);
}

function upload_images_admin_settings_validate() {
	//validate function for config form!
	// form_set_error('upload_images_path','example text');
}
