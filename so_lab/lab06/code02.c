#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main() {
    struct timeval t0, t1;
    int i = 0;
    int id = -1;
    gettimeofday(&t0, NULL);
    for (i = 0; i < 100; i++) {
        id = fork();
        if (id == 0) return 0;
    }
    if (id != 0) {
        gettimeofday(&t1, NULL);
        unsigned int ut1 = t1.tv_sec * 1000000 + t1.tv_usec;
        unsigned int ut0 = t0.tv_sec * 1000000 + t0.tv_usec;
        /* Tiempo medio en microsegundos */
        printf("%f\n", (ut1 - ut0) / 100.0);
    }
    return 0;
}
// exec code: gcc code02.c -o code02
