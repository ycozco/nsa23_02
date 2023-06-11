#include <stdio.h>
#include <unistd.h>

int main() {
    /* fork a child process */
    int child1 = fork();
    
    /* fork another child process */
    int child2 = fork();
    
    /* and fork another */
    int child3 = fork();
    
    printf("Proceso actual: %d, PID del padre: %d\n", getpid(), getppid());
    
    return 0;
}
//how execute this code?
//gcc -o ejer05 ejer05.c