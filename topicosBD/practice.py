from datetime import datetime
from typing import List, Tuple


class ServicioAvion:
    def _init_(self, hora: datetime, codigo: Tuple[str, datetime]):
        self.hora = hora
        self.codigo = codigo


class Propietario:
    def _init_(self, num_acciones: int, fecha_com: datetime):
        self.num_acciones = num_acciones
        self.fecha_com = fecha_com


class Persona(Propietario):
    def _init_(self, nombre: str, dni: str, direccion: Tuple[str, int, str], fecha_nac: datetime, *args, **kwargs):
        super()._init_(*args, **kwargs)
        self.nombre = nombre
        self.dni = dni
        self.direccion = direccion
        self.fecha_nac = fecha_nac


class Empresa(Propietario):
    def _init_(self, nombre: str, direccion: Tuple[str, int], telefono: str, *args, **kwargs):
        super()._init_(*args, **kwargs)
        self.nombre = nombre
        self.direccion = direccion
        self.telefono = telefono


class Nave:
    def _init_(self, capacidad: int):
        self.capacidad = capacidad


class Taller:
    def _init_(self, herramienta: str):
        self.herramienta = herramienta


class Hangar:
    def _init_(self, numero: int, lugar: str, nave: Nave, talleres: List[Taller]):
        self.numero = numero
        self.lugar = lugar
        self.nave = nave
        self.talleres = talleres


class Empleado:
    def _init_(self, salario: float, num_emp: int, titulacion: Tuple[str, datetime]):
        self.salario = salario
        self.num_emp = num_emp
        self.titulacion = titulacion


class Piloto(Empleado):
    def _init_(self, licencia: str, horas_vuelo: Tuple[int, int], *args, **kwargs):
        super()._init_(*args, **kwargs)
        self.licencia = licencia
        self.horas_vuelo = horas_vuelo


class ModeloAvion:
    def _init_(self, capacidad: int, peso: int, modelo: str, expertos: List[Empleado], pilotos: List[Piloto]):
        self.capacidad = capacidad
        self.peso = peso
        self.modelo = modelo
        self.expertos = expertos
        self.pilotos = pilotos


class Avion:
    def _init_(self, modelo_avion: ModeloAvion, servicios: List[ServicioAvion], propietario: Propietario, hangar: Hangar):
        self.modelo_avion = modelo_avion
        self.servicios = servicios
        self.propietario = propietario
        self.hangar = hangar
        

# Ejemplo de cómo usar las clases

# Crear un propietario persona
propietario_persona = Persona(nombre="John Doe", dni="12345678", direccion=("Main St", 123, "City"), fecha_nac=datetime(1980, 5, 1), num_acciones=10, fecha_com=datetime(2023, 6, 7))

# Crear un modelo de avion
piloto = Piloto(licencia="XYZ", horas_vuelo=(1000, 30), salario=500)
