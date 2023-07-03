#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutex;
pthread_cond_t empty;
pthread_cond_t full;

void* productor(void* arg) {
    int dato = 1;
    while (1) {
        pthread_mutex_lock(&mutex);

        // Esperar si el buffer está lleno
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&empty, &mutex);
        }

        // Escribir el dato en el buffer
        buffer[count] = dato;
        count++;

        printf("Productor produce dato: %d\n", dato);

        // Notificar al consumidor que hay un nuevo dato disponible
        pthread_cond_signal(&full);

        pthread_mutex_unlock(&mutex);

        dato++;
    }
    return NULL;
}

void* consumidor(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // Esperar si el buffer está vacío
        while (count == 0) {
            pthread_cond_wait(&full, &mutex);
        }

        // Leer el dato del buffer
        int dato = buffer[count - 1];
        count--;

        printf("Consumidor consume dato: %d\n", dato);

        // Notificar al productor que hay un espacio vacío en el buffer
        pthread_cond_signal(&empty);

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t hiloProductor, hiloConsumidor;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&full, NULL);

    pthread_create(&hiloProductor, NULL, productor, NULL);
    pthread_create(&hiloConsumidor, NULL, consumidor, NULL);

    pthread_join(hiloProductor, NULL);
    pthread_join(hiloConsumidor, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);

    return 0;
}
// file name : productor_consumidor.c
// how to exec : gcc -pthread productor_consumidor.c -o productor_consumidor