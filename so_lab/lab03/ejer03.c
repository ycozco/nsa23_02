
#include <stdio.h>
int main(void) 
{
int pid;
printf("Hasta aqui hay un unico proceso...\n"); 
printf("Primera llamada a fork...\n");
/* Creamos un nuevo proceso. */
pid = fork(); 
if (pid == 0) {
printf("HIJO1: Hola, yo soy el primer hijo...\n");
printf("HIJO1: Voy a pararme durante 20 seg. y luego terminare\n"); 
sleep(20);
}
else if (pid > 0) {
printf("PADRE: Hola, soy el padre. El pid de mi hijo es: %d\n", pid);
/* Creamos un nuevo proceso. */
pid = fork(); 
if (pid == 0) {
printf("HIJO2: Hola, soy el segundo hijo...\n");
printf("HIJO2: El segundo hijo va a ejecutar la orden 'ls'...\n"); 
execlp("ls", "ls", NULL);
printf("HIJO2: Si ve este mensaje, el execlp no funciono...\n"); 
}
else if (pid > 0) {
printf("PADRE: Hola otra vez. Pid de mi segundo hijo: %d\n", pid); printf("PADRE: Voy a esperar a que terminen mis hijos...\n"); 
printf("PADRE: Ha terminado mi hijo %d\n", wait(NULL)); 
printf("PADRE: Ha terminado mi hijo %d\n", wait(NULL));
}
else
printf("Ha habido algun error al llamar por 2a vez al fork\n"); }
else
printf("Ha habido algun error al llamar a fork\n");
}
