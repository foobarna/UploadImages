<?php
function upload_images_create(){
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
		$output_array = array_keys($files);
		$output = array(
			'list_images' => array(
				'#items' => $output_array,
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
	// _create_taxonomy_term("works? again and again", 9, 14);
	// $bu = _taxonomy_terms_from_path("path/to/absolute/knowledge/");
	// print_r($bu);
	// _create_taxonomy_terms(_taxonomy_terms_from_path("/testing3/the3/begining3/or3/ending3///"));
	$node = array(
								"#name" => "WORKS!!spoon",
								"#full_path" => "sites/default/images_module/IspoonNutella.jpg",
								"#rel_path" => "/IspoonNutella.jpg",
								"#source_path" => variable_get("upload_images_path", ""),
								"#taxonomy_terms" => _taxonomy_terms_from_path("/IspoonNutella.jpg"),
								);
	_create_node($node);
	// print_r(array_keys($var));
	// drupal_set_message($node["#source_path"],'warning');


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

function _get_files($path, $accept, $rel_path = ""){
	$dir = opendir($path);
	$files = array();
	while ($entry = readdir($dir)) {
		if (substr($entry, 0, 1) == ".") { continue; }
		$next_path = $path . "/";
		$next_path .= $entry;
		$next_rel_path = $rel_path . "/";
		$next_rel_path .= $entry;
		if (is_dir($next_path)) {
			$files_next = _get_files($next_path,$accept, $next_rel_path);
			// asort($files_next);
			$files = array_merge($files, $files_next);
		} elseif (_accepted($entry, $accept)) {
			$files[$next_rel_path] = array(
								"#name" => $entry,
								"#full_path" => $next_path,
								"#rel_path" => $next_rel_path,
								"#taxonomy_terms" => _taxonomy_terms_from_path($rel_path),
								);
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

function _taxonomy_terms_from_path($rel_path) {
	return array_filter(explode('/',$rel_path));
}

function _create_taxonomy_term($term = "", $vid = 0, $pid = 0) {
	$new_term = array(
					'vid' => $vid,
					'name' => $term,
					'parent' => $pid,
				);
	// if (!empty($pid)) $new_term[] = array('parent' => $pid);
	$new_term = (object)$new_term;
	taxonomy_term_save($new_term);
	return $new_term->tid;
}

function _create_taxonomy_terms($terms = array()) {
	$vocabulary = taxonomy_vocabulary_machine_name_load("upload_images_vocabulary");
	$taxonomy_tids = array();
	$pid = 0;
	foreach ($terms as $term_name) {
		$existing_terms = taxonomy_get_term_by_name($term_name, $vocabulary->machine_name);
		if ($existing_terms) {
			foreach ($existing_terms as $term)
				if ($term->vid == $vocabulary->vid) {
					$pid = $term->tid;
					break;
				}
		} else {
			$pid = _create_taxonomy_term($term_name, $vocabulary->vid, $pid);
		}
		$taxonomy_tids[] = $pid;
	}
	return $taxonomy_tids;
}

function _create_node($prenode) {
	global $user;
	$tids = _create_taxonomy_terms($prenode["#taxonomy_terms"]);
	$node = new stdClass();
	$node->title = $prenode["#name"];
	$node->type = 'upload_images';
	node_object_prepare($node);
	$node->language = LANGUAGE_NONE;
	$node->uid = $user->uid;
	$node->status = 1;
	$node->promote = 1;
	$node->comment = 1;
	$filepath = $prenode["#full_path"];
	$file = (object) array(
		'uid' => 1,
		'uri' => $filepath,
		'filemime' => file_get_mimetype($filepath),
		'status' => 1,
	);
	$file = file_copy($file, 'public:/upload_images_folder/');
	$node->upload_images_image[$node->language][0] = (array)$file;
	foreach ($tids as $tid) {
		$node->upload_images_tag_field[$node->language][]['tid'] = $tid;
	}
	$node = node_submit($node); // Prepare node for saving
		node_save($node);
}

function _create_content($files) {

	}
