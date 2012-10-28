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

function upload_images_admin_settings_validate($form, $form_state) {
	//validate function for config form!
	$path = $form_state['values']['upload_images_path'];
	if (substr($path, -1, 1) == "/") {
		form_set_error('upload_images_path', t('The path dosen\'t need to end with a "/" (slash)!'));
	}
	if (!is_dir($path)) {
		form_set_error('upload_images_path',t('Not a valid path to a directory!'));
	}
}

function upload_images_admin_settings_submit() {

}
