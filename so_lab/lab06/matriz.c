#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

struct parametros {
    int id;
    float escalar;
    float matriz[3][3];
};

void init(float m[3][3]) {
    int i;
    int j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            m[i][j] = (float)rand() / RAND_MAX * 100;
        }
    }
}

void* matrizporescalar(void* arg) {
    struct parametros* p;
    int i;
    int j;
    p = (struct parametros*)arg;
    for (i = 0; i < 3; i++) {
        printf("Hilo %d multiplicando fila %d\n", p->id, i);
        for (j = 0; j < 3; j++) {
            p->matriz[i][j] = p->matriz[i][j] * p->escalar;
            sleep(5);
        }
    }
    return NULL;
}

void mostrarMatriz(float m[3][3]) {
    int i, j;
    printf("Contenido de la matriz:\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%.2f ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    pthread_t h1;
    struct parametros p1;
    p1.id = 1;
    p1.escalar = 5.0;
    init(p1.matriz);

    mostrarMatriz(p1.matriz); // Mostrar matriz antes de la modificación

    pthread_create(&h1, NULL, matrizporescalar, (void*)&p1);
    pthread_join(h1, NULL);

    mostrarMatriz(p1.matriz); // Mostrar matriz después de la modificación

    printf("Fin\n");

    return 0;
}
// exec code: gcc -o matriz matriz.c -pthread
