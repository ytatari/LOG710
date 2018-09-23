#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>

int main (int argc, char* argv[]) {

pid_t pid;
char *str[60];
char *arg[3];
int len;
bool exitCmd = 0;

do {

	struct rusage usage;
	struct timeval start, end;
	struct timeval timeOfDayStart, timeOfDayEnd;
	int rUsageInt = 1;
	int wallClockTimeInt = 1;

	printf("Log710Shell%>");

	if(fgets(str, 60, stdin) !=  NULL)
	{
		len = strlen(str); 
		if(len > 0 && str[len-1] == '\n') {
			str[len-1] = '\0';
		}

		arg[0] = strtok(str," \n");
		int i = 0;
						
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

	if (getrusage(RUSAGE_SELF,&usage) == 0) {
		start = usage.ru_stime;
	}

	gettimeofday(&timeOfDayStart, NULL);

	pid = fork();
	char *command;
			
	if (pid < 0) {
		printf("Erreur de fork.\n");
		return 1;
	}
	else if (pid == 0){
		//printf("Le pid du fils : %d et le père : %d\n", getpid(), getppid());

		if (execvp(arg[0], arg) == -1) {
			printf("Bad command-line arguments\n");
		}				
	} else if (pid > 0) {	
		//printf("Le pid du père : %d et le fils : %d\n", getpid(), pid);
		wait(&pid);
		wallClockTimeInt = gettimeofday(&timeOfDayEnd, NULL);
		rUsageInt = getrusage(RUSAGE_SELF,&usage);
	}

	if ( wallClockTimeInt == 0) {
		float response = (((float)timeOfDayEnd.tv_sec - (float)timeOfDayStart.tv_sec) * 1000) 
			+ (((float)timeOfDayEnd.tv_usec - (float)timeOfDayStart.tv_usec) / 1000);
		printf("==========================Statistics==========================\n");
		printf("Time used : %fms\n", response);
	}

	if ( rUsageInt == 0) {
		end = usage.ru_stime;
		float response = ((float)end.tv_sec - (float)start.tv_sec * 1000) + (((float)end.tv_usec - 
			(float)start.tv_usec) / 1000);
		printf("System CPU time used : %fms\n", response);
		printf("Involontary context switches : %ld\n", usage.ru_nivcsw);
		printf("Volontary context switches : %ld\n", usage.ru_nvcsw);
		printf("Page fault serviced that required I/O activity : %ld\n", usage.ru_majflt);
		printf("Page fault serviced without any I/O activity : %ld\n", usage.ru_minflt);
	}

} while (exitCmd == 0);

}