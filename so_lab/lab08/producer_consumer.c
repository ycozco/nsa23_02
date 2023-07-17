#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

// El buffer
int buffer[BUFFER_SIZE];
// Contador del buffer
int count = 0;

// Los semáforos
sem_t mutex;
sem_t empty;
sem_t full;

// Función del productor
void *productor(void *param) {
    int item;
    int num = *(int*)param;

    while(1) {
        // Producir un elemento
        item = rand();

        // Esperar si el buffer está lleno
        sem_wait(&empty);

        // Esperar por el mutex
        sem_wait(&mutex);

        // Agregar el elemento al buffer
        buffer[count] = item;
        count++;

        printf("El productor %d produjo el elemento %d\n", num, item);

        // Señalizar el mutex y full
        sem_post(&mutex);
        sem_post(&full);

        sleep(rand() % 3);
    }
}

// Función del consumidor
void *consumidor(void *param) {
    int item;
    int num = *(int*)param;

    while(1) {
        // Esperar si el buffer está vacío
        sem_wait(&full);

        // Esperar por el mutex
        sem_wait(&mutex);

        // Remover un elemento del buffer
        item = buffer[count-1];
        count--;

        printf("El consumidor %d consumió el elemento %d\n", num, item);

        // Señalizar el mutex y empty
        sem_post(&mutex);
        sem_post(&empty);

        sleep(rand() % 3);
    }
}

int main() {
    // Inicializar los semáforos
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    // Crear los hilos de productores y consumidores
    pthread_t productores[NUM_PRODUCERS], consumidores[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        int *num = malloc(sizeof(int));
        *num = i+1;
        pthread_create(&productores[i], NULL, productor, num);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        int *num = malloc(sizeof(int));
        *num = i+1;
        pthread_create(&consumidores[i], NULL, consumidor, num);
    }

    // Esperar a que los hilos terminen
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(productores[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumidores[i], NULL);
    }

    return 0;
}

// path: so_lab/lab08/producer_consumer.c
// how to exec: gcc producer_consumer.c -o producer_consumer -lpthread