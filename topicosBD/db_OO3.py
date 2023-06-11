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
    def __init__(self, id, nombre, atributo1):
        self.id = id
        self.nombre = nombre
        self.atributo1 = atributo1
        self.id_distrito = None

class Sede(Persistent):
    def __init__(self, id, direccion, tipo_sede_id, dependencia_id):
        self.id = id
        self.direccion = direccion
        self.tipo_sede_id = tipo_sede_id
        self.dependencia_id = dependencia_id

# Agregar objetos a la base de datos
distrito = DistritoFiscal(id=1, nombre='Distrito 1')
dependencia = Dependencia(id=1, nombre='Dependencia 1', atributo1='valor1')
sede = Sede(id=1, direccion='Direccion 1', tipo_sede_id=1, dependencia_id=1)

dependencia.id_distrito = distrito.id
distrito.dependencias.append(dependencia)

root.distritos = [distrito]

# Confirmar los cambios en la base de datos
transaction.commit()

# Cerrar la conexión a la base de datos
connection.close()
db.close()
