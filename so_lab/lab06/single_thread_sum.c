#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_ELEMENTS 5000

int main() {
    srand((unsigned int) time(NULL)); // Semilla para números aleatorios

    // Crear y llenar el array con números aleatorios
    int array[NUM_ELEMENTS];
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        array[i] = rand() % 100; // Números aleatorios entre 0 y 99
    }

    // Sumar los elementos del array de forma secuencial
    long long totalSum = 0;
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        totalSum += array[i];
    }

    printf("Suma total: %lld\n", totalSum);

    return 0;
}

// Exec code:
// gcc -o single_thread_sum single_thread_sum.c
// ./single_thread_sum
