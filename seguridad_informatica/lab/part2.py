def frecuencias(archivo):
    # Abrimos el archivo en modo lectura
    with open(archivo, 'r') as f:
        texto = f.read()

    # Creamos un diccionario para almacenar las frecuencias
    frecuencias = {}

    # Recorremos cada letra de la 'A' a la 'Z'
    for letra in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ':
        # Contamos la frecuencia de la letra en el texto y la almacenamos en el diccionario
        frecuencias[letra] = texto.count(letra)

    return frecuencias

# Usamos la función para calcular las frecuencias en el archivo "POEMA_PRE.TXT"
frecuencias = frecuencias("POEMA_PRE.TXT")

# Imprimimos las frecuencias
for letra, frecuencia in frecuencias.items():
    print(f'{letra}: {frecuencia}')

# Identificamos los cinco caracteres de mayor frecuencia
top_5 = sorted(frecuencias.items(), key=lambda x: x[1], reverse=True)[:5]

# Imprimimos los cinco caracteres de mayor frecuencia
print("\nLos cinco caracteres de mayor frecuencia son:")
for letra, frecuencia in top_5:
    print(f'{letra}: {frecuencia}')
