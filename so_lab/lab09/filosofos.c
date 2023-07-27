#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_FILOSOFOS 5
#define PENSANDO 0
#define HAMBRIENTO 1
#define COMIENDO 2

sem_t tenedores[NUM_FILOSOFOS];
sem_t mutex;

int estado_filosofo[NUM_FILOSOFOS];

void prueba(int filosofo_id); // Prototipo de la función prueba

void *filosofo(void *arg) {
    int filosofo_id = *(int *)arg;
    while (1) {
        // Filósofo está pensando
        printf("Filósofo %d está pensando.\n", filosofo_id);
        usleep(rand() % 1000000); // Espera aleatoria para pensar

        // Filósofo quiere comer
        sem_wait(&mutex);
        estado_filosofo[filosofo_id] = HAMBRIENTO;
        printf("Filósofo %d tiene hambre.\n", filosofo_id);
        prueba(filosofo_id); // Intenta tomar tenedores
        sem_post(&mutex);

        // Espera a que los tenedores estén disponibles
        sem_wait(&tenedores[filosofo_id]);

        // Filósofo está comiendo
        printf("Filósofo %d está comiendo.\n", filosofo_id);
        usleep(rand() % 1000000); // Espera aleatoria para comer

        // Devuelve los tenedores
        sem_post(&tenedores[filosofo_id]);

        // Filósofo ha terminado de comer
        printf("Filósofo %d ha terminado de comer.\n", filosofo_id);
    }
}

void prueba(int filosofo_id) {
    if (estado_filosofo[filosofo_id] == HAMBRIENTO && estado_filosofo[(filosofo_id + 1) % NUM_FILOSOFOS] != COMIENDO &&
        estado_filosofo[(filosofo_id + NUM_FILOSOFOS - 1) % NUM_FILOSOFOS] != COMIENDO) {
        estado_filosofo[filosofo_id] = COMIENDO;
        sem_post(&tenedores[filosofo_id]);
    }
}

int main() {
    pthread_t filosofos[NUM_FILOSOFOS];
    int id_filosofos[NUM_FILOSOFOS];

    sem_init(&mutex, 0, 1);

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        sem_init(&tenedores[i], 0, 1);
        estado_filosofo[i] = PENSANDO;
        id_filosofos[i] = i;
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_create(&filosofos[i], NULL, filosofo, (void *)&id_filosofos[i]);
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_join(filosofos[i], NULL);
    }

    return 0;
}
// path: so_lab\lab09\filosofos.c
// how to exec (linux): gcc filosofos.c -o filosofos -lpthread