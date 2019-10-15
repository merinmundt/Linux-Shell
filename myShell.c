#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 

//This functions gets the current directory
//There are no parameters
//The return value is the char pointer that holds the current working directory path
 char* getDir(){
        size_t size = 256;
        char *cwd = malloc(256 * sizeof(char));
        getcwd(cwd, size ); 
        return cwd;     
}


//This function will get the commands from the user, and process them
//There are no parameters
//There return value is the variable holding the user input from the command line
char* readInput(){
        char* input = NULL; 
        size_t size = 0;
        //char size[1024];
        getline(&input, &size, stdin);
        return input;
}

//This function will parse the user input line and send it to the program that will execute the instruction
//The parameter being passed in is the line that the user has entered into the shell command linfe
//There are no return values
void parseLine(char* input){
        char* token;
        char** commands;
        int i = 0;

        //separating commands from semicolons
        while((token = strtok(input, ";")) != NULL){
              commands[i] = token;
              i++;  
        }
        printf("%s", &input);
        //separating arguments by spaces
        while((token = strtok(input, " \n\t")) != NULL){
                
        }

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