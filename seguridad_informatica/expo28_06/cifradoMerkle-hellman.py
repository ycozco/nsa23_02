import random

def generate_keyset(bit_length):
    """Genera un conjunto de llaves pública y privada."""
    # Genera la llave privada
    private_key = [random.randint(1, bit_length)] # Inicia la llave privada con un número aleatorio
    total = private_key[0] # Inicia el total con el primer número de la llave privada
    for _ in range(1, bit_length):
        # Añade un número aleatorio a la llave privada que sea mayor que el total actual
        private_key.append(random.randint(total+1, 2*total))
        total += private_key[-1] # Actualiza el total

    # Genera la llave pública
    q = random.randint(total+1, 2*total) # Genera un número aleatorio q que es mayor que el total
    r = find_r(q) # Encuentra un número r que sea coprimo con q
    # Genera la llave pública como una lista de números que son el producto de r y la llave privada módulo q
    public_key = [(r*i)%q for i in private_key]

    return public_key, private_key, r, q

def find_r(q):
    """Encuentra un r tal que r y q sean coprimos."""
    while True:
        r = random.randint(2, q-1) # Genera un número aleatorio r
        if are_coprime(r, q): # Si r y q son coprimos, devuelve r
            return r

def are_coprime(a, b):
    """Comprueba si a y b son coprimos."""
    while b != 0:
        a, b = b, a % b # Realiza el algoritmo de Euclides para encontrar el máximo común divisor
    return a == 1 # Si el máximo común divisor es 1, a y b son coprimos

def encrypt(public_key, plaintext):
    """Cifra el texto plano con la llave pública."""
    ciphertext = []
    for char in plaintext:
        bin_char = format(ord(char), '08b') # Convierte el carácter a binario
        # Suma los elementos de la llave pública correspondientes a los bits 1 del carácter
        cipher_char = sum([public_key[i] for i in range(8) if bin_char[i] == '1'])
        ciphertext.append(cipher_char) # Añade el carácter cifrado al texto cifrado
    return ciphertext

def decrypt(private_key, r, q, ciphertext):
    """Descifra el texto cifrado con la llave privada."""
    plaintext = ''
    s = mod_inverse(r, q) # Calcula el inverso modular de r módulo q
    for cipher_char in ciphertext:
        bin_char = ''
        dec_char = (cipher_char * s) % q # Multiplica el carácter cifrado por s módulo q
        for key in reversed(private_key):
            # Si la llave es menor o igual que el carácter decodificado, resta la llave del carácter y añade un 1 al carácter binario
            if key <= dec_char:
                dec_char -= key
                bin_char = '1' + bin_char
            else:
                bin_char = '0' + bin_char # Si no, añade un 0 al carácter binario
        plaintext +=chr(int(bin_char, 2)) # Convierte el carácter binario a decimal y luego a carácter, y lo añade al texto plano
    return plaintext

def mod_inverse(a, m):
    """Calcula el inverso modular de a mod m."""
    g, x, _ = extended_gcd(a, m) # Calcula el máximo común divisor extendido de a y m
    if g != 1:
        raise Exception('No existe el inverso modular') # Si el máximo común divisor no es 1, no existe el inverso modular
    return x % m # Devuelve el inverso modular de a módulo m

def extended_gcd(a, b):
    """Calcula el máximo común divisor extendido de a y b."""
    if a == 0:
        return b, 0, 1 # Si a es 0, el máximo común divisor es b, y los coeficientes de Bézout son 0 y 1
    else:
        g, x, y = extended_gcd(b % a, a) # Calcula el máximo común divisor extendido de (b módulo a ) y a
        return g, y - (b // a) * x, x # Devuelve el máximo común divisor y los coeficientes de Bézout

# Prueba del algoritmo
public_key, private_key, r, q = generate_keyset(8) # Genera un conjunto de llaves
plaintext = ' ¡Árbol frondoso, ñandú velocísimo! ¿Qué viento ruge en tu manto?' # Texto plano
ciphertext = encrypt(public_key, plaintext) # Cifra el texto plano
decrypted = decrypt(private_key, r, q, ciphertext) # Descifra el texto cifrado
print('Texto plano:', plaintext)
print('Texto cifrado:', ciphertext)
print('Texto descifrado:', decrypted)
