#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    pid_t pid = 0, pid2 = 0;
    int child_status;
    int tokenNum = 0;
    char *tokens[10];
	int i;
    for(i = 0; i < 10; i++) tokens[i] = NULL;
    tokenNum = 2;
    char *command = "../pmbench/pmbench";
    char *duration = "60";
    tokens[0] = command;
    tokens[1] = duration;
   
    //DEBUG  
    printf("tokenNum %d\n", tokenNum);
    for(i = 0; i < tokenNum; i++){
        printf("i %d : token %s\n", i, tokens[i]);
    }

    pid = fork();
    if(pid > 0){
        pid2 = fork();
    }
    if(pid2 == 0){
        pid = 0;
    }
    if(pid == 0){
        //2 children
        if(execve(tokens[0], &tokens[0], NULL) < 0){
            printf("Command not found\n");
            exit(1);
        }
    }
    else if (pid > 0){
        wait(&child_status); 
        wait(&child_status); 
    }
    else{
        printf("Error while forking\n");
    }

    return 0;
}
