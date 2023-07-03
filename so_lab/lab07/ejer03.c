#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 1000
#define M 1000
#define P 1000
#define NUM_THREADS 20

int A[N][M];
int B[M][P];
int C[N][P];

pthread_mutex_t mutex;

typedef struct {
    int startRow;
    int endRow;
} ThreadData;

void* multiply(void* arg) {
    ThreadData* data = (ThreadData*) arg;

    // Multiplicación de las matrices en el rango de filas asignado al hilo
    for (int i = data->startRow; i < data->endRow; i++) {
        for (int j = 0; j < P; j++) {
            int sum = 0;
            for (int k = 0; k < M; k++) {
                sum += A[i][k] * B[k][j];
            }

            // Adquirir el mutex antes de actualizar la matriz resultante C
            pthread_mutex_lock(&mutex);
            C[i][j] = sum;
            pthread_mutex_unlock(&mutex);
        }
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData threadData[NUM_THREADS];

    // Inicializar las matrices A y B con valores aleatorios
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            A[i][j] = rand() % 10;
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            B[i][j] = rand() % 10;
        }
    }

    pthread_mutex_init(&mutex, NULL); // Inicializar el mutex

    // Crear hilos para realizar la multiplicación de matrices
    int rowsPerThread = N / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        threadData[i].startRow = i * rowsPerThread;
        threadData[i].endRow = (i + 1) * rowsPerThread;

        pthread_create(&threads[i], NULL, multiply, &threadData[i]);
    }

    // Esperar a que los hilos terminen
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex); // Destruir el mutex

    // Imprimir la matriz resultante C
    printf("Matriz resultante C:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
// file name : ejer03.c
// how to exec: gcc -o ejer03 ejer03.c -lpthread