#include <stdio.h>

//This function initializing the shell and prompting the user to enter their commands
//There are no parameters
//There are no return values
void promptShell(){
        char* curDir = getDir();
        printf("Hello! Welcome to myshell!\n\n\n");
        printf("Please enter your commands:\n");

        readInput();
}

//This functions gets the current directory
 char* getDir(){
    char cwd[1024]; 
    getcwd(cwd, sizeof(cwd)); 
    return cwd;
}

//This function will get the commands from the user, and process them
//There are no parameters
//There are no return values
void readInput(){
        char* input;
        //getline(input, )
   
}



int main(){
    
    promptShell();

}