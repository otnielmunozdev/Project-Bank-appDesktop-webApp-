<?php
session_start();
$usuario=$_SESSION['nuevaSesion'];
$conexion = mysqli_connect('192.168.1.3', 'Lalo', 'AdmonBasesDatos', 'banco');
$consulta = "SELECT seguros.importe_prima_anual,seguros.suma_asegurada,seguros.plazo_seguro,seguros.plazo_pago FROM cuenta inner join seguros on seguros.Num_Cuenta=cuenta.Num_Cuenta WHERE cuenta.ID_Cliente='$usuario' and cuenta.activo=1";
$result = mysqli_query($conexion, $consulta);
$rowDesk=mysqli_fetch_assoc($result);
$conexion2 = mysqli_connect('bancorata.com', 'cliente', 'password', 'bancoRataWeb');
$consulta = "SELECT seguro.empresa,seguro.descuento,seguro.moneda,seguro.cobertura FROM cuenta inner join seguro on seguro.ID_Cuenta=cuenta.ID_Cuenta WHERE cuenta.ID_Cliente='$usuario'  and cuenta.activo=1";
$result = mysqli_query($conexion2,$consulta);
$auxRow=mysqli_fetch_assoc($result);
$result = mysqli_query($conexion2, $consulta);
?>
<!doctype html>
<html lang="en">
  <head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="css/bootstrap.css">
    <link href="sticky-footer-navbar.css" rel="stylesheet">
		<link rel="shortcut icon" type="image/x-icon" href="img/favicon.ico" />
    <title>Mi cuenta | Seguro</title>

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
    <!--Datos-->
    <?php if($auxRow['empresa']!=''):?>
      <?php while($row=mysqli_fetch_assoc($result)): ?>
        <table class="table">
          <thead>
            <tr>
              <th scope="col">Empresa</th>
              <th scope="col">Descuento</th><!--Cada cuando te roban. Lo más común es quincenal, mensual y anual-->
              <th scope="col">Moneda</th>
              <th scope="col">Importe prima anual</th><!--Lo que te van a a robar al año-->
            </tr>
          </thead>
          <tbody>
            <tr>
              <th scope="row"><?php echo $row['empresa'];?></th>
              <td>$<?php echo $row['descuento'];?></td>
              <td><?php echo $row['moneda'];?></td>
              <td>$<?php echo $rowDesk['importe_prima_anual'];?></td>
            </tr>
          </tbody>
        </table>
        <table class="table">
          <thead>
            <tr>
              <th scope="col">Cobertura</th><!--Lo que cubre la póliza-->
              <th scope="col">Suma asegurada</th><!--Cuánto te pagan alv-->
              <th scope="col">Plazo de seguro</th><!--Tiempo en el que estás asegurado-->
              <th scope="col">Plazo de Pago</th><!--Tiempo en el vas a pagar-->
            </tr>
          </thead>
          <tbody>
            <tr>
              <th scope="row"><?php echo $row['cobertura'];?></th>
              <td>$<?php echo $rowDesk['suma_asegurada'];?></td>
              <td><?php echo $rowDesk['plazo_seguro'];?> Años</td>
              <td><?php echo $rowDesk['plazo_pago'];?> Años</td>
            <tr>
          </tbody>
        </table>
      <?php endwhile; ?>
    <?php
    else:
      echo'<script language="javascript">alert("El cliente no tiene Seguros contratados :(");
      window.location.href="clientes.php";</script>';
    ?>
  <?php endif;?>

    <!--Aviso legal y así-->
    <footer class="footer" position="absolute">
      <div class="container">
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
      <div>
    </footer>

    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
    <script src="js/bootstrap.js"></script>
  </body>
</html>
