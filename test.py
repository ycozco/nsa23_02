def calcular_velocidad(velocidad_inicial, aceleracion, tiempo):
    if aceleracion != 0 and tiempo != 0:
        velocidad = velocidad_inicial + (aceleracion * tiempo)
        return velocidad
    else:
        if aceleracion == 0:
            print("La aceleración no puede ser cero. No se puede calcular la velocidad.")
        if tiempo == 0:
            print("El tiempo no puede ser cero. No se puede calcular la velocidad.")

# Ejemplo de uso
velocidad_resultado = calcular_velocidad(10, 2, 5)
if velocidad_resultado is not None:
    print("La velocidad es:", velocidad_resultado)
