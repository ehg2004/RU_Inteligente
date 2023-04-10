<?php
  function csvToArray(){
    $file_to_read = fopen('saldos.csv', 'r');
    while (!feof($file_to_read) ) {
      $lines[] = fgetcsv($file_to_read, 1000, ',');
    }
    fclose($file_to_read);
    return $lines;
  }
  function arrayToCsv($lines)
  {
    $file = fopen('saldos.csv', 'w');
    $size = sizeof($lines);
    for ($i=0; $i < $size; $i++) { 
      fputcsv($file, $lines[$i]);
    }
    fclose($file);
  }

  if(!($_POST["RA"] && $_POST["RFID"]))
  {
    redirect("index.php");
  }

  $lines = csvToArray();

  $size = sizeof($lines);
  $lines[$size-1][0] = $_POST["RA"];
  $lines[$size-1][1] = $_POST["RFID"];
  $lines[$size-1][2] = 0;
  
  arrayToCsv($lines);

  function redirect($url) {
    header('Location: '.$url);
    die();
  }
  redirect("index.php");
?>