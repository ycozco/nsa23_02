#include <iostream>
#include <thread>
#include <semaphore.h>

#define NUM_FILOSOFOS 5

sem_t cubierto[NUM_FILOSOFOS];
sem_t control;
bool continuar = true; // Variable de control

void meditar() {
    // Lógica para meditar
}

void alimentarse(int id) {
    std::cout << "Filósofo " << id << " está tratando de obtener los cubiertos." << std::endl;

    sem_wait(&cubierto[id]); // Usar cubierto izquierdo
    sem_wait(&cubierto[(id + 1) % NUM_FILOSOFOS]); // Usar cubierto derecho

    std::cout << "Filósofo " << id << " tiene los cubiertos y está comiendo." << std::endl;

    // Lógica para alimentarse

    sem_post(&cubierto[(id + 1) % NUM_FILOSOFOS]); // Liberar cubierto derecho
    sem_post(&cubierto[id]); // Liberar cubierto izquierdo
}

void filosofo(int id) {
    while (continuar) { // Continuar mientras la variable de control sea verdadera
        meditar();

        sem_wait(&control); // Inicializar Filósofos -1

        alimentarse(id);

        sem_post(&control);
    }
}

int main() {
    std::thread filosofos[NUM_FILOSOFOS];

    // Inicializar los semáforos de los cubiertos
    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        sem_init(&cubierto[i], 0, 1);
    }

    sem_init(&control, 0, 1);

    // Crear los hilos de los filósofos
    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        filosofos[i] = std::thread(filosofo, i);
    }

    // Esperar un tiempo antes de detener a los filósofos (ejemplo: 5 segundos)
    std::this_thread::sleep_for(std::chrono::seconds(1));

    continuar = false; // Cambiar la variable de control para detener a los filósofos

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        filosofos[i].join();
    }

    return 0;
}
