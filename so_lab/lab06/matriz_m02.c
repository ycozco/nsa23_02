#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 3

struct parametros {
    int id;
    float matriz[SIZE][SIZE];
};

void init(float m[SIZE][SIZE]) {
    srand((unsigned int) time(NULL)); // Semilla para generar números aleatorios
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            m[i][j] = (float)rand() / RAND_MAX * 100;
        }
    }
}

void mostrarMatriz(float m[SIZE][SIZE]) {
    printf("Contenido de la matriz:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%.2f ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void* matrizporescalar(void* arg) {
    struct parametros* p = (struct parametros*)arg;
    float escalar = 5.0;
    for (int i = 0; i < SIZE; i++) {
        printf("Hilo %d multiplicando fila %d\n", p->id, i);
        for (int j = 0; j < SIZE; j++) {
            p->matriz[i][j] *= escalar;
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    pthread_t h1;
    struct parametros p1;
    p1.id = 1;
    init(p1.matriz);

    mostrarMatriz(p1.matriz); // Mostrar matriz original

    pthread_create(&h1, NULL, matrizporescalar, (void*)&p1);
    pthread_join(h1, NULL);

    mostrarMatriz(p1.matriz); // Mostrar matriz modificada

    printf("Fin\n");

    return 0;
}
// exec code: gcc matrizm02.c -o matrizm02 -lpthread