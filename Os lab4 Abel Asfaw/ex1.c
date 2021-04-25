

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

// If you want To quit, enter 'quit' and CTRL+C

int main(int argc, char* argv[])
{
	int pid,count, printC=1;
	const char s[3] = " ";
	char *token[500];
	char *enter_directory[500];
	char string[1000]; // ls -l  for example

	
	while(1)
	{
	
		count= 0;
		// begin linux terminal
		
	     	static int clear = 1;
		if(clear){
			// Using ANSI to clear the screan
			printf(" \e[1;1H\e[2J");
			clear = 0;
		}
		while(printC<2) {	
	       printf("**********Welcome to Abel's linux shell intepreter*******\n");
               char *user = getenv("USER");
               printf("The username of this shell is: %s\n", user); 
               printC++;
               }

		fgets(string,sizeof(string),stdin);

		token[count] = strtok(string, s);


		while (token[count] != NULL){
			count++;
			token[count] = strtok(NULL, s);
		}
		
		//remove newline character 
		token[count-1][strlen(token[count-1])-1] = '\0';
		
		int result = strcmp(token[0], "quit");
		int result1 = strcmp(token[0], "cd");
		
		//if (result1 == 0){
                     // chdir(token[1]);
			//getchar();
			//printf("\nYou are logged in %s directory",token[1]);

	//}	

		if (result == 0){
			printf("\n\nExiting Shell!\n\n");
			getchar();
			break;	
	}
		
  	pid = fork();
		if (pid == -1)
		{
			perror("Forking child failed");
			exit(0);
		}
		
		if (pid == 0)
		{
			// Check for command 
			execv(token[0], token);
			
			// Checking for command outside of cd
			execvp(token[0], token);
			
			// Command inot valid
			printf("Command not found, Please enter a correct command\n For help please type 'cat --help'\n\n");
			exit(0);
		}
		
		// Waits for children to terminate
		wait(NULL);
	}
	return 0;
}


