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
    
    pthread_join(hilo, NULL);
    
    return 0;
}

void* funcion(void* p11) {
    int i = 0;
    while (i < 300) {
        c--;
        printf("Hijo: %d\n", c);
        i++;
    }
    
    return NULL;
}
