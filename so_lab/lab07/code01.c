#include <stdio.h>
#include <pthread.h>

void* funcion(void* p1);
void printResult(char* threadName, int value);

int c = 0;

int main() {
    pthread_t hilo;
    pthread_attr_t attr;
    int error;

    pthread_attr_init(&attr);
    error = pthread_create(&hilo, &attr, funcion, NULL);

    if (error != 0) {
        perror("error");
        return (-1);
    }

    printResult((char*)"proceso Padre", 1);

    pthread_join(hilo, NULL);

    return 0;
}

void* funcion(void* p11) {
    printResult((char*)"Proceso Hijo:", -1);
    pthread_exit(0);
}

void printResult(char* threadName, int v) {
    int i = 0;
    
    while (i < 300) {
        c += v;
        printf("Inicio ");
        
        for (int j = 0; j < 10000; j++) {} //delay
        
        printf("%s: %d ", threadName, c);
        
        for (int j = 0; j < 10000; j++) {} //delay
        
        printf("Finalizacion \n");
        
        i++;
    }
}
