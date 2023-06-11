#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#define CLAVE_MSG 2000
#define ERROR -1

typedef struct {
    long tipo;
    int x;
    int y;
} MENSAJE;

int main() {
    int qid;
    MENSAJE msg;

    qid = msgget(CLAVE_MSG, 0666);
    if (qid == ERROR) {
        perror("msgget:");
        exit(errno);
    }

    printf("Jugador O, esperando movimiento...\n");
    if (msgrcv(qid, &msg, sizeof(MENSAJE) - sizeof(long), 2, 0) == ERROR) {
        perror("msgrcv:");
        exit(errno);
    }

    printf("Movimiento recibido: %d, %d\n", msg.x, msg.y);

    exit(0);
}
