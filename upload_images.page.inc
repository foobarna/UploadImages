<?php
function upload_images_page(){
	$path = variable_get('upload_images_path','');
	if (!is_dir($path)) {
		return 'This is not a valid path to a dir!';
	}
	$output = 'These are the items: <br>';
	$accept = array('jpg','bmp','jpeg');
	$files = get_files($path,$accept);
	foreach ($files as $name => $path) {
		$output .= '<a href=' . urlencode($path) . '>'. $name . '</a><br>';
	}
	return $output;
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

