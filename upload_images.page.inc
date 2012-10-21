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
	$accept = _get_accepted_ext();
	$files = _get_files($path,$accept);
	variable_set('files',$files);
	if (empty($files)) {
		$output = array(
			'list_images' => array(
				'#type' => 'markup',
				'#markup' => '<p> There were no images found!</p>',
			),
			'submit_form' => drupal_get_form('submit_create_node_form'),
		);
	} else {
		$output = array(
			'list_images' => array(
				'#items' => array_flip($files),
				'#title' => 'Images from folders',
				'#theme' => 'item_list'
			),
			'submit_form' => drupal_get_form('submit_create_node_form'),
		);
	}
	return $output;
}

function submit_create_node_form(){
	$form['#redirect'] = '';
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Create',
	);
	return $form;
}

function submit_create_node_form_submit(){
	$var = variable_get('files','0');
	if ($var) {
		drupal_set_message('variable images is NOT empty!','warning');
	} else {
		drupal_set_message('There are no images!','error');
	}
	global $user;

	print_r($var);
		$key = 'Screenshot from 2012-10-06 00:46:02.png';
	foreach ($var as $key => $value) {
		$node = new stdClass();
		$node->title = $key;
		$node->type = 'upload_images';
		node_object_prepare($node);
		$node->language = LANGUAGE_NONE;
		$node->uid = $user->uid;
		$node->status = 1;
		$node->promote = 1;
		$node->comment = 1;
		$filepath = $value;
  		$file = (object) array(
    		'uid' => 1,
    		'uri' => $filepath,
    		'filemime' => file_get_mimetype($filepath),
		    'status' => 1,
		);
  		$file = file_copy($file, 'public://');
  		$node->upload_images_image[$node->language][0] = (array)$file;
		// $node->upload_images_tag_field[$node->language][]['tid'] = 7;
		$node = node_submit($node); // Prepare node for saving
		node_save($node);
	}
}

function _accepted($name, $accept){
	if (empty($accept)) { return TRUE;}
	foreach ($accept as $ext) {
		$reg = '/\.' . $ext . '$/i';
		if (preg_match($reg,$name)) {
			return TRUE;
		}
	}
	return FALSE;
}

function _get_files($path, $accept=array()){
	$dir = opendir($path);
	$files = array();
	while ($entry = readdir($dir)) {
		if (substr($entry, 0, 1) != ".") {
			$next_path = $path . "/";
			$next_path .= $entry;
			if (is_dir($next_path)) {
				$files_next = _get_files($next_path,$accept);
				asort($files_next);
				$files = array_merge($files, $files_next);
			} elseif (_accepted($entry, $accept)) {
				$files[$entry] = $next_path;
			}
		}
	}
	closedir($dir);
	return $files;
}

function _get_accepted_ext() {
	$s = variable_get('upload_images_accepts','');
	$s = preg_replace('/\s+/','', $s);
	return explode(',',$s);
}

function _create_content($files) {
	foreach ($var as $key => $value) {
		$node = new stdClass();
		$node->title = $key;
		$node->type = 'upload_images';
		node_object_prepare($node);
		$node->language = LANGUAGE_NONE;
		$node->uid = $user->uid;
		$node->status = 1;
		$node->promote = 1;
		$node->comment = 1;
		$filepath = $value;
		$file = (object) array(
			'uid' => 1,
			'uri' => $filepath,
			'filemime' => file_get_mimetype($filepath),
			'status' => 1,
		);
		$file = file_copy($file, 'public://');
		$node->upload_images_image[$node->language][0] = (array)$file;
		$node->upload_images_tag_field[$node->language][]['tid'] = 7;
		$node = node_submit($node); // Prepare node for saving
		node_save($node);
	}
}

function _
