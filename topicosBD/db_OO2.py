from tinydb import TinyDB, Query

# Crear la base de datos y las tablas
db = TinyDB('my_database.json')

class DistritoFiscal:
    def __init__(self, id, nombre):
        self.id = id
        self.nombre = nombre

    def guardar(self):
        db.insert({'id': self.id, 'nombre': self.nombre})

class Dependencia:
    def __init__(self, id, nombre, atributo1, id_distrito):
        self.id = id
        self.nombre = nombre
        self.atributo1 = atributo1
        self.id_distrito = id_distrito

    def guardar(self):
        db.insert({'id': self.id, 'nombre': self.nombre, 'atributo1': self.atributo1, 'id_distrito': self.id_distrito})

class Sede:
    def __init__(self, id, direccion, tipo_sede_id, dependencia_id):
        self.id = id
        self.direccion = direccion
        self.tipo_sede_id = tipo_sede_id
        self.dependencia_id = dependencia_id

    def guardar(self):
        db.insert({'id': self.id, 'direccion': self.direccion, 'tipo_sede_id': self.tipo_sede_id, 'dependencia_id': self.dependencia_id})

class TipoSede:
    def __init__(self, id, nombre):
        self.id = id
        self.nombre = nombre

    def guardar(self):
        db.insert({'id': self.id, 'nombre': self.nombre})

class Servicio:
    def __init__(self, id, continuidadServicio, sede_id, conectividad_id, fluidoElectrico_id):
        self.id = id
        self.continuidadServicio = continuidadServicio
        self.sede_id = sede_id
        self.conectividad_id = conectividad_id
        self.fluidoElectrico_id = fluidoElectrico_id

    def guardar(self):
        db.insert({'id': self.id, 'continuidadServicio': self.continuidadServicio, 'sede_id': self.sede_id, 'conectividad_id': self.conectividad_id, 'fluidoElectrico_id': self.fluidoElectrico_id})

class Conectividad:
    def __init__(self, id, servicio_id):
        self.id = id
        self.servicio_id = servicio_id

    def guardar(self):
        db.insert({'id': self.id, 'servicio_id': self.servicio_id})

class FluidoElectrico:
    def __init__(self, id, servicio_id):
        self.id = id
        self.servicio_id = servicio_id

    def guardar(self):
        db.insert({'id': self.id, 'servicio_id': self.servicio_id})

class Fiscalia:
    def __init__(self, id, categoria):
        self.id = id
        self.categoria = categoria

    def guardar(self):
        db.insert({'id': self.id, 'categoria': self.categoria})

class Despacho:
    def __init__(self, id, fiscalia_id):
        self.id = id
        self.fiscalia_id = fiscalia_id

    def guardar(self):
        db.insert({'id': self.id, 'fiscalia_id': self.fiscalia_id})

class TipoFiscalia:
    def __init__(self, id, nombre, fiscalia_id):
        self.id = id
        self.nombre = nombre
        self.fiscalia_id = fiscalia_id

    def guardar(self):
        db.insert({'id': self.id, 'nombre': self.nombre, 'fiscalia_id': self.fiscalia_id})

# Crear objetos y guardar en la base de datos
distrito = DistritoFiscal(id=1, nombre='Distrito 1')
distrito.guardar()

dependencia = Dependencia(id=1, nombre='Dependencia 1', atributo1='valor1', id_distrito=distrito.id)
dependencia.guardar()

sede = Sede(id=1, direccion='Direccion 1', tipo_sede_id=1, dependencia_id=dependencia.id)
sede.guardar()

tipo_sede = TipoSede(id=1, nombre='Tipo 1')
tipo_sede.guardar()

servicio = Servicio(id=1, continuidadServicio='Continuo', sede_id=sede.id, conectividad_id=1, fluidoElectrico_id=1)
servicio.guardar()

conectividad = Conectividad(id=1, servicio_id=servicio.id)
conectividad.guardar()

fluido_electrico = FluidoElectrico(id=1, servicio_id=servicio.id)
fluido_electrico.guardar()

fiscalia = Fiscalia(id=1, categoria='Categoria 1')
fiscalia.guardar()

despacho = Despacho(id=1, fiscalia_id=fiscalia.id)
despacho.guardar()

tipo_fiscalia = TipoFiscalia(id=1, nombre='Tipo 1', fiscalia_id=fiscalia.id)
tipo_fiscalia.guardar()
