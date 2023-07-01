#include <iostream>
#include <thread>
#include <semaphore.h>

#define NUM_FILOSOFOS 5
#define IZQUIERDA(i) ((i + NUM_FILOSOFOS - 1) % NUM_FILOSOFOS)
#define DERECHA(i) ((i + 1) % NUM_FILOSOFOS)

sem_t cubierto[NUM_FILOSOFOS];
sem_t inicioSemaforo;

void meditar() {
    // Lógica para meditar
    // Aquí puedes implementar el código correspondiente a la meditación de los filósofos
}

void alimentarse(int id) {
    std::cout << "Filósofo " << id << " está tratando de obtener los cubiertos." << std::endl;

    // Solicitar los cubiertos
    wait(&cubierto[IZQUIERDA(id)]);
    wait(&cubierto[DERECHA(id)]);

    std::cout << "Filósofo " << id << " tiene los cubiertos y está comiendo." << std::endl;

    // Lógica para alimentarse
    // Aquí puedes implementar el código correspondiente a la alimentación de los filósofos

    // Liberar los cubiertos
    signal(&cubierto[DERECHA(id)]);
    signal(&cubierto[IZQUIERDA(id)]);
}

void filosofo(int id) {
    while (true) {
        meditar();

        wait(&inicioSemaforo);

        alimentarse(id);

        signal(&inicioSemaforo);
    }
}

int main() {
    std::thread filosofos[NUM_FILOSOFOS];

    // Inicializar los semáforos de los cubiertos
    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        initSem(&cubierto[i], 1);
    }

    // Inicializar el semáforo de inicio
    initSem(&inicioSemaforo, 1);

    // Crear los hilos de los filósofos
    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        filosofos[i] = std::thread(filosofo, i);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        filosofos[i].join();
    }

    return 0;
}

// how to exec filosofo.cpp on linux
// gcc -pthread filosofo.c -o filosofoc
// 
