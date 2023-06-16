import re

def sustitucion(texto):
    # Realizamos las sustituciones solicitadas
    texto = texto.replace('a', 'o')
    texto = texto.replace('h', 'i')
    texto = texto.replace('ñ', 'm')
    texto = texto.replace('k', 'l')
    texto = texto.replace('u', 'v')
    texto = texto.replace('w', 'v')
    texto = texto.replace('z', 'y')
    texto = texto.replace('x', 'r')
    # same replace for uppercase letters
    texto = texto.replace('A', 'O')
    texto = texto.replace('H', 'I')
    texto = texto.replace('Ñ', 'M')
    texto = texto.replace('K', 'L')
    texto = texto.replace('U', 'V')
    texto = texto.replace('W', 'V')
    texto = texto.replace('Z', 'Y')
    texto = texto.replace('X', 'R')
    return texto

def del_tildes(texto):
    # Eliminamos las tildes
    texto = texto.replace('á', 'a')
    texto = texto.replace('é', 'e')
    texto = texto.replace('í', 'i')
    texto = texto.replace('ó', 'o')
    texto = texto.replace('ú', 'u')

    # same replace for uppercase letters
    texto = texto.replace('Á', 'A')
    texto = texto.replace('É', 'E')
    texto = texto.replace('Í', 'I')
    texto = texto.replace('Ó', 'O')
    texto = texto.replace('Ú', 'U')
    return texto

def conver_upper(texto):
    # Convertimos el texto a mayúsculas
    return texto.upper()

def del_spaces_punt(texto):
    # Eliminamos los espacios en blanco y los signos de puntuación
    texto = re.sub(r'\s+', '', texto)
    texto = re.sub(r'[^\w\s]', '', texto)
    return texto

# Aplicamos las funciones al texto
texto = "Mi corazón oprimido Siente junto a la alborada El dolor de sus amores Y el sueño de las distancia. La luz de la aurora lleva Semilleros de nostalgias Y la tristeza sin los ojos De la médula del alma La gran tumba de la noche Su negro velo levanta Para ocultar con el día La inmensa cumbre estrellada. ¡Qué haré yo sobre estos campos Cogiendo niños y ramas Rodeado de la aurora Y llena de noche el ama! ¡Qué haré si tienes tus ojos Muertos a las luces claras Y no ha de sentir mi carne El calor de tus miradas! ¿Por qué te perdí por siempre En aquella tarde clara? Hoy mi pecho está reseco Como una estrella apagada."

# Guardamos el resultado en un archivo
with open("POEMA_PRE.TXT", "w") as f:
    f.write(texto)
