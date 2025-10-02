#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROCESS_NUM 10

// Example Programm of some of the multiproccesing functionalities in C 

int main(int argc, char* argv[]) {
    
    int pids[PROCESS_NUM];  //arr of processes ids
    
    // Pipes are a way of comunication between processes. The function pipe() return two file descriptors to 
    // reference a region in memory to write and read data to (int[2]).
    
    int pipes[PROCESS_NUM + 1][2]; //pipes 10 + 1 because of the parent process
    int i;
    
    // Creating pipes
    for (i = 0; i < PROCESS_NUM + 1; i++) {
        if (pipe(pipes[i]) == -1) {
            printf("Error with creating pipe\n");
            return 1;
        }
    }
    
    // Creating different processes which are clones of the current process
    for (i = 0; i < PROCESS_NUM; i++) {
        
        pids[i] = fork();

        // ----------------------- The cloned processes start executing from here ---------------- 
        
        if (pids[i] == -1) {
            printf("Error with creating process\n");
            return 2;
        }
        

        // If the id is not the id of the parent process then 
        // Take a value from one process increment its value and finally give it to the next process    
        if (pids[i] == 0) {

            int j;
           
            for (j = 0; j < PROCESS_NUM + 1; j++) {
                if (i != j) {
                    close(pipes[j][0]);         //close all read-pipes of the other processes except the current
                }
                if (i + 1 != j) {                   //the same but with the write except for the next process
                    close(pipes[j][1]);
                }
            }
            
            int x;

            if (read(pipes[i][0], &x, sizeof(int)) == -1) {    //read from the current process
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
            
            close(pipes[i][0]);      //close read end of the current process 
            
            close(pipes[i + 1][1]);  //close write end of the next process
            
            return 0;
        }
    }

    // Main process
    int j;
    

    for (j = 0; j < PROCESS_NUM + 1; j++) {

        if (j != PROCESS_NUM) {
            close(pipes[j][0]); //closes all read pipes execept the last read
        }
        
        if (j != 0) {               //close all write pipes except for the parent process
            close(pipes[j][1]);
        }
    }
   
    // Procedure for sending the first value 

    int y = 5;

    printf("Main process sent %d\n", y);
    
    if (write(pipes[0][1], &y, sizeof(int)) == -1) { //write value to the next process
        printf("Error at writing\n");
        return 4;
    }
    
    // Read from the last process
    if (read(pipes[PROCESS_NUM][0], &y, sizeof(int)) == -1) { //read from the last process
        printf("Error at reading\n");
        return 3;
    }

    printf("The final result is %d\n", y);
    
    // Clean Up
    close(pipes[0][1]); //close last pipes
    close(pipes[PROCESS_NUM][0]);
    
    //Wait for all processes to do their work. Wait is called after read because the parent 
    //process must first retrieve the result from the pipeline. Also, it has to signalize that it is 
    //expecting some result of the last process because other wise the last child processes will be never 
    //terminate properly because it has no way of sending the data

    for (i = 0; i < PROCESS_NUM; i++) { //wait for all processes
        wait(NULL);
    }

    // --------------  Creating other processes which are not clones  -----------------------
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
