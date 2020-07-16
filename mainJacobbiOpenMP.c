#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
# include <cmath>
# include <cstdlib>
# include <ctime>
# include <iomanip>
# include <iostream>
# include <omp.h>
//haremos el uso de namespace para los espacios
using namespace std;
//declaramos una variable entera para la dimension de la matriz
int dim;
//declaramos las funciones norma para normalizar el vector o la matriz y suma para sumar matrices
float norma(float vector1[],float vector2[]);
float suma_jacobi(float Matriz[], float vector[], int componente);
//declaramos esta funcion que nos devuelve el tiempo exacto
void timestamp ( );
//empezamos a realizar el ejercicio
int main(){
    //declaramos las variables para las matrices y el numero de iteraciones que necesitaremos para calcular las ecuaciones
    int i,j,iteraciones=0;
    //declaramos dos variables float para almacenar el epsilon y el error permitido
    float error,epsilon;
    printf("\n METODO DE JACOBI DE RESOLUCION DE SISTEMAS Ax=b \n");
    //leemos la dimesion de la matriz
    printf("Dimension de la matriz A: ");
    scanf("%d",&dim);
    //y almacenamos esta diemcion en los diferentes vectores y matrices que definimos
    float A[dim][dim],b[dim],x[dim],x_prev[dim],aux[dim];
    //empezamos a llenar la matriz
    printf("\n Elementos de la matriz A: \n");
    //usamos el pragma omp para el for para que nos permita que las iteraciones se ejecuten en paralelo por hilos que ya existen
    //en este caso fue la mejor directiva que pude usar ya que los otros al tratar de ser funciones de lectura de teclado con la
    //paralelizacion se confunde
    #pragma omp for
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++){
          printf("A(%d,%d)=",i,j);
          scanf("%f",&A[i][j]);
       }
    }
    //ahora almacenamos los valores delvector b
    printf("\n Elementos del vector b: \n");
    //y con ete pragma pedimos que se llene el vector utilizando la cantidad de procesadores que existen
    #pragma omp for
    for(i=0;i<dim;i++){
        printf("b(%d)=",i);
        scanf("%f",&b[i]);
    }
    //introducimos el error permitido para el calculo de las ecuaciones
    printf("\n Error permitido: \n");
    printf("E=",i);
    scanf("%f",&epsilon);
    error=epsilon+1;

    timestamp ( );
    //cominezo algoritmo de Jacobi
    //Error se mide como la norma del vector diferenceia entre la iteracion i e i+1
    printf("\n Valor inicial de la iteracion: \n");
    //tra vez usamos el pragma para que el procedimiento sea as rapido
    #pragma omp for
    for(i=0;i<dim;i++){
        printf("x0(%d)=",i);
        scanf("%f",&x_prev[i]);
    }
    while (error>epsilon){
        //la directiva parallel crea un grupo de threads que se une al principal en este caso se alicara al primer for
        #pragma omp parallel for default(shared)
        for(i=0;i<dim;i++){
          //ahora alicamos para el segundo for otro parallel diferente para que el programa no se confunda en los calculos
          #pragma omp parallel for
          for(j=0;j<dim;j++){
                aux[j]=A[i][j];
                x[i]=(1/A[i][i])*(b[i]-suma_jacobi(aux,x_prev,i));
            }
        }
        //igualamos la variable error que sera el resultado de normalizar el vector
        error=norma(x,x_prev);
        //imprimimos la cantidad de iteraciones que usamos para encontrar los resultados
        printf("\n\n Iteracion %d: \n",iteraciones);
        //otra vez aplicamos el pragma para usar las funciones de openmp en el for
        #pragma omp for
        for(i=0;i<dim;i++){
            x_prev[i]=x[i];
            printf("X(%d)=%f \n",i,x[i]);
        }
        //sumamos una iteracion mas
        iteraciones++;
    //si los errores llegan a 10 existe un error, puede que la ecuacion no converga
        if (iteraciones==10){
            error=epsilon-1;
        }
    }
    //ahora mostramos la solucion del sistema
    printf("Solucion del sistema\n");
    //mostramos la cantidad de oteraciones
    printf("Numero de iteraciones: %d \n", iteraciones);
    //imprimimos las soluciones
    #pragma omp for
    for(i=0;i<dim;i++){
        printf("x(%d)=%f\n",i,x[i]);
    }
    //y tambien impreimimos el tiempopara veer cuanto demoro en hacer los calculos
    timestamp ( );
    return 1;
}
//este es la funcion para normalizar los vectores
float norma(float vector1[],float vector2[]){
    float aux=0;
    int i;
    //usamos esta directiva porque nos ayudara a decirle al for que use los hilos
    //de procesadores que tenemos en este dispositivo para hacerlo mas rapido
    //con la reduction(+:aux) repartiremos el número total de iteraciones del bucle entre los distintos hilos
    #pragma omp parallel for reduction (+:aux)
    for(i=0;i<dim;i++){
        aux=aux+(vector1[i]-vector2[i])*(vector1[i]-vector2[i]);
    }
    return aux;
}
//esta esla funcion para sumar los vectores
float suma_jacobi(float Matriz[], float vector[], int componente){
    float aux=0;
    int i;
    // y usamos esta directiva para repartir el procedimiento en los hilos que tenemos
    #pragma omp parallel for reduction (+:aux)
    for(i=0;i<dim;i++){
        if (componente!=i){
            aux=aux+Matriz[i]*vector[i];
        }
    }
    return aux;
}
//esta es la funcion que nos permitira devolver la hora y fecha esto nos ayudara a ver cuanto tiempo tardo en ejecutarse el proceso
void timestamp ( ){
    //definimos el tamano
    # define TIME_SIZE 40
    //declaramos la variable
    static char time_buffer[TIME_SIZE];
    const struct std::tm *tm_ptr;
    std::time_t now;
    now = std::time ( NULL );
    tm_ptr = std::localtime ( &now );
    //mostramos los datos
    std::strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm_ptr );
    std::cout << time_buffer << "\n";
    return;
    # undef TIME_SIZE
}
