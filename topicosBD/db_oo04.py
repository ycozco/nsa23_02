from persistent import Persistent
from ZODB import DB, FileStorage
import transaction

# Crear la base de datos y obtener la raíz del objeto
storage = FileStorage.FileStorage('my_database.fs')
db = DB(storage)
connection = db.open()
root = connection.root()

# Definir clases para los objetos persistentes
class DistritoFiscal(Persistent):
    def __init__(self, id, nombre):
        self.id = id
        self.nombre = nombre
        self.dependencias = []

class Dependencia(Persistent):
    def __init__(self, id, nombre, atributo1, id_distrito):
        self.id = id
        self.nombre = nombre
        self.atributo1 = atributo1
        self.id_distrito = id_distrito
        self.sedes = []

class Sede(Persistent):
    def __init__(self, id, direccion, tipo_sede_id, dependencia_id):
        self.id = id
        self.direccion = direccion
        self.tipo_sede_id = tipo_sede_id
        self.dependencia_id = dependencia_id
        self.servicios = []

class TipoSede(Persistent):
    def __init__(self, id, nombre):
        self.id = id
        self.nombre = nombre

class Servicio(Persistent):
    def __init__(self, id, continuidad_servicio, sede_id, conectividad_id, fluido_electrico_id):
        self.id = id
        self.continuidad_servicio = continuidad_servicio
        self.sede_id = sede_id
        self.conectividad_id = conectividad_id
        self.fluido_electrico_id = fluido_electrico_id

class Conectividad(Persistent):
    def __init__(self, id, servicio_id):
        self.id = id
        self.servicio_id = servicio_id

class FluidoElectrico(Persistent):
    def __init__(self, id, servicio_id):
        self.id = id
        self.servicio_id = servicio_id

class Fiscalia(Persistent):
    def __init__(self, id, categoria):
        self.id = id
        self.categoria = categoria
        self.despachos = []
        self.tipos_fiscalia = []


class Despacho(Persistent):
    def __init__(self, id, fiscalia_id):
        self.id = id
        self.fiscalia_id = fiscalia_id

class TipoFiscalia(Persistent):
    def __init__(self, id, nombre, fiscalia_id):
        self.id = id
        self.nombre = nombre
        self.fiscalia_id = fiscalia_id

# Agregar objetos a la base de datos
distrito = DistritoFiscal(id=1, nombre='Distrito 1')
dependencia = Dependencia(id=1, nombre='Dependencia 1', atributo1='valor1', id_distrito=distrito.id)
sede = Sede(id=1, direccion='Direccion 1', tipo_sede_id=1, dependencia_id=dependencia.id)
tipo_sede = TipoSede(id=1, nombre='Tipo 1')
servicio = Servicio(id=1, continuidad_servicio='Continuo', sede_id=sede.id, conectividad_id=1, fluido_electrico_id=1)
conectividad = Conectividad(id=1, servicio_id=servicio.id)
fluido_electrico = FluidoElectrico(id=1, servicio_id=servicio.id)
fiscalia = Fiscalia(id=1, categoria='Categoria 1')
despacho = Despacho(id=1, fiscalia_id=fiscalia.id)
tipo_fiscalia = TipoFiscalia(id=1, nombre='Tipo 1', fiscalia_id=fiscalia.id)

sede.servicios.append(servicio)
fiscalia.despachos.append(despacho)
fiscalia.tipos_fiscalia.append(tipo_fiscalia)

dependencia.sedes.append(sede)
distrito.dependencias.append(dependencia)

root.distritos = [distrito]
root.fiscalias = [fiscalia]

# Confirmar los cambios en la base de datos
transaction.commit()

# Cerrar la conexión a la base de datos
connection.close()
db.close()
