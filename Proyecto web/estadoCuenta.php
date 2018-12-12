<?php
session_start();
$usuario=$_SESSION['nuevaSesion'];
$conexion = mysqli_connect('bancorata.com', 'cliente', 'password', 'bancoRataWeb');
$consulta = "SELECT * FROM cuenta WHERE ID_Cliente='$usuario'";
$result = mysqli_query($conexion, $consulta);
//$auxRow=mysqli_fetch_assoc($result);
//$consulta = "SELECT * FROM estado_de_cuenta WHERE ID_Cuenta='$cuenta'";
//$result = mysqli_query($conexion, $consulta);
//$row=mysqli_fetch_assoc($result);
?>
<!doctype html>
<html lang="en">
  <head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="css/bootstrap.css">
		<link rel="shortcut icon" type="image/x-icon" href="img/favicon.ico"/>
    <title>Mi cuenta | Estado de Cuenta</title>

  </head>

  <body>
    <!--barra de navegación-->
    <nav class="navbar navbar-expand-lg navbar-dark bg-dark sticky-top">
      <a class="navbar-brand" href="clientes.php">Clientes</a>
      <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
        <span class="navbar-toggler-icon"></span>
      </button>

      <div class="collapse navbar-collapse" id="navbarSupportedContent">
        <ul class="navbar-nav mr-auto">
          <li class="nav-item dropdown">
            <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
              Mi Cuenta
            </a>
            <div class="dropdown-menu" aria-labelledby="navbarDropdown">
              <a class="dropdown-item" href="estadoCuenta.php">Estado de Cuenta</a>
              <a class="dropdown-item" href="seguros.php">Seguros</a>
              <a class="dropdown-item" href="creditoHipotecario.php">Crédito Hipotecario</a>
              <a class="dropdown-item" href="prestamos.php">Préstamos</a>
              <a class="dropdown-item" href="inversiones.php">Inversiones</a>
              <div class="dropdown-divider"></div>
              <a class="dropdown-item" href="salir.php">Salir</a>
            </div>
          </li>
          <li class="nav-item">
            <a class="nav-link" href="promociones.php">Promociones</a>
          </li>
        </ul>
        <form class="form-inline my-2 my-lg-0">
          <input class="form-control mr-sm-2" type="search" placeholder="Buscar" aria-label="Search">
          <button type="button" class="btn btn-primary">Buscar</button>
        </form>
      </div>
    </nav>

    <!--Contenido-->
    <form name="cuenta" action="estadoCuenta2.php" method="POST">
      <div class="col-3">
        <p align="center">
          <div class="input-group mb-3">
            <div class="input-group-prepend">
              <label class="input-group-text" for="inputGroupSelect01">Tipo de producto</label>
            </div>
            <select class="custom-select" name="tipo" id="tipo" onChange="cambiar_tipo()">
              <option>Elegir opción</option>
              <?php while($cuentas=mysqli_fetch_assoc($result)):?>
                <option value=<?php echo $cuentas['ID_Cuenta'];?>><?php echo $cuentas['ID_Cuenta'];?></option>
              <?php endwhile;?>
            </select>
          </div>
        </p>
      </div>
      <div class="col-3">
        <p align="center">
          <div class="input-group mb-3">
            <div class="input-group-prepend">
              <label class="input-group-text" for="inputGroupSelect01">Periodo</label>
            </div>
            <select class="custom-select" id="periodo" name="periodo">
              <option>Elegir opción</option>
            </select>
          </div>
        </p>
      </div>
      <p></p>
      <button type="submit" class="btn btn-primary btn-lg active">Aceptar</button>
    </form>

    <!--Aviso legal y así-->
    <footer class="footer sticky-bottom">
      <div class="row">
          <div class="col">
              <p> </p>
              <p align="right"> <img src="img/logo.jpg" width="20%" height="50%"/></p>
          </div>
          <div class="col-6">
            <p align="center"><br/>Derechos reservados 2018, Banco Admon Bases de Datos (México) S.A., Institución de banca Múltiple,
              <br/>Grupo financiero Admon de Bases de Datos México, <a href="#">Aviso Legal</a></p>
          </div>
          <div class="col">
            <p> </p>   <!--para hacer un salto de linea y que la imagen quede más centrada-->
            <img src="img/esr.jpg" width="50%" height="50%"/>
          </div>
      </div>
    </footer>

    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
    <script src="js/bootstrap.js"></script>
    <script type="text/javascript">
      function cambiar_tipo()
      {
        var xmlhttp=new XMLHttpRequest();
        xmlhttp.open("GET","darTipo.php?tipo="+document.getElementById("tipo").value,false);
        xmlhttp.send(null);
        document.getElementById("periodo").innerHTML=xmlhttp.responseText;
      }
    </script>
    </script>
  </body>
</html>
