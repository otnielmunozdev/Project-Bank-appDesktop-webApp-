-- phpMyAdmin SQL Dump
-- version 4.7.9
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 24-05-2018 a las 17:47:01
-- Versión del servidor: 10.1.31-MariaDB
-- Versión de PHP: 7.2.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `banco`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `citas`
--

CREATE TABLE `citas` (
  `id_cita` int(11) NOT NULL,
  `fecha` date NOT NULL,
  `hora` time NOT NULL,
  `sucursal` varchar(30) NOT NULL,
  `id_cliente` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `cliente`
--

CREATE TABLE `cliente` (
  `id_cliente` varchar(30) NOT NULL,
  `sexo` char(1) NOT NULL,
  `ciudad` varchar(30) NOT NULL,
  `fecha_nac` date NOT NULL,
  `telefono` varchar(15) NOT NULL,
  `curp` varchar(19) NOT NULL,
  `domicilio` varchar(30) NOT NULL,
  `correo_electronico` varchar(40) NOT NULL,
  `nombre` varchar(50) NOT NULL,
  `id_suc` varchar(15) NOT NULL,
  `activo` int(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `cliente`
--

-- INSERT INTO `cliente` (`id_cliente`, `sexo`, `ciudad`, `fecha_nac`, `telefono`, `curp`, `domicilio`, `correo_electronico`, `nombre`, `id_suc`, `activo`) VALUES
-- ('123456789', 'H', 'Guadalajara', '1996-07-08', '332345454', 'as4das', 'isla gomera', 'lalo.a.camarena@gmail.com', 'lalo camarena', 'ATJ420', 1),
-- ('M53RM67C77', 'H', 'Guadalajara', '2000-01-01', '3318165135', 'CSEA2352352', 'Casita 66', 'EduardoAt2@gmail.com', 'Camarena Santamaria Eduardo Atonatiuh', 'ATJ420', 1);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `credito_hipotecario`
--

CREATE TABLE `credito_hipotecario` (
  `id_credito` int(11) NOT NULL,
  `mensualidad` float NOT NULL,
  `total` float NOT NULL,
  `monto_prima` float NOT NULL,
  `valor_inmueble` int(11) NOT NULL,
  `num_cuenta` varchar(16) NOT NULL,
  `activo` int(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `credito_hipotecario`
--

-- INSERT INTO `credito_hipotecario` (`id_credito`, `mensualidad`, `total`, `monto_prima`, `valor_inmueble`, `num_cuenta`, `activo`) VALUES
-- (1, 11, 11, 11, 11, '6512216066048546', 1),
-- (2, 11, 11, 11, 11, '6512216066048546', 1),
-- (3, 222, 222, 222, 2222, '6512216066048546', 1),
-- (4, 1, 3, 6, 5, '6512216066048546', 1),
-- (5, 5555, 5555, 5555, 5555, '6512216066048546', 1);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `cuenta`
--

CREATE TABLE `cuenta` (
  `num_cuenta` varchar(16) NOT NULL,
  `saldo` int(11) NOT NULL,
  `tipo` varchar(20) DEFAULT NULL,
  `codigo_seguridad` int(11) NOT NULL,
  `fecha_tramite` date NOT NULL,
  `id_cliente` varchar(20) NOT NULL,
  `activo` int(1) NOT NULL,
  `fecha_corte` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `cuenta`
--

-- INSERT INTO `cuenta` (`num_cuenta`, `saldo`, `tipo`, `codigo_seguridad`, `fecha_tramite`, `id_cliente`, `activo`, `fecha_corte`) VALUES
-- ('0828703185317606', 6000, 'Rata Zero', 8261, '2018-05-23', 'M53RM67C77', 1, '0000-00-00'),
-- ('1234567890987654', 5000, 'Tarjeta de credito', 123, '2018-05-02', '123456789', 1, '0000-00-00'),
-- ('2321873001782405', 69000, 'Supreme', 5341, '2018-05-23', '123456789', 1, '2018-05-23'),
-- ('6512216066048546', 50000, 'Super Rata', 2620, '2018-05-23', 'M53RM67C77', 1, '0000-00-00');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `empleado`
--

CREATE TABLE `empleado` (
  `id_empleado` varchar(30) NOT NULL,
  `nombre` varchar(30) NOT NULL,
  `curp` varchar(19) NOT NULL,
  `puesto` varchar(15) NOT NULL,
  `sexo` char(1) NOT NULL,
  `correo_electronico` varchar(40) NOT NULL,
  `telefono` varchar(15) NOT NULL,
  `fecha_nac` date NOT NULL,
  `rfc` varchar(30) NOT NULL,
  `salario` int(11) NOT NULL,
  `horario` time NOT NULL,
  `id_suc` varchar(15) NOT NULL,
  `activo` int(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `empleado`
--

 INSERT INTO `empleado` (`id_empleado`, `nombre`, `curp`, `puesto`, `sexo`, `correo_electronico`, `telefono`, `fecha_nac`, `rfc`, `salario`, `horario`, `id_suc`, `activo`) VALUES
 ('Admin0', 'Gonzalez Camacho Diego', 'GCD420', 'Administrador', 'M', 'DiegoGCC@gmail.com', '33186123065', '1996-03-15', 'FSDFSDFS', 42000, '09:00:00.000000', 'ATJ420', 1);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `inversion`
--

CREATE TABLE `inversion` (
  `id_inversion` int(11) NOT NULL,
  `cantidad_invertida` int(11) NOT NULL,
  `plazo` int(11) NOT NULL,
  `num_cuenta` varchar(16) NOT NULL,
  `activo` int(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `inversion`
--

-- INSERT INTO `inversion` (`id_inversion`, `cantidad_invertida`, `plazo`, `num_cuenta`, `activo`) VALUES
-- (1, 5000, 25, '6512216066048546', 1);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `prestamo`
--

CREATE TABLE `prestamo` (
  `id_prestamo` int(11) NOT NULL,
  `mensualidad` int(11) NOT NULL,
  `total` int(11) DEFAULT NULL,
  `num_cuenta` varchar(16) NOT NULL,
  `activo` int(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `prestamo`
--

-- INSERT INTO `prestamo` (`id_prestamo`, `mensualidad`, `total`, `num_cuenta`, `activo`) VALUES
-- (1, 1, 1, '6512216066048546', 1),
-- (2, 2, 2, '6512216066048546', 1);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `seguros`
--

CREATE TABLE `seguros` (
  `num_poliza` int(11) NOT NULL,
  `importe_prima_anual` float NOT NULL,
  `suma_asegurada` float NOT NULL,
  `plazo_seguro` int(11) NOT NULL,
  `plazo_pago` int(11) NOT NULL,
  `num_cuenta` varchar(16) NOT NULL,
  `activo` int(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `seguros`
--

-- INSERT INTO `seguros` (`num_poliza`, `importe_prima_anual`, `suma_asegurada`, `plazo_seguro`, `plazo_pago`, `num_cuenta`, `activo`) VALUES
-- (3, 111, 111, 111, 111, '6512216066048546', 1);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `sucursal`
--

CREATE TABLE `sucursal` (
  `id_suc` varchar(15) NOT NULL,
  `telefono` varchar(15) NOT NULL,
  `direccion` varchar(30) NOT NULL,
  `horario` time DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `sucursal`
--

INSERT INTO `sucursal` (`id_suc`, `telefono`, `direccion`, `horario`) VALUES
('ATJ420', '33855479', 'Atemajac #54', '08:00:00.000000');

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `citas`
--
ALTER TABLE `citas`
  ADD PRIMARY KEY (`id_cita`),
  ADD KEY `id_cliente` (`id_cliente`);

--
-- Indices de la tabla `cliente`
--
ALTER TABLE `cliente`
  ADD PRIMARY KEY (`id_cliente`),
  ADD KEY `id_suc` (`id_suc`);

--
-- Indices de la tabla `credito_hipotecario`
--
ALTER TABLE `credito_hipotecario`
  ADD PRIMARY KEY (`id_credito`),
  ADD KEY `num_cuenta` (`num_cuenta`);

--
-- Indices de la tabla `cuenta`
--
ALTER TABLE `cuenta`
  ADD PRIMARY KEY (`num_cuenta`),
  ADD KEY `id_cliente` (`id_cliente`);

--
-- Indices de la tabla `empleado`
--
ALTER TABLE `empleado`
  ADD PRIMARY KEY (`id_empleado`),
  ADD KEY `id_suc` (`id_suc`);

--
-- Indices de la tabla `inversion`
--
ALTER TABLE `inversion`
  ADD PRIMARY KEY (`id_inversion`),
  ADD KEY `num_cuenta` (`num_cuenta`);

--
-- Indices de la tabla `prestamo`
--
ALTER TABLE `prestamo`
  ADD PRIMARY KEY (`id_prestamo`),
  ADD KEY `num_cuenta` (`num_cuenta`);

--
-- Indices de la tabla `seguros`
--
ALTER TABLE `seguros`
  ADD PRIMARY KEY (`num_poliza`),
  ADD KEY `num_cuenta` (`num_cuenta`);

--
-- Indices de la tabla `sucursal`
--
ALTER TABLE `sucursal`
  ADD PRIMARY KEY (`id_suc`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `citas`
--
ALTER TABLE `citas`
  MODIFY `id_cita` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `credito_hipotecario`
--
ALTER TABLE `credito_hipotecario`
  MODIFY `id_credito` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT de la tabla `inversion`
--
ALTER TABLE `inversion`
  MODIFY `id_inversion` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT de la tabla `prestamo`
--
ALTER TABLE `prestamo`
  MODIFY `id_prestamo` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT de la tabla `seguros`
--
ALTER TABLE `seguros`
  MODIFY `num_poliza` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- Restricciones para tablas volcadas
--

--
-- Filtros para la tabla `citas`
--
ALTER TABLE `citas`
  ADD CONSTRAINT `citas_ibfk_1` FOREIGN KEY (`id_cliente`) REFERENCES `cliente` (`id_cliente`);

--
-- Filtros para la tabla `cliente`
--
ALTER TABLE `cliente`
  ADD CONSTRAINT `cliente_ibfk_1` FOREIGN KEY (`id_suc`) REFERENCES `sucursal` (`id_suc`);

--
-- Filtros para la tabla `credito_hipotecario`
--
ALTER TABLE `credito_hipotecario`
  ADD CONSTRAINT `credito_hipotecario_ibfk_1` FOREIGN KEY (`num_cuenta`) REFERENCES `cuenta` (`num_cuenta`);

--
-- Filtros para la tabla `cuenta`
--
ALTER TABLE `cuenta`
  ADD CONSTRAINT `cuenta_ibfk_1` FOREIGN KEY (`id_cliente`) REFERENCES `cliente` (`id_cliente`);

--
-- Filtros para la tabla `empleado`
--
ALTER TABLE `empleado`
  ADD CONSTRAINT `empleado_ibfk_1` FOREIGN KEY (`id_suc`) REFERENCES `sucursal` (`id_suc`);

--
-- Filtros para la tabla `inversion`
--
ALTER TABLE `inversion`
  ADD CONSTRAINT `inversion_ibfk_1` FOREIGN KEY (`num_cuenta`) REFERENCES `cuenta` (`num_cuenta`);

--
-- Filtros para la tabla `prestamo`
--
ALTER TABLE `prestamo`
  ADD CONSTRAINT `prestamo_ibfk_1` FOREIGN KEY (`num_cuenta`) REFERENCES `cuenta` (`num_cuenta`);

--
-- Filtros para la tabla `seguros`
--
ALTER TABLE `seguros`
  ADD CONSTRAINT `seguros_ibfk_1` FOREIGN KEY (`num_cuenta`) REFERENCES `cuenta` (`num_cuenta`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
