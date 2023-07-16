#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
#else
    union semun {
        int val;
        struct semid_ds* buf;
        unsigned short int* array;
        struct seminfo* __buf;
    };
#endif

int main() {
    key_t Clave;
    int Id_Semaforo;
    struct sembuf Operacion;
    union semun arg;
    int i;

    Clave = ftok("/bin/ls", 33);
    if (Clave == (key_t)-1) {
        printf("No puedo conseguir clave de semaforo \n ");
        exit(0);
    }

    Id_Semaforo = semget(Clave, 10, 0600 | IPC_CREAT);
    if (Id_Semaforo == -1) {
        printf("No puedo crear semaforo \n");
        exit(0);
    }

    Operacion.sem_num = 0;
    Operacion.sem_op = 1;
    Operacion.sem_flg = 0;

    for (i = 0; i < 10; i++) {
        printf("Levanto Semaforo \n");
        semop(Id_Semaforo, &Operacion, 1);
        sleep(1);
    }
}
// path: so_lab\lab08\code02.c
// how to exec : gcc code02.c -o code02