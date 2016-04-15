/*
	Name: Terence Chok 
	Matric: A0124503W

	Name: Gilbert Chua
	Matric: A0123972A
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv, char **envp){

	const char *key = "SHELL_PATH";
	char *shell_path, *ret;

	while(*envp) {
		ret = strstr(*envp, key);

		if (ret != NULL){
			shell_path = strstr(ret, "=");
			shell_path++;
		}

		printf("%s\n", *envp++);
	}

	printf("\n");

	if (shell_path == NULL){
		printf("SHELL_PATH value is UNKNOWN\n");
	}
	else{
		printf("SHELL_PATH value is %s\n", shell_path);
	}
}
