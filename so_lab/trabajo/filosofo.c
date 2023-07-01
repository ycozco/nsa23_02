#include <iostream>
#include <thread>
#include <semaphore.h>

#define NUM_FILOSOFOS 5
#define IZQUIERDA (i + NUM_FILOSOFOS - 1) % NUM_FILOSOFOS
#define DERECHA (i + 1) % NUM_FILOSOFOS

sem_t cubierto[NUM_FILOSOFOS];
sem_t inicioSemaforo;

void meditar() {
    // Lógica para meditar
}

void alimentarse(int id) {
    std::cout << "Filósofo " << id << " está tratando de obtener los cubiertos." << std::endl;

    // Solicitar los cubiertos
    sem_wait(&cubierto[IZQUIERDA]);
    sem_wait(&cubierto[DERECHA]);

    std::cout << "Filósofo " << id << " tiene los cubiertos y está comiendo." << std::endl;
    // Lógica para alimentarse

    // Liberar los cubiertos
    sem_post(&cubierto[DERECHA]);
    sem_post(&cubierto[IZQUIERDA]);
}

void filosofo(int id) {
    while (true) {
        meditar();

        sem_wait(&inicioSemaforo);

        alimentarse(id);

        sem_post(&inicioSemaforo);
    }
}

int main() {
    std::thread filosofos[NUM_FILOSOFOS];

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        sem_init(&cubierto[i], 0, 1);
    }

    sem_init(&inicioSemaforo, 0, 1);

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        filosofos[i] = std::thread(filosofo, i);
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        filosofos[i].join();
    }

    return 0;
}
