def preprocesar_insertar(archivo):
    # Abrimos el archivo en modo lectura
    with open(archivo, 'r') as f:
        texto = f.read()

    # Insertamos 'AQP' cada 20 caracteres
    texto = ''.join(texto[i:i+20] + 'AQP' for i in range(0, len(texto), 20))

    # Comprobamos si la longitud del texto es múltiplo de 4
    while len(texto) % 4 != 0:
        # Si no lo es, añadimos 'X' al final del texto
        texto += 'X'

    return texto

# Usamos la función para preprocesar el archivo "POEMA_PRE.TXT"
texto = preprocesar_insertar("POEMA_PRE.TXT")

# Imprimimos el texto preprocesado
print(texto)
