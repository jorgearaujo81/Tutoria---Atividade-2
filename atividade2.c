#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define QTD_MESSAGES 2

int main() {
    int pipeFileDescriptors[2];
    int returnStatus;
    char writeMessages[QTD_MESSAGES][20] = {"Maria", "Joao andou a noite"};
    char readMessages[20];
    memset(readMessages, '\0', sizeof(char) * 20);

    returnStatus = pipe(pipeFileDescriptors);

    if (returnStatus == -1) {
        printf("Error when create pipe\n");
        
        return 1;
    }

    pid_t pid;
    pid = fork();  
    if (pid != 0){
        for (int i = 0; i < QTD_MESSAGES; i++) {
            printf("\nWriting Message %d is %s\n", i+1, writeMessages[i]);
            write(pipeFileDescriptors[1], writeMessages[i], sizeof(char) * 20);
        }
    }else{
        for (int i = 0; i < QTD_MESSAGES; i++) {
            read(pipeFileDescriptors[0], readMessages, sizeof(char) * 20);
            printf("\nReading Message %d is %s\n", i+1, readMessages);
        }
    }
    
    return 0;
}