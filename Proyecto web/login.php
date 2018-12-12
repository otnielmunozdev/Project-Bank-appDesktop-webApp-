<!doctype html>
<html lang="en">
  <head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="css/bootstrap.css">
    <link rel="stylesheet" href="css/signin.css">
		<link rel="shortcut icon" type="image/x-icon" href="img/favicon.ico" />
    <title>Mi cuenta | Ingresar</title>

  </head>

  <body>
    <center>
      <img src="img/logo.jpg" height="20%" width="20%">
      <p></p>
      <div class="col-6">
        <form action="validarLogin.php" method="POST">
          <div class="form-group">
            <label for="exampleInputEmail1">Correo Electrónico</label>
            <input type="email" class="form-control" name="email" aria-describedby="emailHelp" placeholder="Ingrese su correo">
          </div>
          <div class="form-group">
            <label for="exampleInputPassword1">Contraseña</label>
            <input type="password" class="form-control" name="contrasenia" placeholder="Ingrese su contraseña">
          </div>
          <button type="submit" class="btn btn-primary btn-lg active">Entrar</button>
        </form>
      </div>
    </center>
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
    <script src="js/bootstrap.js"></script>
  </body>
</html>
