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
#define SIZE 3

typedef struct {
    long tipo;
    int x;
    int y;
} MENSAJE;

char tablero[SIZE][SIZE];

void imprimir_tablero() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", tablero[i][j] ? tablero[i][j] : '.');
        }
        printf("\n");
    }
}

int verificar_ganador() {
    for (int i = 0; i < SIZE; i++) {
        if (tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2] && tablero[i][0] != '.') {
            return 1;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        if (tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i] && tablero[0][i] != '.') {
            return 1;
        }
    }

    if (tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2] && tablero[0][0] != '.') {
        return 1;
    }

    if (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0] && tablero[0][2] != '.') {
        return 1;
    }

    return 0;
}

int main() {
    int qid;
    MENSAJE msg;
    pid_t pid;

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

    pid = fork();

    if (pid < 0) {
        perror("fork:");
        exit(errno);
    } else if (pid == 0) {
        // Proceso hijo (jugador O)
        while (1) {
            MENSAJE msg2;
            printf("Jugador O, esperando turno...\n");
            if (msgrcv(qid, &msg2, sizeof(MENSAJE) - sizeof(long), 2, 0) == ERROR) {
                perror("msgrcv:");
                exit(errno);
            }
            printf("Turno de O. Posición recibida: %d, %d\n", msg2.x, msg2.y);
            tablero[msg2.x][msg2.y] = 'O';
            imprimir_tablero();

            if (verificar_ganador()) {
                printf("Jugador O ha ganado!\n");
                break;
            }

            printf("Jugador O, ingrese su movimiento (x y): ");
            scanf("%d %d", &msg.x, &msg.y);
            msg.tipo = 1;
            msgsnd(qid, &msg, sizeof(MENSAJE) - sizeof(long), 0);
        }
    } else {
        // Proceso padre (jugador X)
        while (1) {
            printf("Jugador X, ingrese su movimiento (x y): ");
            scanf("%d %d", &msg.x, &msg.y);
            msg.tipo = 2;
            msgsnd(qid, &msg, sizeof(MENSAJE) - sizeof(long), 0);

            MENSAJE msg2;
            printf("Jugador X, esperando turno...\n");
            if (msgrcv(qid, &msg2, sizeof(MENSAJE) - sizeof(long), 1, 0) == ERROR) {
                perror("msgrcv:");
                exit(errno);
            }
            printf("Turno de X. Posición recibida: %d, %d\n", msg2.x, msg2.y);
            tablero[msg2.x][msg2.y] = 'X';
            imprimir_tablero();

            if (verificar_ganador()) {
                printf("Jugador X ha ganado!\n");
                break;
            }
        }
    }

    if (pid > 0) {
        wait(NULL); // Espera a que el proceso hijo termine
        if (msgctl(qid, IPC_RMID, NULL) == ERROR) {
            perror("msgctl:");
            exit(errno);
        }
        printf("Cola de mensajes eliminada\n");
    }

    exit(0);
}

//exec code: gcc tres_en_raya.c -o tres_en_raya
