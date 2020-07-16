#include <omp.h>
#include <stdio.h>
#include<conio.h>
#include<iostream>
#include<string.h>
#include<windows.h>
#include<Math.h>
//primero vamos a definir una longitud maxima para poder escribir la frase que queramos pero hasta la longitud definida
#define LONGITUD 5000

//tambien vamos a definir un char donde guardaremos todo el alfabeto en minusculas
char alf[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

int main()
{
    //vamos a obtener el numero de hilos o procesadores para que nos ayude a paralelizar mas adelante
    int p;
    p =omp_get_num_procs();
	omp_set_num_threads(p);
//definimos un vector char del tamano de la longitud definida
    char m[LONGITUD];
    printf("Ingrese mensaje a cifrar: ");
    //leemos la frase introducida por teclado
	fgets(m,LONGITUD,stdin);
	//eliminamos el salto que esta por defecto
	m[strcspn(m, "\r\n")] = 0;


//ahora establecemos el #pragma para decirle al compilador la forma de compilar, en este caso usara el compilador de omp
//con el parallel vamos a decirle al for que use los hilos de procesadores que tenemos en este dispositivo para hacerlo mas rapido
//con la ction(+:m) repartiremos el número total de iteraciones del bucle entre los distintos hilos, por ejemplo, si hay 100
//iteraciones y 4 hilos, cada uno de ellos compruebe 25 iteraciones, lo que hace la clausula reduction las cuatro variables
//que estan en el char m
    #pragma omp parallel for reduction(+:m)
    //con este procedimeinto en caso de meter por teclado mayusculas lo convertimos a minuculas
	for (int i = 0; i<strlen(m); i++){
		m[i] = tolower(m[i]);
	}
//para este procedimiento usaremos el #pragma parallel for para paralelizar el procedimiento
	#pragma omp parallel for
	for(int i=0; i<strlen(m);i++){
		if(m[i]!= 32){
			for(int j=0;j<strlen(alf);j++){
				if(m[i]==alf[j]){
					int aux=(j+3)%26;
					m[i]=alf[aux];
					break;
				}
			}
		}
	}
	printf("El mensaje cifrado es: %s \n", m);
//definimos un vector char del tamano de la longitud definida para decifrar el codigo
    char m1[LONGITUD];
	printf("Ingrese mensaje a descifrar: ");
	fgets(m1,LONGITUD,stdin);
	m1[strcspn(m1, "\r\n")] = 0;
//usamos el mismo procedimiento, para convertir en minuscula la frase ingresada por teclado
	#pragma omp parallel for reduction(+:m)
	for (int i = 0; i<strlen(m); i++){
		m1[i] = tolower(m1[i]);
	}
//para este procedimiento usaremos el #pragma parallel for para paralelizar el procedimiento
	#pragma parallel for
	for(int i=0; i<strlen(m1);i++){
		if(m1[i]!= 32){
			for(int j=0;j<strlen(alf);j++){
				if(m1[i]==alf[j]){
					int aux;
					if((j-3)<0){
						aux=26+(j-3);
					}
					else{
						aux=(j-3)%26;
					}
					m1[i]=alf[aux];
					break;
				}
			}
		}
	}
	printf("El mensaje descifrado es: %s \n", m1);

	return 0;
}



