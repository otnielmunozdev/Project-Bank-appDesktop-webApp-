<?php
	$usuario = $_POST['email'];
	$contrasenia = $_POST['contrasenia'];
	if(empty($usuario) | empty($contrasenia))
	{
		header("Location: login.php");
	}
	$conexion = mysqli_connect('bancorata.com', 'cliente', 'password', 'bancoRataWeb');
	// Check connection
	if (!$conexion)
	{
	  die("Connection failed: " . mysqli_connect_error());
	}

	$consulta = "SELECT email, contrasenia, ID_Cliente FROM cliente where email='$usuario'";
	$result = mysqli_query($conexion, $consulta);
	$row=mysqli_fetch_assoc($result);
	if ($result)
	{
		if($row['contrasenia']==$contrasenia)
		{
			$usuario=$row['ID_Cliente'];
			$conexion = mysqli_connect('192.168.1.3', 'Lalo', 'AdmonBasesDatos', 'banco');
			$consulta = "SELECT activo FROM cliente where ID_Cliente='$usuario'";
			$result = mysqli_query($conexion, $consulta);
			$row=mysqli_fetch_assoc($result);
			if($row['activo']==='1')
			{
				session_start();
				$_SESSION['nuevaSesion']=$usuario;
				header("Location: clientes.php");
			}
			else{
				header("Location: login.php");
			}
		}
		else{
			header("Location: login.php");
		}
	}
	else {
	    header("Location: login.php");
	}
?>
