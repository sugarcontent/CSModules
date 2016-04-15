/*
	Name: Terence Chok
	Matric: A0124503W

	Name: Gilbert Chua
	Matric: A0123972A
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define ARR_SIZE 1000

void createProcess(char userInput[]);
void childProcess(pid_t pid, char userInput[]);
void parentProcess(pid_t pid);

int main(){

	char userInput[ARR_SIZE];

	while(1){

		printf("> ");

		fgets(userInput, sizeof(userInput), stdin);
		userInput[strlen(userInput)-1] = '\0';

		createProcess(userInput);
	}
}

void createProcess(char userInput[]){

	pid_t pid = fork();

	if (pid == 0) 
		childProcess(pid, userInput);
	else
		parentProcess(pid);
}

void childProcess(pid_t pid, char userInput[]) {

	printf("Parent pid: %d\n",getppid());

	int count = 0;
	char *command;
	char *argStorage[ARR_SIZE];

	command = strtok(userInput, " ");
	argStorage[count++] = command;

	while (command != NULL) {
		command = strtok(NULL, " ");
		argStorage[count++] = command;
	}

	execvp(argStorage[0], argStorage);
	printf("Shell Error: %s\n", strerror(errno));
	return;
}

void parentProcess(pid_t pid) {

	printf("Loading new process with id %d\n", pid);

	int status;
	wait(&status);
}
