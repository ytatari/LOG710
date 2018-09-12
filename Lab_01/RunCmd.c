#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {
	int pid = fork();

	if (pid<0){
		printf("Erreur de fork.\n");
		printf("toto %c \n", argv[1]);
		return 1;
	}
	else if (pid) {
		printf("je suis le parent, pid=%d \n");
		printf("le id de mon fils=%d \n", pid);
		printf("toto %d \n", argc);
	}
	else {
		printf("je suis le fils, mon id= %d \n");
		printf("l'argument est %s \n", argv[3]);
		return 1;
	}
	return 0;

}