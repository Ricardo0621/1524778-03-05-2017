#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define MAXRECT 1000000
#define MAXTHREAD 10
#define BASE 0.0
#define LIMIT 1.0

double length = LIMIT - BASE; // Longitud en el eje X.
double numRectxThread = (double) (MAXRECT / MAXTHREAD); // Cuantos rectangulos por hilo.
double base_length = 0; // Variable que tiene el ancho de cada rectangulo.
double sumTotal = 0; // Variable que tendra la suma total.
double partialSums[MAXTHREAD]; // Variable que tiene la suma parcial de cada hilo.

double function(double x) {// Funcion a la que se le calculara la integral.
    return (x * x);
}

void *calcular(void *arg) {
    int id = (int) arg;    // id es el identificador del hilo para reconocer que porcion le corresponde calcular.
    partialSums[id] = 0;    // Inicializar la variable de la suma de las areas de cada hilo.
    double loslimit = id * base_length * numRectxThread ;    // Loslimit es la posicion inicial del hilo.
    for (int i = 0; i < numRectxThread; i++) {
        partialSums[id] += (base_length * function(loslimit));
        loslimit += base_length;
    }
    printf("Hilo %d -> Suma parcial %lf.\n", id, partialSums[id]);
    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    pthread_t threads[MAXTHREAD];
    int taskids[MAXTHREAD];
    int contenedor = 0;
    base_length = (double) (length / MAXRECT);
    //printf("Base length: %lf y numRectxThread: %lf\n", base_length, numRectxThread);
    for (int i = 0; i < MAXTHREAD; i++) {    // Creacion de los hilos que calcularan el area bajo la curva.
        taskids[i] = i;
        contenedor = pthread_create(&threads[i], NULL, calcular, (void *) taskids[i]);
        if (contenedor) {
            printf("!Error en la creacion de los hilos!\n");
            exit(-1);
        }
    }
    for (int j = 0; j < MAXTHREAD; j++) {// Ciclo donde se espera el resultado de cada hilo.
        pthread_join(threads[j], NULL);
        sumTotal += partialSums[j];
    }
    printf("Suma total: %lf\n", sumTotal);
    pthread_exit(NULL);
}
