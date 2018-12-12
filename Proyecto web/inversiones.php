<?php
session_start();
$usuario=$_SESSION['nuevaSesion'];
$conexion = mysqli_connect('192.168.1.3', 'Lalo', 'AdmonBasesDatos', 'banco');
$consulta = "SELECT inversion.cantidad_invertida,inversion.plazo FROM cuenta inner join inversion on inversion.Num_Cuenta=cuenta.Num_Cuenta WHERE cuenta.ID_Cliente='$usuario' and cuenta.activo=1";
$result = mysqli_query($conexion, $consulta);
$rowDesk=mysqli_fetch_assoc($result);
$conexion2 = mysqli_connect('bancorata.com', 'cliente', 'password', 'bancoRataWeb');
$consulta = "SELECT inversion.tipo,inversion.tasa_de_interes,inversion.tipo_de_tasa FROM cuenta inner join inversion on inversion.ID_Cuenta=cuenta.ID_Cuenta WHERE cuenta.ID_Cliente='$usuario' and cuenta.activo=1";
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
		<link rel="shortcut icon" type="image/x-icon" href="img/favicon.ico" />
    <title>Mi cuenta | Inversiones</title>
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
    <?php if($auxRow['tipo']!=''):?>
      <table class="table">
        <thead>
          <tr>
            <th scope="col">Tipo de Inversion</th>
            <th scope="col">Cantidad invertida</th>
            <th scope="col">Tasa de interés</th>
            <th scope="col">Tipo de tasa</th>
            <th scope="col">Plazo</th>
          </tr>
        </thead>
        <tbody>
          <?php while($row=mysqli_fetch_assoc($result)): ?>
            <tr>
              <th scope="row"><?php echo $row['tipo']; ?></th>
              <td>$<?php echo $rowDesk['cantidad_invertida']; ?></td>
              <td><?php echo $row['tasa_de_interes']; ?>%</td>
              <td><?php echo $row['tipo_de_tasa']; ?></td>
              <td><?php echo $rowDesk['plazo']; ?> Días</td>
            </tr>
          <?php endwhile;?>
        </tbody>
      </table>
    <?php
      else:
        echo'<script language="javascript">alert("El cliente no tiene inversiones contratadas :(");
        window.location.href="clientes.php";</script>';
    ?>
  <?php endif;?>

    <!--Aviso legal y así-->
    <footer class="footer">
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
  </body>
</html>
