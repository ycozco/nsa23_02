import numpy as np

def crear_matriz_polybios(clave, n):
    # Creamos un conjunto para almacenar los caracteres únicos de la clave
    caracteres_unicos = set(clave.upper())

    # Creamos el alfabeto sin la letra 'J', ya que se suele combinar con la 'I'
    alfabeto = "ABCDEFGHIKLMNOPQRSTUVWXYZ"

    # Eliminamos los caracteres de la clave del alfabeto
    for letra in caracteres_unicos:
        alfabeto = alfabeto.replace(letra, "")

    # Creamos la matriz de Polybios de nxn
    matriz_polybios = np.zeros((n, n), dtype=str)

    # Rellenamos la matriz con la clave y el alfabeto restante
    i = 0
    for letra in clave.upper() + alfabeto:
        if i >= n * n:
            break
        matriz_polybios[i // n][i % n] = letra
        i += 1

    return matriz_polybios

def cifrar_polybios(texto, clave, n):
    # Creamos la matriz de Polybios con la clave proporcionada y el tamaño n
    matriz_polybios = crear_matriz_polybios(clave, n)

    # Creamos un diccionario para mapear las letras a sus coordenadas en la matriz
    coordenadas = {}
    for i in range(n):
        for j in range(n):
            coordenadas[matriz_polybios[i][j]] = (i + 1, j + 1)

    # Ciframos el texto utilizando la matriz de Polybios
    texto_cifrado = ""
    for letra in texto.upper():
        if letra == " ":
            texto_cifrado += "00"  # Usamos "00" para representar un espacio
        elif letra in coordenadas:
            fila, columna = coordenadas[letra]
            texto_cifrado += f"{fila}{columna}"

    return texto_cifrado

def descifrar_polybios(texto_cifrado, clave, n):
    # Creamos la matriz de Polybios con la clave proporcionada y el tamaño n
    matriz_polybios = crear_matriz_polybios(clave, n)

    # Dividimos el texto cifrado en pares de números
    pares_numeros = [texto_cifrado[i:i+2] for i in range(0, len(texto_cifrado), 2)]
    # Desciframos el texto cifrado utilizando la matriz de Polybios
    texto_descifrado = ""
    for par in pares_numeros:
        fila = int(par[0]) - 1  # Obtenemos la fila correspondiente al primer número del par
        columna = int(par[1]) - 1  # Obtenemos la columna correspondiente al segundo número del par
        if fila == -1 and columna == -1:
            texto_descifrado += " "  # Agregamos un espacio si encontramos "00"
        else:
            texto_descifrado += matriz_polybios[fila][columna]  # Agregamos el carácter correspondiente en la matriz de Polybios al texto descifrado

    return texto_descifrado  # Devolvemos el texto descifrado

clave = input("Ingresa la clave: ")
n = int(input("Ingresa el valor de n: "))
texto = input("Ingresa el texto a cifrar: ")
texto_cifrado = cifrar_polybios(texto, clave, n)
print("Texto cifrado:", texto_cifrado)
#con valor ya cifrado
cip_text = "1127411127"
texto_descifrado_prueba = descifrar_polybios(cip_text, clave, n)
print("Texto descifrado:", texto_descifrado_prueba)

#test online https://md5decrypt.net/en/Polybius-square/
