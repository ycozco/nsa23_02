import re

def kasiski(archivo):
    # Abrimos el archivo en modo lectura
    with open(archivo, 'r') as f:
        texto = f.read()

    # Creamos un diccionario para almacenar los trigramas y sus distancias
    trigramas = {}

    # Recorremos el texto buscando trigramas
    for i in range(len(texto) - 2):
        trigrama = texto[i:i+3]
        if re.match(r'[A-Z]{3}', trigrama):
            if trigrama not in trigramas:
                trigramas[trigrama] = []
            else:
                ultima_ocurrencia = trigramas[trigrama][-1] if trigramas[trigrama] else 0
                trigramas[trigrama].append(i - ultima_ocurrencia)

    # Abrimos el archivo "trigrama.txt" en modo escritura
    with open("trigrama.txt", "w") as f:
        # Escribimos los trigramas y sus distancias en el archivo
        for trigrama, distancias in trigramas.items():
            f.write(f'{trigrama}: {distancias}\n')

    return trigramas

# Usamos la función para calcular los trigramas y sus distancias en el archivo "POEMA_PRE.TXT"
trigramas = kasiski("POEMA_PRE.TXT")

# Imprimimos los trigramas y sus distancias
for trigrama, distancias in trigramas.items():
    print(f'{trigrama}: {distancias}')
