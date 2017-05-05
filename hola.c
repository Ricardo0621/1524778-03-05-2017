#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUMHILOS 100

//funHola: Funcion con el prototipo requerido para usar pthread

void *funcHola(void *nada) {
    sleep(3); //Duerme los hilos durante un tiempo
    pthread_t identificador; //Variable de tipo phread_t
    identificador = pthread_self(); //Toma el identificador del hilo actual
    printf("Hola! %ld\n", (long) identificador); //Imprime una cadena que contiene la palabra hola y el identificador del hilo 
    pthread_exit(NULL); //Termina el llamado al hilo de ejecucion
}

int main(int argc, char *argv[]) {
    int codigo = 1524778; //Mi codigo de estudiante
    int contenedor; //Variable auxiliar
    pthread_t hilos[NUMHILOS]; //Almacena todos los hilos que se van a crear
    for (int i = 0; i < NUMHILOS; i++) { //Itera desde cero hasta el numero total de hilos
        contenedor = pthread_create(&hilos[i], NULL, funcHola, NULL); //Crea tantos hilos con respecto al numero guardado en la variable NUMHILOS
        if (contenedor) {
            printf("ERROR: return code from pthread_create() is %d\n", contenedor);
            printf("Code %d= %s\n", contenedor, strerror(contenedor));
            exit(-1);
        }
    }
    printf("%d\n", codigo); //Imprime el codigo de estudiante
    printf("Creando %d hilos ...\n", NUMHILOS); //Imprime la cantidad de hilos
    pthread_exit(NULL); //Termina el llamado al hilo de ejecucion
}