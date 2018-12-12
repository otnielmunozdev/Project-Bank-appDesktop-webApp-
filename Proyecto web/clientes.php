<?php
session_start();
$usuario=$_SESSION['nuevaSesion'];
$conexion = mysqli_connect('192.168.1.3', 'Lalo', 'AdmonBasesDatos', 'banco');
$consulta = "SELECT  DATE_FORMAT(Fecha_Tramite,'%d') as dia,DATE_FORMAT(Fecha_Tramite,'%m') as mes,Saldo,Tipo,Num_Cuenta FROM cuenta WHERE ID_Cliente='$usuario' and activo=1";
$result = mysqli_query($conexion, $consulta);
$auxRow=mysqli_fetch_assoc($result);
$result = mysqli_query($conexion, $consulta);
?>
<!doctype html>
<html lang="en">
  <head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="css/bootstrap.css">
    <link rel="stylesheet" href="css/jquery.datetimepicker.min.css">
    <link rel="stylesheet" href="css/footer.css">
		<link rel="shortcut icon" type="image/x-icon" href="img/favicon.ico" />
    <title>Mi cuenta | Clientes</title>

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
    <div class="row">
      <div class="col">
        <p> </p>
        <img src="img/logo.jpg" height="75%" width="50%">
      </div>
      <div class="col">
        <?php if($auxRow['Tipo']!==''): ?>
          <table class="table">
            <thead>
              <tr>
                <th scope="col">Número de Tarjeta/Referencia</th>
                <th scope="col">Tipo de Producto</th>
                <th scope="col">Total a pagar</th>
                <th scope="col">Fecha límite de pago</th>
              </tr>
            </thead>
            <?php while ($row=mysqli_fetch_assoc($result)): ?>
              <?php
                $dia=(integer)$row['dia'];
                $dia=$dia+15;
                $mes=(integer)$row['mes'];
                if($mes===2 and $dia>28)
                {
                  $mes=3;
                  $dia=dia-28;
                }
                elseif($mes===1 or $mes===3 or $mes===5 or $mes===7 or $mes===8 or $mes===10 or $mes===12)
                {
                  if($dia>31)
                  {
                    $mes=$mes+1;
                    $dia=$dia-31;
                  }
                }
                else{
                  if($dia>30)
                  {
                    $mes=$mes+1;
                    $dia=$dia-30;
                  }
                }
                if($mes===1)
                {
                  $nuevoMes='Enero';
                }
                elseif($mes===2)
                {
                  $nuevoMes='Febrero';
                }
                elseif($mes===3)
                {
                  $nuevoMes='Marzo';
                }
                elseif($mes===4)
                {
                  $nuevoMes='Abril';
                }
                elseif($mes===5)
                {
                  $nuevoMes='Mayo';
                }
                elseif($mes===6)
                {
                  $nuevoMes='Junio';
                }
                elseif($mes===7)
                {
                  $nuevoMes='Julio';
                }
                elseif($mes===8)
                {
                  $nuevoMes='Agosto';
                }
                elseif($mes===9)
                {
                  $nuevoMes='Septiembre';
                }
                elseif($mes===10)
                {
                  $nuevoMes='Octubre';
                }
                elseif($mes===11)
                {
                  $nuevoMes='Noviembre';
                }
                elseif($mes===12)
                {
                  $nuevoMes='Diciembre';
                }
                $fecha_limite=(string)$dia.' de '.$nuevoMes;
              ?>
              <tbody>
                <tr>
                  <th scope="row"><?php echo $row['Num_Cuenta']; ?></th>
                  <td><?php echo $row['Tipo']; ?></td>
                  <td><?php echo $row['Saldo']; ?></td>
                  <td><?php echo $fecha_limite; ?></td>
                </tr>
              </tbody>
            <?php endwhile; ?>
          </table>
        <?php endif; ?>
        <p></p>
        <center>
          <form action="validarTramites.php" method="POST">
            <h4>Agendar una cita</h4>
            <input type="text" class="form-control2" id="datetime" name="fecha" placeholder="Ingrese la fecha de la cita">
            <p></p>
            <?php
              $conexion = mysqli_connect('192.168.1.3', 'Lalo', 'AdmonBasesDatos', 'banco');
              $consulta = "SELECT direccion FROM sucursal";
              $result = mysqli_query($conexion, $consulta);
              $auxRow=mysqli_fetch_assoc($result);
              $result = mysqli_query($conexion, $consulta);
            ?>
            <div class="col-5">
              <p align="center">
                <div class="input-group mb-3">
                  <div class="input-group-prepend">
                    <label class="input-group-text" for="inputGroupSelect01">Sucursal</label>
                  </div>
                  <select class="custom-select" id="sucursal" name="sucursal">
                    <option>Elegir opción</option>
                    <?php while($sucursal=mysqli_fetch_assoc($result)):?>
                      <option value=<?php echo $sucursal['direccion'];?>><?php echo $sucursal['direccion'];?></option>
                    <?php endwhile;?>
                  </select>
                </div>
              </p>
            </div>
            <button type="submit" class="btn btn-primary btn-lg active">Aceptar</button>
            <p></p>
          </form>
          <?php
            $conexion = mysqli_connect('bancorata.com', 'cliente', 'password', 'bancoRataWeb');
            $consulta = "SELECT DATE_FORMAT(fecha,'%d/%m/%Y %H:%i') as dia,sucursal FROM cita WHERE ID_Cliente='$usuario' order by fecha";
            $result = mysqli_query($conexion, $consulta);
            $auxRow=mysqli_fetch_assoc($result);
            $result = mysqli_query($conexion, $consulta);
          ?>
          <?php if($auxRow['fecha']!==''): ?>
            <h4>Citas agendadas por el cliente</h4>
            <?php while($row=mysqli_fetch_assoc($result)):?>
              <p><?php echo 'Fecha: '.$row['dia'].'  -  Sucursal: '.$row['sucursal']?></p>
            <?php endwhile;?>
          <?php endif;?>
        </center>
      </div>
    </div>

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
    <script src="js/jquery.js"></script>
    <script src="js/jquery.datetimepicker.full.js"></script>
    <script>
      $( function() {
        $( "#datetime" ).datetimepicker();
      } );
    </script>
  </body>
</html>
