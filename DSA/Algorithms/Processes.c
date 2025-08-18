#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROCESS_NUM 10

int main(int argc, char* argv[]) {
    int pids[PROCESS_NUM];  //arr of processes
    int pipes[PROCESS_NUM + 1][2]; //pipes 10 + 1 because of the parent process
    int i;
    for (i = 0; i < PROCESS_NUM + 1; i++) { //creating pipes
        if (pipe(pipes[i]) == -1) {
            printf("Error with creating pipe\n");
            return 1;
        }
    }

    for (i = 0; i < PROCESS_NUM; i++) {  //creating processes
        pids[i] = fork();
        if (pids[i] == -1) {
            printf("Error with creating process\n");
            return 2;
        }
        //Childs
        if (pids[i] == 0) {
            // Child process
            int j;
            for (j = 0; j < PROCESS_NUM + 1; j++) {
                if (i != j) {
                    close(pipes[j][0]); //close all read read pipes of the other processes except the current
                }
                if (i + 1 != j) {       //the same but with read
                    close(pipes[j][1]);
                }
            }
            int x;
            if (read(pipes[i][0], &x, sizeof(int)) == -1) { //read from the current process
                printf("Error at reading\n");
                return 3;
            }
            printf("(%d) Got %d\n", i, x);
            x++;
            if (write(pipes[i + 1][1], &x, sizeof(int)) == -1) { //write to the next process
                printf("Error at writing\n");
                return 4;
            }
            printf("(%d) Sent %d\n", i, x);
            close(pipes[i][0]);  //close read end
            close(pipes[i + 1][1]);  //close write end of the next process
            return 0;
        }
    }

    // Main process
    int j;
    for (j = 0; j < PROCESS_NUM + 1; j++) {
        if (j != PROCESS_NUM) {
            close(pipes[j][0]); //closes all other pipes execept the last read
        }
        if (j != 0) {  //except the write for the parent process
            close(pipes[j][1]);
        }
    }
    int y = 5;
    printf("Main process sent %d\n", y);
    if (write(pipes[0][1], &y, sizeof(int)) == -1) { //write 5 to the pipe
        printf("Error at writing\n");
        return 4;
    }
    if (read(pipes[PROCESS_NUM][0], &y, sizeof(int)) == -1) { //read from the last process
        printf("Error at reading\n");
        return 3;
    }
    printf("The final result is %d\n", y);
    close(pipes[0][1]); //close last pipes
    close(pipes[PROCESS_NUM][0]);

    for (i = 0; i < PROCESS_NUM; i++) { //wait for all processes
        wait(NULL);
    }

    //Other stuff
    int omega;
    printf("Choose 1 or 0? ");
    scanf("%d",&omega);
    if(omega == 1){
       
        // Execute external processes

        // Without specifying environment variables and using PATH
        execlp("ping", "ping", "google.com", NULL); // Use PATH to find ping executable

        // With specifying environment variables and using PATH
        char* env[] = {
            "TEST=environment variables",
            NULL
        };
    };
    
    return 0;
}
