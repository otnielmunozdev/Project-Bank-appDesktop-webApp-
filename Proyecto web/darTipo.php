<?php
  $conexion = mysqli_connect('bancorata.com', 'cliente', 'password', 'bancoRataWeb');
  $cuenta=$_GET['tipo'];
  $consulta="SELECT DATE_FORMAT(fecha_de_compra,'%m/%Y') as periodo_chido FROM movimiento WHERE ID_Cuenta='$cuenta' GROUP BY periodo_chido ORDER BY periodo_chido";
  if($cuenta!=='')
  {
    $result=mysqli_query($conexion,$consulta);
    echo "<select class='custom-select' name='periodo' id='periodo'>";
      echo "<option>Elegir opción</option>";
      while($row=mysqli_fetch_assoc($result))
      {
        echo "<option value='$row[periodo_chido]'>";
          echo $row['periodo_chido'];
        echo "</option>";
      }
    echo "</select>";
  }
?>
