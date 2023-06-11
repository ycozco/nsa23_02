#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
		pid_t pid;
			/* fork a child process */
		        pid = fork();
				if (pid < 0){
							fprintf(stderr, "Fork Failed");
									return 1;
																							                }
					else if (pid == 0) {
								execlp("/bin/ls", "ls", NULL);
									}
						else{
									printf("Child Complete");
																							                }
							return 0;
}	
