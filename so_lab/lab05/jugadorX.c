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

    printf("Jugador X, ingrese su movimiento (x y): ");
    scanf("%d %d", &msg.x, &msg.y);
    msg.tipo = 2;
    if (msgsnd(qid, &msg, sizeof(MENSAJE) - sizeof(long), 0) == ERROR) {
        perror("msgsnd:");
        exit(errno);
    }

    printf("Movimiento enviado.\n");

    exit(0);
}
