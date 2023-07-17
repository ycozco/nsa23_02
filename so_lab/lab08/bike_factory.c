#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 10
#define M 20

sem_t sem_ruedas;
sem_t sem_cuadros;
sem_t sem_manillares;
sem_t sem_bicicletas;

int ruedas_count = 0;
int cuadros_count = 0;
int manillares_count = 0;
int bicicletas_count = 0;

void *OP1(void *param) {
    while(ruedas_count < M) {
        // Produce ruedas
        ruedas_count += 2;
        printf("OP1 produjo dos ruedas\n");
        sem_post(&sem_ruedas);
        sem_post(&sem_ruedas);
        usleep(200000);
    }
}

void *OP2(void *param) {
    while(cuadros_count < N) {
        // Produce cuadros
        cuadros_count++;
        printf("OP2 produjo un cuadro\n");
        sem_post(&sem_cuadros);
        usleep(200000);
    }
}

void *OP3(void *param) {
    while(manillares_count < N) {
        // Produce manillares
        manillares_count++;
        printf("OP3 produjo un manillar\n");
        sem_post(&sem_manillares);
        usleep(200000);
    }
}

void *Montador(void *param) {
    while(bicicletas_count < N) {
        sem_wait(&sem_ruedas);
        sem_wait(&sem_ruedas);
        sem_wait(&sem_cuadros);
        sem_wait(&sem_manillares);
        printf("Montador ensambló una bicicleta\n");
        bicicletas_count++;
        sem_post(&sem_bicicletas);
        usleep(200000);
    }
}

int main() {
    sem_init(&sem_ruedas, 0, 0);
    sem_init(&sem_cuadros, 0, 0);
    sem_init(&sem_manillares, 0, 0);
    sem_init(&sem_bicicletas, 0, 0);

    pthread_t hilo_OP1, hilo_OP2, hilo_OP3, hilo_Montador;
    pthread_create(&hilo_OP1, NULL, OP1, NULL);
    pthread_create(&hilo_OP2, NULL, OP2, NULL);
    pthread_create(&hilo_OP3, NULL, OP3, NULL);
    pthread_create(&hilo_Montador, NULL, Montador, NULL);

    pthread_join(hilo_OP1, NULL);
    pthread_join(hilo_OP2, NULL);
    pthread_join(hilo_OP3, NULL);
    pthread_join(hilo_Montador, NULL);

    return 0;
}

// path: so_lab/lab08/bike_factory.c
// how to exec: gcc bike_factory.c -o bike_factory -lpthread
