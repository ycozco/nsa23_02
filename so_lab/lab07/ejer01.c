#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4
#define NUM_ELEMENTS 5000

pthread_mutex_t mutex;
long long totalSum = 0;

// Estructura para pasar parámetros al hilo
typedef struct {
    int start; // índice de inicio en el array para el hilo
    int end;   // índice final en el array para el hilo
    int* array; // puntero al array
} ThreadData;

// Función que será ejecutada por cada hilo
void* sum_array(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    long long sum = 0;
    for (int i = data->start; i < data->end; ++i) {
        sum += data->array[i];
    }
    
    pthread_mutex_lock(&mutex); // Adquirir el mutex antes de actualizar totalSum
    totalSum += sum;
    pthread_mutex_unlock(&mutex); // Liberar el mutex después de actualizar totalSum

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

    pthread_mutex_init(&mutex, NULL); // Inicializar el mutex

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

    pthread_mutex_destroy(&mutex); // Destruir el mutex

    printf("Suma total: %lld\n", totalSum);

    return 0;
}
// file name : ejer01.c
// how to exec : gcc -pthread ejer01.c -o ejer01