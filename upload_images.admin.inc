<?php
function upload_images_admin_settings() {
	$form = array();
	$form['#redirect'] = '';
	$form['upload_images_path'] = array(
		'#type' => 'textfield',
		'#title' => t('Path to source directory'),
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
	$form['upload_images_destination'] = array(
		'#type' => 'textfield',
		'#title' => t('Path to destination'),
		'#description' => t('Path to the directory where the files will be stored. It needs to exists, be writable by Drupal, the path relative to the Drupal Installation directory, and be accesable over the web.'),
		'#default_value' => variable_get('upload_images_destination',''),
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
	$dest = $form_state['values']['upload_images_destination'];
	if (substr($dest, -1, 1) == "/") {
		form_set_error('upload_images_destination', t('The path dosen\'t need to end with a "/" (slash)!'));
	}
	if (!is_dir($dest)) {
		form_set_error('upload_images_destination',t('Not a valid path to a directory!'));
	}
}

function upload_images_admin_settings_submit() {

}
