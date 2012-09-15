<?php
function upload_images_page(){
	$path = variable_get('upload_images_path','');
	if (!is_dir($path)) {
		$output = array(
			'#type' => 'markup',
			'#markup' => '<p>Invalid path of dir!</p>',
		);
		return $output;
	}
	$accept = array('jpg','bmp','jpeg');
	$files = get_files($path,$accept);
	variable_set('files',$files);
	$output = array(
		'list_images' => array(
			'#items' => array_flip($files),
			'#title' => 'Images from folders',
			'#theme' => 'item_list'
		),
		'submit_form' => drupal_get_form('submit_create_node_form'),
	);
	return $output;
}

function submit_create_node_form(){
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Submit',
	);
	return $form;
}

function submit_create_node_form_submit(){
	$var = variable_get('files','0');
	// $var = 1;
	if ($var) {
		drupal_set_message('variable images is NOT empty!','warning');
	} else {
		drupal_set_message('variable images is  empty!','warning');
	}
}

function accepted($name, $accept){
	if (empty($accept)) { return TRUE;}
	foreach ($accept as $ext) {
		$reg = '\.' . $ext . '$';
		if (eregi($reg,$name)) {
			return TRUE;
		}
	}
	return FALSE;
}

function get_files($path, $accept=array()){
	$dir = opendir($path);
	$files = array();
	while ($entry = readdir($dir)) {
		if (substr($entry, 0, 1) != ".") {
			$next_path = $path . "/";
			$next_path .= $entry;
			if (is_dir($next_path)) {
				$files_next = get_files($next_path,$accept);
				asort($files_next);
				$files = array_merge($files, $files_next);
			} elseif (accepted($entry, $accept)) {
				$files[$entry] = $next_path;
			}
		}
	}
	closedir($dir);
	return $files;
}

