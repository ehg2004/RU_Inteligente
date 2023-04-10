<?php
  //http://localhost:8888/arduino.php/?code=123&value=5
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
    for ($i=0; $i < $size-1; $i++) { 
      fputcsv($file, $lines[$i]);
    }
    fclose($file);
  }
  
  $flag = 0;
  $lines = csvToArray();
  $size = sizeof($lines);
  $flag = 0;
  for ($i=0; $i < $size-1; $i++) 
  { 
    if  ($lines[$i][1] == $_GET["code"])
    {
      if((int)$lines[$i][2] >= (int)$_GET["value"])
      {
        $lines[$i][2] = (int)$lines[$i][2] - (int)$_GET["value"];
        $flag = 1;
        echo json_encode(1);
      }
      break;
    }
  }
  if(!$flag)
  {
    echo json_encode(0);
  }
  arrayToCsv($lines);
?>