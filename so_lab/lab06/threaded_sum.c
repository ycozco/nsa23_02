#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4
#define NUM_ELEMENTS 5000

// Estructura para pasar parámetros al hilo
typedef struct {
    int start; // índice de inicio en el array para el hilo
    int end;   // índice final en el array para el hilo
    int* array; // puntero al array
    long long sum; // suma de elementos procesados por el hilo
} ThreadData;

// Función que será ejecutada por cada hilo
void* sum_array(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    data->sum = 0;
    for (int i = data->start; i < data->end; ++i) {
        data->sum += data->array[i];
    }
    return NULL;
}

int main() {
    srand((unsigned int) time(NULL)); // Semilla para números aleatorios

    // Crear y llenar el array con números aleatorios
    int array[NUM_ELEMENTS];
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        array[i] = rand() % 100; // Números aleatorios entre 0 y 99
    }

    pthread_t threads[NUM_THREADS];
    ThreadData threadData[NUM_THREADS];

    // Crear los hilos
    for (int i = 0; i < NUM_THREADS; ++i) {
        threadData[i].start = i * (NUM_ELEMENTS / NUM_THREADS);
        threadData[i].end = (i + 1) * (NUM_ELEMENTS / NUM_THREADS);
        threadData[i].array = array;
        pthread_create(&threads[i], NULL, sum_array, &threadData[i]);
    }

    // Esperar a que los hilos terminen
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Sumar los resultados de cada hilo
    long long totalSum = 0;
    for (int i = 0; i < NUM_THREADS; ++i) {
        totalSum += threadData[i].sum;
    }

    printf("Suma total: %lld\n", totalSum);

    return 0;
}

// Exec code:
// gcc -o threaded_sum threaded_sum.c -pthread
// ./threaded_sum
