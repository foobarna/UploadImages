<?php
function upload_images_page(){
	$path = variable_get('upload_images_path','');
	if (!is_dir($path)) {
		return 'This is not a valid path to a dir!';
	}
	$output = 'These are the items: <br>';
	$accept = array('jpeg' => 1);
	$files = get_files($path);
	// $no_items = count($files);
	// for ($i = 0; $i < $no_items; $i++){
	// 	if (($files[$i] == '.') || ($files[$i] == '..') ) {
	// 		continue;
	// 	}
	// 	// if (is_dir($files[$i])) {
	// 		$output .= $files[$i] . "<br>";
	// 	// }
	// }


	return $output;
}

function get_files($path, $accept = array()){
	$files = array();
	return $files;
}
