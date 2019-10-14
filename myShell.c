#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 

//This functions gets the current directory
 char* getDir(){
        size_t size = 256;
        char *cwd = malloc(256 * sizeof(char));
        getcwd(cwd, size ); 
        return cwd;     
}


//This function will get the commands from the user, and process them
//There are no parameters
//There are no return values
char* readInput(){
        char* input = NULL; 
        size_t size = 0;
        //char size[1024];
        getline(&input, &size, stdin);
        return input;
}

//This function will parse the user input line
//
//
void parseLine(char* input){


}

//This function initializing the shell and prompting the user to enter their commands
//There are no parameters
//There are no return values
void promptShell(){
        // printf("Hello! Welcome to myshell!\n\n\n");
        // printf("Please enter your commands:\n");
        printf("%s/myshell>:", getDir());
        char* line;
        while(strcmp(line = readInput(), "quit\n") != 0){
                printf("%s/myshell>:", getDir());
                parseLine(line);
        }
}

int main(){
    
    promptShell();

}