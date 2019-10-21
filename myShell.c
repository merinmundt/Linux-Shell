#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 
#include <stdbool.h> 
#include <dirent.h>



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
//The parameter being passed in is the line that the user has entered into the shell command linee
//There are no return values
void parseLine(char* input){
        char* token;
        char* commands[40];
        char* arguments[40];
        int i = 0;
        char* tempString = (char*) malloc(sizeof(input));
        strcpy(tempString, input);
        bool com7t12 = false;
        bool com0t6 = false;
        int n = -1;

        //char array to hold the commands
        char* command[13];
        command[0] = "cd";
        command[1] = "clr";
        command[2] = "dir";
        command[3] = "environ";
        command[4] = "echo";
        command[5] = "help";
        command[6] = "pause";
        command[7] = "date";
        command[8] = "who";
        command[9] = "cal";
        command[10] = "ls";
        command[11] = "ps";
        command[12] = "time";

        //separating commands from semicolons
        while((commands[i] = strtok_r(tempString, ";", &tempString))) {
                
                i++;  
        }

        //separating commands from arguments 
        for(int j = 0; j < i; j++){
                char* tempArg = (char*) malloc(sizeof(commands[j]));
                strcpy(tempArg, commands[j]);
                int count = 0;
                com7t12 = false;
                com0t6 = false;
                while((arguments[count] = strtok_r(tempArg, " \n\t", &tempArg))){
                        count++;
                }
                //checking if the commands should be run by execvp()./myshell
                if(arguments[0] == command[7] || command[8] || command[9] || command[10] || command[11] || command[12]){
                        com7t12 = true;
                }
                
                if(strcmp(arguments[0], "quit\n")== 0){
                        return;
                }
                //checkign if commands are 
                if(arguments[0] == command[0] || command[1] || command[2] || command[3] || command[4] || command[5] || command[6]){
                        com0t6 = true;
                        if(strcmp(arguments[0], "cd") == 0){
                                n = 0;
                                
                                //printf("%s %s", arguments[0], command[0] );
                        } else if(strcmp(arguments[0], "clr") == 0){
                                n = 1;
                               
                                //printf("%s %s", arguments[0], command[1] );

                        } else if(strcmp(arguments[0], "dir") == 0){
                                n = 2;
                                //printf("%s %s", arguments[0], command[2] );

                                //printf("got here also");
                        } else if(strcmp(arguments[0], "environ") == 0){
                                n = 3;
                        } else if(strcmp(arguments[0], "echo") == 0){
                                n = 4;
                        } else if(strcmp(arguments[0], "help") == 0){
                                n = 5;
                        } else if(strcmp(arguments[0], "pause") == 0){
                                n = 6;
                        }
                }
        }
        //running execvp on the certain functions that are apart of the the exec family of functions
        if(com7t12){
                if(fork() == 0){
                        execvp(arguments[0], arguments);
                }
                        
                else{
                        wait(NULL);
                }
        }
        //sendign the rest of the commands to their specific programs that will execute the command
        if(com0t6){
                
                switch(n){
                        case 0: //cd
                                if(arguments[1] == NULL){
                                        printf("%s\n",getDir());
                                }
                                else{
                                        chdir(arguments[1]);
                                }
                                break;
                        case 1: //clr
                                printf("\033[H\033[J");
                                break;

                        case 2: //dir <directory>
                                if(arguments[1] == NULL){
                                        printf("No directory specified");
                                }
                                else{
                                        printf("in here");
                                        char *old = getDir();
                                        chdir(arguments[1]);
                                        arguments[1] = "ls";
                                        execvp(arguments[1], arguments);
                                        chdir(old);
                                        
                                }
                                break;

                }
        }
        
}


//This function initializing the shell and prompting the user to enter their commands
//There are no parameters
//There are no return values
void promptShell(){
        printf("%s/myshell>:", getDir());
        char* line = "";
        while(strcmp(line = readInput(), "quit\n") != 0){
                if (strcmp(line, "\n") != 0) {
                        parseLine(line); 
                }         
                printf("\n%s/myshell>:", getDir());

        }
}

//main function
int main(){
    
    promptShell();

}