Semáforo cubierto[5];
int i;

Filosofo(int i) {
    while (forever) {
        meditar();
        wait(cubierto[i]); // Usar cubierto izq
        wait(cubierto[(i + 1) % 5]); // Usar cubierto derecho

        alimentarse();

        signal(cubierto[(i + 1) % 5]); // Liberar cubierto derecho
        signal(cubierto[i]); // Liberar cubierto izquierdo
    }
}

main() {
    for (int i = 0; i < 5; i++)
        // Los semáforos inicializados en 1
        initSemaforo(cubierto[i], 1);

    cobegin {
        Filosofo(0); // Inicializar Filósofo 0
        Filosofo(1); // Inicializar Filósofo 1
        Filosofo(2); // Inicializar Filósofo 2
        Filosofo(3); // Inicializar Filósofo 3
        Filosofo(4); // Inicializar Filósofo 4
    }
}

Semáforo cubierto[5];
Semáforo control;
int i;

Filosofo(int i) {
    while (forever) {
        meditar();
        wait(control); // Inicializar Filósofos -1
        wait(cubierto[i]); // Usar cubierto izquierdo
        wait(cubierto[(i + 1) % 5]); // Usar cubierto derecho

        alimentarse();

        signal(cubierto[(i + 1) % 5]); // Liberar cubierto derecho
        signal(cubierto[i]); // Liberar cubierto izquierdo
        signal(control);
    }
}
