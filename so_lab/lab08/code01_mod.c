#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
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

// Declare the new functions
int create_semaphore(key_t key, int sem_flags);
void lock_semaphore(int semid, struct sembuf *sops);

int main() {
    key_t Clave;
    int Id_Semaforo;
    struct sembuf Operacion;
    union semun arg;
    int i = 0;

    Clave = ftok("/bin/ls", 33);
    if (Clave == (key_t)-1) {
        printf("No puedo conseguir clave de semaforo \n");
        exit(0);
    }

    Id_Semaforo = create_semaphore(Clave, 0600);

    arg.val = 0;
    semctl(Id_Semaforo, 0, SETVAL, &arg);

    Operacion.sem_num = 0;
    Operacion.sem_flg = 0;

    while (1) {
        printf(" Esperando Semaforo %d \n", i);
        lock_semaphore(Id_Semaforo, &Operacion);
        printf(" Salgo del Semaforo %d \n", i);
        i++;
    }
}

// Function to create a semaphore
int create_semaphore(key_t key, int sem_flags) {
    int semid = semget(key, 10, sem_flags | IPC_CREAT);
    if (semid == -1) {
        printf("No puedo crear semaforo \n");
        exit(0);
    }
    return semid;
}

// Function to lock a semaphore
void lock_semaphore(int semid, struct sembuf *sops) {
    sops->sem_op = -1;
    if (semop(semid, sops, 1) == -1) {
        printf("No puedo bloquear semaforo \n");
        exit(0);
    }
}
// path: so_lab\lab08\code01_mod.c
// how to exec : gcc code01_mod.c -o code01_mod