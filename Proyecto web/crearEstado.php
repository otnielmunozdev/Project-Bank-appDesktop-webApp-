<?php
  $conexion = mysqli_connect('bancorata.com', 'cliente', 'password', 'bancoRataWeb');
  $periodo=$_POST['periodo'];
  $consulta="SELECT * FROM movimiento WHERE DATE_FORMAT(fecha_de_compra,'%m/%Y')='$periodo' ORDER BY fecha_de_compra";
  if($periodo!=='')
  {
    $result=mysqli_query($conexion,$consulta);
    echo "<table>";
      echo "<thead>";
        echo "<tr>";
          echo "<th scope='col'>Costo</th>";
          echo "<th scope='col'>Referencia</th>";
          echo "<th scope='col'>Fecha de compra</th>";
        echo "</tr>";
      echo "</thead>";
      echo "<tbody>";
        echo "<tr>";
          while($row=mysqli_fetch_assoc($result))
          {
            echo "<th scope='row'>".$row['costo']."</th>";
            echo "<td>".$row['referencia']."</td>";
            echo "<td>"$row['fecha_de_compra']."</td>";
          }
        echo "</tr>";
      echo "</tbody>";
    echo "</table>";
  }
?>
