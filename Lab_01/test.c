#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

bool exitCmd = 0;
char *str[60];
char *arg[5];
int i;
int fd[2];
char write_msg[BUFFER_SIZE] = "toto";
char read_msg[BUFFER_SIZE];

void *threadA(void *thread_argument) {
	sleep(10);
	int i  = (int)thread_argument;
	printf("arguments : %s %s %s %s %d\n", arg[0], arg[1], arg[2], arg[3], i);
	int s = execvp(arg[0], arg);
	printf("%d\n", s);
	//fflush(stdout);
	
}

int main (int argc, char* argv[]) {

pid_t pid;
//char *str[60];
//char *arg[4];
//int len;
//bool exitCmd = 0;

do {

	struct rusage usage;
	struct timeval start, end;
	struct timeval timeOfDayStart, timeOfDayEnd;
	int rUsageInt = 1;
	int wallClockTimeInt = 1;
	

	toto();

	//gettimeofday(&timeOfDayStart, NULL);
	if (pipe(fd) == -1) {
		printf("Pipe failed\n");
	} else {
		printf("ok\n");
	}

	pid = fork();
	//char *command;
	//thread_t* thTab[];
			
	if (pid < 0) {
		printf("Erreur de fork.\n");
		return 1;
	}
	else if (pid == 0){
		printf("Le pid du fils : %d et le père : %d\n", getpid(), getppid());
		int tempo = 0;
		int intThread = 0;
		pthread_t th[10];

		read(fd[READ_END], read_msg, BUFFER_SIZE);
		printf("Child read\n", read_msg);

		do {
			if (strcmp(arg[i - 1], "&") != 0) {
				execvp(arg[0], arg);
				toto();
				break;
			}
			//printf("Dans le Do : %d\n", tempo);
			tempo = 1;
			if (strcmp(arg[i - 1], "&") == 0) 
			{
				
				printf("Valeur de intThread : %d\n", intThread);
				arg[i - 1] = NULL;
				//printf("arguments : %s %s %s %s\n", arg[0], arg[1], arg[2], arg[3]);
				//printf("%d\n", i);
			
				pthread_create(&th[intThread], NULL, threadA, (void*) intThread);
				intThread = intThread + 1;
				//arg[i - 1] = "";
				toto();
				//printf("arguments : %s %s %s %s\n", arg[0], arg[1], arg[2], arg[3]);
				//printf("Le i vaut : %d\n", i);
				if (strcmp(arg[i - 1], "&") != 0) {
					//printf("Dans le If : %d\n", tempo);
					tempo = 0;
				}
			}
		} while (1);

		printf("%s\n", "Je suis dehors");
		pthread_exit(NULL);
			
	} else if (pid > 0) {	
		printf("Le pid du père : %d et le fils : %d\n", getpid(), pid);
		close(fd[READ_END]);
		write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
		close(fd[WRITE_END]);
		wait(&pid);
	}

} while (exitCmd == 0);

}

void toto() {
	int len;

	printf("Log710Shell%>");

	if(fgets(str, 60, stdin) !=  NULL)
	{
		len = strlen(str); 
		if(len > 0 && str[len-1] == '\n') {
			str[len-1] = '\0';
		}

		arg[0] = strtok(str," \n");
		i = 0;
						
		while (arg[i] != NULL)
		{
			i = i + 1;
			arg[i] = strtok (NULL, " \n");	
		}
	}

	if(strcmp(arg[0], "exit") == 0)
	{					
		exitCmd = 1;
		exit(0);				
	} else if (strcmp(arg[0], "cd") == 0) {
		chdir(arg[1]);	
	}
}
