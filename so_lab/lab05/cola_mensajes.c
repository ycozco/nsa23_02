#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define CLAVE_MSG 2000
#define ERROR -1
#define INFO 150
#define TIPO 7

typedef struct {
    long tipo;
    int info;
} MENSAJE;

int main() {
    int qid, opcion;
    MENSAJE msg, msg2;
    int lector = 0;

    qid = msgget(CLAVE_MSG, IPC_CREAT | IPC_EXCL | 0666);

    if (qid == ERROR) {
        if (errno == EEXIST) {
            printf("Ya existe una cola de mensajes, accediendo...\n");
            qid = msgget(CLAVE_MSG, 0666);
            if (qid == ERROR) {
                perror("msgget:");
                exit(errno);
            }
        }
    }

    printf("Cola de mensajes creada...\n");
    printf("Enviar mensaje[1] o leer mensaje[2]:\n");
    scanf("%d", &opcion);

    switch (opcion) {
        case 1:
            msg.tipo = TIPO; // pid del destinatario
            msg.info = INFO; // informacion a transmitir
            printf("Enviando mensaje...\n");
            if (msgsnd(qid, &msg, sizeof(MENSAJE) - sizeof(long), 0) == ERROR) {
                perror("msgsnd:");
                exit(errno);
            }
            printf("Mensaje enviado.\n");
            break;

        case 2:
            printf("Leyendo el primer mensaje de la cola...\n");
            if (msgrcv(qid, &msg2, sizeof(MENSAJE) - sizeof(long), 0, 0) == ERROR) {
                perror("msgrcv:");
                exit(errno);
            }
            printf("Mensaje recibido de tipo = %ld con info = %d\n", msg2.tipo, msg2.info);
            lector = 1;
            break;

        default:
            printf("No ha elegido ninguna opcion\n");
    }

    if (lector == 1) {
        if (msgctl(qid, IPC_RMID, NULL) == ERROR) {
            perror("msgctl:");
            exit(errno);
        }
        printf("Cola de mensajes eliminada\n");
    }

    exit(0);
}
// exec this code : gcc cola_mensajes.c -o cola_mensajes