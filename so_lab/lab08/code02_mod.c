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

// Declare the new functions
int create_semaphore(key_t key, int sem_flags);
void unlock_semaphore(int semid, struct sembuf *sops);

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

    Id_Semaforo = create_semaphore(Clave, 0600);

    Operacion.sem_num = 0;
    Operacion.sem_flg = 0;

    for (i = 0; i < 10; i++) {
        printf("Levanto Semaforo \n");
        unlock_semaphore(Id_Semaforo, &Operacion);
        sleep(1);
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

// Function to unlock a semaphore
void unlock_semaphore(int semid, struct sembuf *sops) {
    sops->sem_op = 1;
    if (semop(semid, sops, 1) == -1) {
        printf("No puedo desbloquear semaforo \n");
        exit(0);
    }
}
// path: so_lab\lab08\code02_mod.c
// how to exec : gcc code02_mod.c -o code02_mod