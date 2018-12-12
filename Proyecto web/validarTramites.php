<?php
  session_start();
  $usuario=$_SESSION['nuevaSesion'];
  $fecha=$_POST['fecha'].':00';
  $sucursal=$_POST['sucursal'];
  $conexionLocal=mysqli_connect('bancorata.com', 'cliente', 'password', 'bancoRataWeb');
  $conexionRed=mysqli_connect('192.168.1.3', 'Lalo', 'AdmonBasesDatos', 'banco');
  $consulta="INSERT INTO cita(fecha,sucursal,ID_Cliente) VALUES('$fecha','$sucursal','$usuario')";
  $result=mysqli_query($conexionLocal,$consulta);
  $consulta="INSERT INTO citas(fecha,sucursal,ID_Cliente) VALUES('$fecha','$sucursal','$usuario')";
  $result=mysqli_query($conexionRed,$consulta);
  header('Location: clientes.php');
?>
