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
    for ($i=0; $i < $size-1; $i++) { 
      fputcsv($file, $lines[$i]);
    }
    fclose($file);
  }
  
  $saldoAnt = 0;
  $saldoAt = 0;
  $lines = csvToArray();
  $size = sizeof($lines);
  $flag = 0;
  for ($i=0; $i < $size-1; $i++) 
  { 
    if  ($lines[$i][0] == $_POST["RA"])
    {
      $saldoAnt = $lines[$i][2];
      $lines[$i][2] = (int)($lines[$i][2]) + (int)($_POST["Valor"]);
      $saldoAt = $lines[$i][2];
      $flag = 1;
      break;
    }
  }
  arrayToCsv($lines);
?>
<html>
<body>
<br>
  RA: <?php echo $_POST["RA"]?> <br>
  Saldo aumentado: <?php echo $_POST["Valor"]?> <br>
  Saldo anterior: <?php echo $saldoAnt?> <br>
  Saldo atual: <?php echo $saldoAt?> <br>
  <br>
  <form action="index.php">
    Voltar: <br>
  <input type="submit">
  </form>
</body>
</html>
