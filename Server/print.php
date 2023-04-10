<?php
  $file_to_read = fopen('saldos.csv', 'r');
  if($file_to_read !== FALSE){
      
      echo "<table>\n";
      while(($data = fgetcsv($file_to_read, 100, ',')) !== FALSE){
          echo "<tr>";
          for($i = 0; $i < count($data); $i++) {
              echo "<td>".$data[$i]."</td>";
          }
          echo "</tr>\n";
      }
      echo "</table>\n";
      fclose($file_to_read);
  }
?>

<html>
<body>
  <br>
  <form action="index.php">
    Voltar: <br>
  <input type="submit">
  </form>
</body>
</html>