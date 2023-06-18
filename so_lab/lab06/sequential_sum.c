#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_ELEMENTS 5000

// Variable para decidir cuántos hilos se utilizarán
// 1 para un solo hilo, >1 para múltiples hilos
int num_threads = 1;

typedef struct {
    int start;
    int end;
    int* array;
    long long sum;
} ThreadData;

void* sum_array(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    data->sum = 0;
    for (int i = data->start; i < data->end; ++i) {
        data->sum += data->array[i];
    }
    return NULL;
}

int main() {
    srand((unsigned int) time(NULL));

    int array[NUM_ELEMENTS];
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        array[i] = rand() % 100;
    }

    long long totalSum = 0;
    pthread_t threads[num_threads];
    ThreadData threadData[num_threads];

    // Crear los hilos
    for (int i = 0; i < num_threads; ++i) {
        threadData[i].start = i * (NUM_ELEMENTS / num_threads);
        threadData[i].end = (i + 1) * (NUM_ELEMENTS / num_threads);
        threadData[i].array = array;
        pthread_create(&threads[i], NULL, sum_array, &threadData[i]);
    }

    // Esperar a que los hilos terminen
    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
        totalSum += threadData[i].sum;
    }

    printf("Suma total: %lld\n", totalSum);

    return 0;
}

// Exec code:
// gcc -o sequential_sum sequential_sum.c -pthread
// ./sequential_sum
