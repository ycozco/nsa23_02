#include <stdio.h>
#include <pthread.h>

void* funcion(void* p1);
int c = 0;

int main() {
    pthread_t hilo;
    pthread_attr_t attr;
    int error;

    pthread_attr_init(&attr);
    error = pthread_create(&hilo, &attr, funcion, NULL);
    if (error != 0) {
        perror("error");
        return -1;
    }

    int i = 0;
    while (i < 300) {
        c++;
        printf("Padre: %d\n", c);
        i++;
    }

    // La sentencia pthread_join() se removio

    return 0;
}

void* funcion(void* p1) {
    int i = 0;
    while (i < 300) {
        c--;
        printf("Hijo: %d\n", c);
        i++;
    }
    pthread_exit(0);
}
// code01_incompleto.c end
// how to execute with lpthread:
// gcc -o code01_incompleto code01_incompleto.c -lpthread
