#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/resource.h>

bool exitCmd = 0;
char *str[60];
char *arg[5];
int i;

void *threadA (void *thread_argument) {
	sleep(5);
	//int i  = (int)thread_argument;
	printf("arguments : %s %s %s %s %d\n", arg[0], arg[1], arg[2], arg[3], i);
	execvp(arg[0], arg);
	fflush(stdout);
	
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

	//printf("Log710Shell%>");

	//if(fgets(str, 60, stdin) !=  NULL)
	//{
	//	len = strlen(str); 
	//	if(len > 0 && str[len-1] == '\n') {
	//		str[len-1] = '\0';
	//	}
//
//		arg[0] = strtok(str," \n");
//		i = 0;
//						
//		while (arg[i] != NULL)
//		{
//			i = i + 1;
//			arg[i] = strtok (NULL, " \n");	
//		}
	//}

//	if(strcmp(arg[0], "exit") == 0)
//	{					
//		exitCmd = 1;
//		exit(0);				
//	} else if (strcmp(arg[0], "cd") == 0) {
//		chdir(arg[1]);	
//	}

	//if (getrusage(RUSAGE_SELF,&usage) == 0) {
	//	start = usage.ru_stime;
	//}

	//gettimeofday(&timeOfDayStart, NULL);

	pid = fork();
	//char *command;
	//thread_t* thTab[];
			
	if (pid < 0) {
		printf("Erreur de fork.\n");
	q	return 1;
	}
	else if (pid == 0){
		printf("Le pid du fils : %d et le père : %d\n", getpid(), getppid());
		int tempo = 0;
		int intThread = 0;
		pthread_t th[10];

		for (intThread = 0; intThread < 10; intThread++) {
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
			
				pthread_create(&th[intThread], NULL, threadA, 1);
				//sleep(10);
				pthread_create(&th[intThread + 1], NULL, threadA, 1);
				//intThread = intThread + 1;
				//arg[i - 1] = "";
				printf("%s\n", "Je suis là");
				toto();
				//printf("arguments : %s %s %s %s\n", arg[0], arg[1], arg[2], arg[3]);
				//printf("Le i vaut : %d\n", i);
				if (strcmp(arg[i - 1], "&") != 0) {
					//printf("Dans le If : %d\n", tempo);
					tempo = 0;
				}
			}
		}

		printf("%s\n", "Je suis dehors");
		pthread_exit(NULL);
			
	} else if (pid > 0) {	
		//printf("Le pid du père : %d et le fils : %d\n", getpid(), pid);
		wait(&pid);
		//wallClockTimeInt = gettimeofday(&timeOfDayEnd, NULL);
		//rUsageInt = getrusage(RUSAGE_SELF,&usage);
	}

	//if ( wallClockTimeInt == 0) {
	//	float response = (((float)timeOfDayEnd.tv_sec - (float)timeOfDayStart.tv_sec) * 1000) 
	//		+ (((float)timeOfDayEnd.tv_usec - (float)timeOfDayStart.tv_usec) / 1000);
		//printf("==========================Statistics==========================\n");
		//printf("Time used : %fms\n", response);
	//}

	//if ( rUsageInt == 0) {
	//	end = usage.ru_stime;
		//float response = ((float)end.tv_sec - (float)start.tv_sec * 1000) + (((float)end.tv_usec - 
		//	(float)start.tv_usec) / 1000);
		//printf("System CPU time used : %fms\n", response);
		//printf("Involontary context switches : %ld\n", usage.ru_nivcsw);
		//printf("Volontary context switches : %ld\n", usage.ru_nvcsw);
		//printf("Page fault serviced that required I/O activity : %ld\n", usage.ru_majflt);
		//printf("Page fault serviced without any I/O activity : %ld\n", usage.ru_minflt);
	//}

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
