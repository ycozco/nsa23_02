CREATE TABLE `Usuarios` (
  `id` INT PRIMARY KEY,
  `nombre` TEXT NOT NULL,
  `correo_electronico` TEXT UNIQUE NOT NULL,
  `password` TEXT NOT NULL,
  `tipo` TEXT NOT NULL,
  `status` TEXT NOT NULL
);

CREATE TABLE `Lecciones` (
  `id` INT PRIMARY KEY,
  `titulo` TEXT NOT NULL,
  `descripcion` TEXT,
  `material` TEXT,
  `status` TEXT NOT NULL
);

CREATE TABLE `Ejercicios` (
  `id` INT PRIMARY KEY,
  `id_leccion` INT,
  `enunciado` TEXT NOT NULL,
  `solucion_correcta` TEXT NOT NULL
);

CREATE TABLE `Resultados` (
  `id` INT PRIMARY KEY,
  `id_usuario` INT,
  `id_ejercicio` INT,
  `respuesta_estudiante` TEXT
);

CREATE TABLE `Progreso` (
  `id` INT PRIMARY KEY,
  `id_usuario` INT,
  `id_leccion` INT,
  `completada` BOOLEAN NOT NULL
);

ALTER TABLE `Ejercicios` ADD FOREIGN KEY (`id_leccion`) REFERENCES `Lecciones` (`id`);

ALTER TABLE `Resultados` ADD FOREIGN KEY (`id_usuario`) REFERENCES `Usuarios` (`id`);

ALTER TABLE `Resultados` ADD FOREIGN KEY (`id_ejercicio`) REFERENCES `Ejercicios` (`id`);

ALTER TABLE `Progreso` ADD FOREIGN KEY (`id_usuario`) REFERENCES `Usuarios` (`id`);

ALTER TABLE `Progreso` ADD FOREIGN KEY (`id_leccion`) REFERENCES `Lecciones` (`id`);
