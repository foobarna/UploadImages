<?php
function upload_images_drush_help($command) {
	switch ($command) {
		case 'upload-images-cmd':
			return dt('a simple help. NOT');
	}
}

function upload_images_drush_command() {
	$items = array();
	$items['upload-images-cmd'] = array(
		'description' => dt('run this'),
		'arguments' => array(
			'arg1' => dt('An optional argument'),
		),
		'examples' => array(
			'Standard example' => 'drush upload-images-cmd',
			'Argument example' => 'drush upload-images-cmd 6',
		),
		'aliases' => array('uicmd'),
	);
	return $items;
}

function drush_upload_images_upload_images_cmd($arg1 = NULL) {
	if (isset($arg1)) {
		drush_print($arg1);
	} else {
		drush_print('Nice of you that you havent pass args\n!');
	}
	drush_log('Running the cmd', 'ok');
}
