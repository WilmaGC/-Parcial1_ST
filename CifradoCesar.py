
#esta es la funcion que nos permitira cifrar el mensaje, metemos el mensaje y la cantidad de espacios que se debera recorrer
def cifrar(mensaje, rotaciones):
    #declaramos la variable alfabeto minusculas y mayusculas
    alfabeto = "abcdefghijklmnopqrstuvwxyz"
    alfabeto_mayusculas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    #obtenemos la longitud del alfabeto
    longitud_alfabeto = len(alfabeto)
    #en esta variable guardaremos la variable codificada
    codificado = ""
    #con un for recorreremos el mensaje
    for letra in mensaje:
        #validamos si se metio una variable ñ para que lo tome encuenta
        if not letra.isalpha() or letra.lower() == 'ñ':
            codificado += letra
            continue
        #ordenamos la letra  
        valor_letra = ord(letra)
        # Suponemos que es minúscula, así que esto comienza en 97(a) y se usará el alfabeto en minúsculas
        alfabeto_a_usar = alfabeto        
        limite = 97  
        # Pero si es mayúscula, comienza en 65(A) y se usa en mayúsculas
        if letra.isupper():
            limite = 65
            #si es 65 actualizamos nuestra variable alfabeto usar con el alfaeto mayusculas
            alfabeto_a_usar = alfabeto_mayusculas
        # Rotamos la letra
        posicion = (valor_letra - limite + rotaciones) % longitud_alfabeto
        # Convertimos el entero resultante a letra y lo concatenamos
        codificado += alfabeto_a_usar[posicion]
    return codificado
#esta es la funcion que nos permitira descifrar el mensaje, metemos el mensaje y la cantidad de espacios que se debera recorrer
def descifrar(mensaje, rotaciones):
    #declaramos la variable alfabeto minusculas y mayusculas
    alfabeto = "abcdefghijklmnopqrstuvwxyz"
    alfabeto_mayusculas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    #obtenemos la longitud del alfabeto
    longitud_alfabeto = len(alfabeto)
    #en esta variable guardaremos la variable decodificada
    decodificado = ""
    for letra in mensaje:
        if not letra.isalpha() or letra.lower() == 'ñ':
            decodificado += letra
            continue
        valor_letra = ord(letra)
        # Suponemos que es minúscula, así que esto comienza en 97(a) y se usará el alfabeto en minúsculas
        alfabeto_a_usar = alfabeto
        limite = 97  # Pero si es mayúscula, comienza en 65(A) y se usa en mayúsculas
        if letra.isupper():
            limite = 65
            alfabeto_a_usar = alfabeto_mayusculas
        # Rotamos la letra, ahora hacia la izquierda
        posicion = (valor_letra - limite - rotaciones) % longitud_alfabeto
        # Convertimos el entero resultante a letra y lo concatenamos
        decodificado += alfabeto_a_usar[posicion]
    return decodificado
#definimos el main
def main():
    #en estas variables guardamos el mensaje y el numero que sera recorrido en el alfabeto 
    c = str(input('cadena a cifrar: '))
    n = int(input('clave numerica: '))
    #mandamos las variables a la funcion cifrar
    print(cifrar(c,n)) 
    #en estas variables guardamos el mensaje y el numero que sera restado en el recorrido en el alfabeto
    cc = str(input('cadena a descifrar: '))
    cn = int(input('clave numerica: '))
    #mandamos las variables a la funcion descifrar
    print(descifrar(cc,cn))
if __name__ == '__main__':
    main()