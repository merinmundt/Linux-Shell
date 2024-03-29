#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h>
 
//#include<readline/readline.h> 
//#include<readline/history.h> 
#include <stdbool.h> 
#include <dirent.h>

#define MAXARGS 64

//This program is the program I gwrote that is a standard shell that implements the commands
//within the exec family of functions others
// along with extra things such as pipes, reading from a file, multiple commands and arguments
//@author Merin Mundt



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

//This function pauses the program until enter is pressed
//There are no parameteres
//There are no return values
void pauseFunc(){
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
        char* arguments[MAXARGS];
        char* more[1000];
        char* nullptr = NULL;
        int i = 0;
        char* tempString = (char*) malloc(sizeof(input));
        strcpy(tempString, input);
        bool com7t12 = false;
        bool com0t6 = false;
        bool background = false;
        bool pipes = false;
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
                //printf("%s", commands[0]); 
        }
        
        //separating commands from arguments 
        for(int j = 0; j < i; j++){
                char* tempArg = (char*) malloc(sizeof(1000000));

                //this is the line that give the abort trap 6 error
                strcpy(tempArg, commands[j]);

                int count = 0;
                com7t12 = false;
                com0t6 = false;

                while((arguments[count] = strtok_r(tempArg, " \n\t", &tempArg))){
                        
                        count++;
                        
                       
                }
                
                //checking if it is a program name
                if(fileExists(arguments[0]) == 1){
                        FILE *file;
                        FILE *fPtr;
                        size_t len = 0;
                        char *line; 
                        ssize_t read;
                        char* inputfile = arguments[count -3];
                        char* outputfile = arguments[count-1];
                        // if(fileExists(outputfile) == 0){
                        //         fPtr = fopen("Linux-Shell/outputfile.txt", "w");
                        // }
                        printf("%s", inputfile);
                        if((file = fopen(inputfile, "r")) != NULL){
                                while((read = getline(&line, &len, file)) != -1){
                                        parseLine(line);
                                }
                                if(strcmp(arguments[count-2], ">")== 0){
                                        freopen("outputfile.txt", "a+", stdout);
                                }else if(strcmp(arguments[count-2], ">>")== 0){
                                        freopen("outputfile.txt", "a+", stdout);
                                }else if(strcmp(arguments[count-2], "dir")== 0){//not sure what to do with internal commands

                                }else if(strcmp(arguments[count-2], "echo")== 0){

                                }else if(strcmp(arguments[count-2], "environ")== 0){

                                }else if(strcmp(arguments[count-2], "help")== 0){

                        }
                                fclose(file);
                        }
                        else{
                                printf("file DNE");
                        }
                       

                }

                //checking if the commands should be run by execvp()./myshell
                if(arguments[0] == command[7] || command[8] || command[9] || command[10] || command[11] || command[12]){
                        com7t12 = true;
                        
                }
                
                if(strcmp(arguments[0], "quit\n")== 0){
                        return;
                }

                //checking if program should be run in the background
                if(strcmp(arguments[count -1], "&") == 0){
                        background = true;
                        //this line can be uncommented, and will create a seg fault
                        //arguments[count-1] = (char*) NULL;
                        
        
                }
                
                
                //checkign if commands are 
                if(arguments[0] == command[0] || command[1] || command[2] || command[3] || command[4] || command[5] || command[6]){
                        com0t6 = true;
                        if(strcmp(arguments[0], "cd") == 0){
                                
                                if(arguments[1] == NULL){
                                        printf("%s\n",getDir());
                                }
                                else{   
                                        chdir(arguments[1]);
                                        return;
                                }
                                
                        } else if(strcmp(arguments[0], "clr") == 0){
                                
                                printf("\033[H\033[J");
                                
                        } else if(strcmp(arguments[0], "dir") == 0){
                                char* old = getDir();
                                //checking if there is an arguments after dir
                                if(arguments[1] == NULL){
                                        
                                        printf("no directory specified");
                                }
                                else{   
                                        chdir(arguments[1]);
                                        system("ls");
                                        chdir(old);

                                }
                                
                        } else if(strcmp(arguments[0], "environ") == 0){
                                system("env");
                        
                        } else if(strcmp(arguments[0], "echo") == 0){
                                int i = 1;
                                while(arguments[i] != NULL){
                                        
                                        i++;
                                }

                        } else if(strcmp(arguments[0], "help") == 0){
                               for(int i = 0; i < 13; i++){
                                       printf("%s\n", command[i]);
                               }
                               if(fork() == 0){
                                       execvp(more[0], more); 
                               }
                        } else if(strcmp(arguments[0], "pause") == 0){
                                pauseFunc();
                        }

                }
                int m = 0;

                if(strcmp(arguments[count-1], "|") == 0){
                        pipes = true;
                        com7t12 = true;
                        arguments[count-1] = (char*) NULL;
                        //printf("here");
                }
                      
                
                //running execvp on the certain functions that are apart of the the exec family of functions
                if(com7t12){
                        int pipes1[2];
                        pipe(pipes1); 
                        //printf("%d", pipes);
                        if(fork() == 0){
                                //printf("here");

                                if(pipes){
                                        printf("here");
                                        //arguments[m] = (char*) NULL;
                                        close(STDOUT_FILENO);
                                        dup(pipes1[1]);
                                        close(pipes1[0]);
                                        close(pipes1[1]);
                                        const char* args[] = {"/bin/ls", NULL};
                                        printf("%s", args[0]);
                                        execvp(args[0], (char**) args);
                                        
                                        if(fork() == 0){
                                                close(STDIN_FILENO);
                                                dup(pipes1[0]);
                                                close(pipes1[0]);
                                                close(pipes1[1]);
                                                const char* more[] = {"/bin/more", NULL};
                                                execvp(more[0], (char**) more);
                                            
                                        }
                                        wait(NULL);
                                }
                                else{   
                                        
                                        execvp(arguments[0], arguments);
                                        
                                                                      
                                }
                        } 
                        else{
                                //printf("here");

                                if(background == true){
                                        background = false;
                                }
                                else{
                                        wait(NULL);    
                                }
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
        //fgets(line, )
        while(strcmp(line = readInput(), "quit\n") != 0){
                if (strcmp(line, "\n") != 0) {
                       
                        parseLine(line); 
                        
                }         
                printf("\n%s/myshell>:", getDir());

        }
}

//main function, start the shell programs
//No parameters
//No return value
int main(int argc, char *argv[]){
        if(argc > 1){
                FILE *file;
                char *line = NULL;
                size_t len = 0;
                ssize_t read; 
                if((file = fopen(argv[1], "r")) != NULL){
                        while((read = getline(&line, &len, file)) != -1){
                                parseLine(line);
                        }
                        fclose(file);
                }
                else{
                        printf("file DNE");
                }

        }
        else{
                promptShell();
        }
        

}