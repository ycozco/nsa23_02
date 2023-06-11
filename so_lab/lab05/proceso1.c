#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CLAVE_MSG 2000
#define ERROR -1
#define INFO 150
#define TIPO 7

typedef struct {
    long tipo;
    int info;
} MENSAJE;

int main() {
    int qid;
    MENSAJE msg;
    int opcion;

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
            if (msgrcv(qid, &msg, sizeof(MENSAJE) - sizeof(long), TIPO, 0) == ERROR) {
                perror("msgrcv:");
                exit(errno);
            }
            printf("Mensaje recibido de tipo = %ld con info = %d\n", msg.tipo, msg.info);
            break;

        default:
            printf("No ha elegido ninguna opción válida\n");
    }

    exit(0);
}

// exec code : gcc proceso1.c -o proceso1
