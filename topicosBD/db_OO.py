from peewee import *

db = SqliteDatabase('my_database.db')

class DistritoFiscal(Model):
    id = IntegerField(primary_key=True)
    nombre = CharField()

class Dependencia(Model):
    id = IntegerField(primary_key=True)
    nombre = CharField()
    atributo1 = CharField()
    id_distrito = ForeignKeyField(DistritoFiscal, backref='dependencias')

class Sede(Model):
    id = IntegerField(primary_key=True)
    direccion = CharField()
    tipo_sede_id = IntegerField()
    dependencia_id = ForeignKeyField(Dependencia, backref='sedes')

class TipoSede(Model):
    id = IntegerField(primary_key=True)
    nombre = CharField()

class Servicio(Model):
    id = IntegerField(primary_key=True)
    continuidadServicio = CharField()
    sede_id = ForeignKeyField(Sede, backref='servicios')
    conectividad_id = IntegerField()
    fluidoElectrico_id = IntegerField()

class Conectividad(Model):
    id = IntegerField(primary_key=True)
    servicio_id = ForeignKeyField(Servicio, backref='conectividades')

class FluidoElectrico(Model):
    id = IntegerField(primary_key=True)
    servicio_id = ForeignKeyField(Servicio, backref='fluido_electricos')

class Fiscalia(Model):
    id = IntegerField(primary_key=True)
    categoria = CharField()

class Despacho(Model):
    id = IntegerField(primary_key=True)
    fiscalia_id = ForeignKeyField(Fiscalia, backref='despachos')

class TipoFiscalia(Model):
    id = IntegerField(primary_key=True)
    nombre = CharField()
    fiscalia_id = ForeignKeyField(Fiscalia, backref='tipos_fiscalia')

db.connect()
db.create_tables([DistritoFiscal, Dependencia, Sede, TipoSede, Servicio, Conectividad, FluidoElectrico, Fiscalia, Despacho, TipoFiscalia])

distrito = DistritoFiscal.create(id=1, nombre='Distrito 1')
dependencia = Dependencia.create(id=1, nombre='Dependencia 1', atributo1='valor1', id_distrito=distrito)
sede = Sede.create(id=1, direccion='Direccion 1', tipo_sede_id=1, dependencia_id=dependencia)
tipo_sede = TipoSede.create(id=1, nombre='Tipo 1')
servicio = Servicio.create(id=1, continuidadServicio='Continuo', sede_id=sede, conectividad_id=1, fluidoElectrico_id=1)
conectividad = Conectividad.create(id=1, servicio_id=servicio)
fluido_electrico = FluidoElectrico.create(id=1, servicio_id=servicio)
fiscalia = Fiscalia.create(id=1, categoria='Categoria 1')
despacho = Despacho.create(id=1, fiscalia_id=fiscalia)
tipo_fiscalia = TipoFiscalia.create(id=1, nombre='Tipo 1', fiscalia_id=fiscalia)