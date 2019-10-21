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

//This fuction returns whether the file/directory exists
//Parameters is the file path
//The return value is 0 is the file does not exist & 1 if the file dodes exits
int fileExists(char* path){
        FILE *fptr = fopen(path, "r");
        if(fptr == NULL){
                return 0;
        }
        fclose(fptr);
        return 1;
}

void pause(){
        fflush(stdin);
        printf("Press [Enter] key to continue.\n");
        while(getchar() != '\n'){
                getchar();
        }
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
        char* commands[1000];
        char* arguments[1000];
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
                printf("gothere");
                char* tempArg = (char*) malloc(sizeof(1000000));
                printf("got here 1");
                strcpy(tempArg, commands[j]);
                printf("got here2");
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
                                if(arguments[1] == NULL){
                                        printf("%s\n",getDir());
                                }
                                else{
                                        chdir(arguments[1]);
                                }
                                //printf("%s %s", arguments[0], command[0] );
                        } else if(strcmp(arguments[0], "clr") == 0){
                                n = 1;
                                printf("\033[H\033[J");
                                //printf("%s %s", arguments[0], command[1] );

                        } else if(strcmp(arguments[0], "dir") == 0){
                                n = 2;
                                char* path;
                                printf("%s %s", arguments[0], arguments[1] );
                                char* old = getDir();
                                //checking if there is an arguments after dir
                                if(arguments[1] == NULL){
                                        
                                        printf("no directory specified");
                                }
                                else{   //checking if the file exist
                                        //path = ("%s/%s", getDir(), arguments[1]); 
                                        int ans = fileExists(path);
                                        if(ans == 1){
                                                printf("file exists");
                                                arguments[0] = "ls";
                                                com7t12 = true;
                                                chdir("..");
                                        }
                                        if (ans == 0){
                                                printf("file does not exist");
                                        }
                                        
                                }
                                
                        } else if(strcmp(arguments[0], "environ") == 0){
                                n = 3;

                        } else if(strcmp(arguments[0], "echo") == 0){
                                n = 4;
                                int i = 1;
                                while(arguments[i] != NULL){
                                        printf("%s this is echo ", arguments[i]);
                                        i++;
                                }

                        } else if(strcmp(arguments[0], "help") == 0){
                                n = 5;
                        } else if(strcmp(arguments[0], "pause") == 0){
                                n = 6;
                                pause();
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