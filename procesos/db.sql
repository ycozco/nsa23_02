-- Tabla Usuarios
CREATE TABLE Usuarios (
    id INT PRIMARY KEY,
    nombre TEXT NOT NULL,
    correo_electronico TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL,
    tipo TEXT NOT NULL CHECK(tipo IN ('Estudiante', 'Administrador')),
    status TEXT NOT NULL CHECK(status IN ('Activo', 'Inactivo', 'Suspendido'))
);

-- Tabla Categorias
CREATE TABLE Categorias (
    id INT PRIMARY KEY,
    nombre TEXT NOT NULL
);

-- Tabla Lecciones
CREATE TABLE Lecciones (
    id INT PRIMARY KEY,
    titulo TEXT NOT NULL,
    descripcion TEXT,
    contenido_texto TEXT,
    ruta_imagen TEXT,
    ruta_recurso TEXT,
    id_categoria INT,
    status TEXT NOT NULL CHECK(status IN ('Publicada', 'En revision', 'Borrador')),
    FOREIGN KEY (id_categoria) REFERENCES Categorias(id)
);

-- Tabla Ejercicios
CREATE TABLE Ejercicios (
    id INT PRIMARY KEY,
    id_leccion INT,
    enunciado TEXT NOT NULL,
    ruta_imagen TEXT,
    FOREIGN KEY (id_leccion) REFERENCES Lecciones(id)
);

-- Tabla Respuestas
CREATE TABLE Respuestas (
    id INT PRIMARY KEY,
    id_ejercicio INT,
    texto_respuesta TEXT NOT NULL,
    es_correcta BOOLEAN NOT NULL,
    FOREIGN KEY (id_ejercicio) REFERENCES Ejercicios(id)
);

-- Tabla Evaluaciones
CREATE TABLE Evaluaciones (
    id INT PRIMARY KEY,
    titulo TEXT NOT NULL,
    descripcion TEXT
);

-- Tabla Evaluaciones_Ejercicios (relaciona los ejercicios que componen cada evaluación)
CREATE TABLE Evaluaciones_Ejercicios (
    id INT PRIMARY KEY,
    id_evaluacion INT,
    id_ejercicio INT,
    FOREIGN KEY (id_evaluacion) REFERENCES Evaluaciones(id),
    FOREIGN KEY (id_ejercicio) REFERENCES Ejercicios(id)
);

-- Tabla Resultados (almacena las respuestas de los usuarios a los ejercicios)
CREATE TABLE Resultados (
    id INT PRIMARY KEY,
    id_usuario INT,
    id_respuesta INT,
    FOREIGN KEY (id_usuario) REFERENCES Usuarios(id),
    FOREIGN KEY (id_respuesta) REFERENCES Respuestas(id)
);

-- Tabla Progreso
CREATE TABLE Progreso (
    id INT PRIMARY KEY,
    id_usuario INT,
    id_leccion INT,
    completada BOOLEAN NOT NULL,
    FOREIGN KEY (id_usuario) REFERENCES Usuarios(id),
    FOREIGN KEY (id_leccion) REFERENCES Lecciones(id)
);

-- Tabla Puntuaciones
CREATE TABLE Puntuaciones (
    id INT PRIMARY KEY,
    id_usuario INT,
    id_leccion INT,
    puntuacion INT CHECK(puntuacion BETWEEN 0 AND 100),
    FOREIGN KEY (id_usuario) REFERENCES Usuarios(id),
    FOREIGN KEY (id_leccion) REFERENCES Lecciones(id)
);
