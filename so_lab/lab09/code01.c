#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h> // Incluir la biblioteca para la función sleep

#define SUMSIZE 20 // Aumentar el número de iteraciones para ambos hilos
#define BUFSIZE 8

int buffer[BUFSIZE];
sem_t llenos;
sem_t vacios;

static void *productor(void *arg1) {
    int i, entra, producir;
    entra = 0;
    for (i = 1; i <= SUMSIZE; i++) {
        while ((producir = getchar()) == '\n');
        sem_wait(&vacios);
        buffer[entra] = producir;
        entra = (entra + 1) % BUFSIZE;
        printf("Productor -->\t %c\n", producir);
        sem_post(&llenos);
    }
    printf("Productor ha terminado\n");
    return NULL;
}

static void *consumidor(void *arg2) {
    int i, sale, consumir;
    sale = 0;
    for (i = 1; i <= SUMSIZE; i++) {
        sem_wait(&llenos);
        printf("\tConsumidor <--\t");
        sleep(1); // El consumo se demora 1 segundo
        sem_post(&vacios);
        consumir = buffer[sale];
        sale = (sale + 1) % BUFSIZE;
        printf(" %c\n", consumir);
    }
    printf("Consumidor ha terminado\n");
    return NULL;
}

int main() {
    pthread_t prodtid;
    pthread_t constid;

    // Semáforos contadores para controlar los espacios en el almacén
    sem_init(&llenos, 0, 0);
    sem_init(&vacios, 0, BUFSIZE);

    printf("Iniciando el programa...\n");

    pthread_create(&prodtid, NULL, productor, NULL);
    pthread_create(&constid, NULL, consumidor, NULL);

    pthread_join(prodtid, NULL);
    pthread_join(constid, NULL);

    printf("Todos los procesos han terminado.\n");

    // Se destruyen los semáforos
    sem_destroy(&llenos);
    sem_destroy(&vacios);

    return 0;
}
// path: so_lab\lab09\code01.c
// how to exec: gcc code01.c -o code01 -lpthread