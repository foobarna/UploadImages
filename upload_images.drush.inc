<?php
require_once('upload_images.create.inc');
function upload_images_drush_help($command) {
	switch ($command) {
		case 'cmd-ui':
			return dt('a simple help. NOT');
	}
}

function upload_images_drush_command() {
	$items = array();
	$items['cmd-ui'] = array(
		'description' => dt('Creates nodes based on images found in the path folder'),
		'arguments' => array(
			'path' => dt('The path to folder.'),
		),
		'examples' => array(
			'Standard example' => 'drush upload-images-cmd ',
			'Argument example' => 'drush upload-images-cmd 6',
		),
		'aliases' => array('uicmd'),
	);
	return $items;
}

function drush_upload_images_cmd_ui($path = NULL) {
	if (!isset($path)) {
		drush_print('You need to set a path!');
	} else {
		if (substr($path, -1, 1) == "/") {
			drush_log('The path dosen\'t need to end with a "/" (slash)! Creating aborded!', 'warning');
			return;
		}
		$files = _get_files($path,array('jpg', 'png', 'bmp'));
		drush_print('creating content....');
		_create_content($files);
		drush_print('content created...');
	}
	drush_log('The command was a succes!', 'ok');
}
