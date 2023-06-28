import random

def generar_conjunto_llaves(longitud_bit):
    """Genera un conjunto de llaves pública y privada."""
    # Genera la llave privada
    llave_privada = [random.randint(1, longitud_bit)] # Inicia la llave privada con un número aleatorio
    total = llave_privada[0] # Inicia el total con el primer número de la llave privada
    for _ in range(1, longitud_bit):
        # Añade un número aleatorio a la llave privada que sea mayor que el total actual
        llave_privada.append(random.randint(total+1, 2*total))
        total += llave_privada[-1] # Actualiza el total

    # Genera la llave pública
    q = random.randint(total+1, 2*total) # Genera un número aleatorio q que es mayor que el total
    r = encontrar_r(q) # Encuentra un número r que sea coprimo con q
    # Genera la llave pública como una lista de números que son el producto de r y la llave privada módulo q
    llave_publica = [(r*i)%q for i in llave_privada]

    return llave_publica, llave_privada, r, q

def encontrar_r(q):
    """Encuentra un r tal que r y q sean coprimos."""
    while True:
        r = random.randint(2, q-1) # Genera un número aleatorio r
        if son_coprimos(r, q): # Si r y q son coprimos, devuelve r
            return r

def son_coprimos(a, b):
    """Comprueba si a y b son coprimos."""
    while b != 0:
        a, b = b, a % b # Realiza el algoritmo de Euclides para encontrar el máximo común divisor
    return a == 1 # Si el máximo común divisor es 1, a y b son coprimos
def cifrar(llave_publica, texto_plano):
    """Cifra el texto plano con la llave pública."""
    texto_cifrado = []
    for caracter in texto_plano:
        caracter_binario = format(ord(caracter), '08b') # Convierte el carácter a binario con 8 digitos
        # Suma los elementos de la llave pública correspondientes a los bits 1 del carácter
        caracter_cifrado = sum([llave_publica[i] for i in range(8) if caracter_binario[i] == '1'])
        texto_cifrado.append(caracter_cifrado) # Añade el carácter cifrado al texto cifrado
    return texto_cifrado

def descifrar(llave_privada, r, q, texto_cifrado):
    """Descifra el texto cifrado con la llave privada."""
    texto_descifrado = ''
    s = inverso_modular(r, q) # Calcula el inverso modular de r módulo q
    for caracter_cifrado in texto_cifrado:
        caracter_binario = ''
        caracter_decodificado = (caracter_cifrado * s) % q # Multiplica el carácter cifrado por s módulo q
        for llave in reversed(llave_privada):
            # Si la llave es menor o igual que elcarácter decodificado, resta la llave del carácter y añade un 1 al carácter binario
            if llave <= caracter_decodificado:
                caracter_decodificado -= llave
                caracter_binario = '1' + caracter_binario
            else:
                caracter_binario = '0' + caracter_binario # Si la llave es mayor que el carácter decodificado, añade un 0 al carácter binario
        texto_descifrado += chr(int(caracter_binario, 2)) # Convierte el carácter binario a un carácter y lo añade al texto descifrado
    return texto_descifrado

def inverso_modular(a, m):
    """Calcula el inverso modular de a mod m."""
    g, x, _ = maximo_comun_divisor_extendido(a, m)
    if g != 1:
        raise Exception('No existe el inverso modular')
    return x % m

def maximo_comun_divisor_extendido(a, b):
    """Calcula el máximo común divisor extendido de a y b."""
    if a == 0:
        return b, 0, 1
    else:
        g, x, y = maximo_comun_divisor_extendido(b % a, a)
        return g, y - (b // a) * x, x

# Prueba del algoritmo
llave_publica, llave_privada, r, q = generar_conjunto_llaves(8)
texto_plano = ' ¡Árbol frondoso, ñandú velocísimo! ¿Qué viento ruge en tu manto?'
texto_cifrado = cifrar(llave_publica, texto_plano)
texto_descifrado = descifrar(llave_privada, r, q, texto_cifrado)
print('Texto plano:', texto_plano)
print('Texto cifrado:', texto_cifrado)
print('Texto descifrado:', texto_descifrado)
