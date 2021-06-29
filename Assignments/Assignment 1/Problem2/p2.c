#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1

int main() {
	char write_msgAB[BUFFER_SIZE];
	char read_msgAB[BUFFER_SIZE];
	char write_msgBA[BUFFER_SIZE];
	char read_msgBA[BUFFER_SIZE];
	char write_msgBC[BUFFER_SIZE];
	char read_msgBC[BUFFER_SIZE];
	char write_msgCB[BUFFER_SIZE];
	char read_msgCB[BUFFER_SIZE];

	int AB[2];
	int BA[2];
	int BC[2];
	int CB[2];

    pid_t pidB;
    pid_t pidC;
    /* create the 4 pipes; A->B, B->A, B->C and C->B*/
    if (pipe(AB) == -1) {
        fprintf(stderr,"Pipe failed");
        return 1;
    }
    if (pipe(BA) == -1) {
        fprintf(stderr,"Pipe failed");
        return 1;
    }
    if (pipe(BC) == -1) {
        fprintf(stderr,"Pipe failed");
        return 1;
    }
    if (pipe(CB) == -1) {
        fprintf(stderr,"Pipe failed");
        return 1;
    }

    /* now fork a child process (Process B forked) */
    pidB = fork();
    if (pidB < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    }
    if (pidB > 0) {  /* parent process (Process A)*/
        /* close the unused end of the pipe */
        close(AB[READ_END]);

        /* write to the pipe */
        struct timeval t1;
        time_t currentTime;
        gettimeofday(&t1, NULL);
        currentTime=t1.tv_sec;
        strftime(write_msgAB,30,"%m-%d-%Y  %T.",localtime(&currentTime));

        printf("Process A is writing the pipe A->B\n");
        write(AB[WRITE_END], write_msgAB, strlen(write_msgAB)+1);
        /* close the write end of the pipe */
        close(AB[WRITE_END]);

        read(BA[READ_END], read_msgBA, BUFFER_SIZE);
        printf("Process A reads: %s\n",read_msgBA);
        kill(pidB,SIGKILL);
    }
    else { /* child process (Process B)*/
        /* close the unused end of the pipe */
        close(AB[WRITE_END]);
        
        /* read from the pipe */
        read(AB[READ_END], read_msgAB, BUFFER_SIZE);
        printf("Child B reads: %s\n",read_msgAB);
        sleep(3);

        pidC = fork();
        if (pidC < 0) {
            fprintf(stderr, "Fork failed");
            return 1;
        }
        if (pidC > 0) {  /* parent process (Process B) */
            /* close the unused end of the pipe */
          	close(BC[READ_END]);

            /* write to the pipe */
            struct timeval t2;
            time_t curentTime2;
            gettimeofday(&t2, NULL);
            curentTime2=t2.tv_sec;
            strftime(write_msgBC,30,"%m-%d-%Y  %T.",localtime(&curentTime2));
            printf("B is writing the time to pipe B->C\n");
            write(BC[WRITE_END], write_msgBC, strlen(write_msgBC)+1);
            /* close the write end of the pipe */
            close(BC[WRITE_END]);

            read(CB[READ_END], read_msgCB, BUFFER_SIZE);
            printf("Child B read %s\n",read_msgCB);
            sleep(3);

            struct timeval tv3;
            time_t curentTime3;
            gettimeofday(&tv3, NULL);
            curentTime3=tv3.tv_sec;
            strftime(write_msgBA,30,"%m-%d-%Y  %T.",localtime(&curentTime3));
            printf("B is writing the time to pipe B->A\n");
            write(BA[WRITE_END], write_msgBA, strlen(write_msgBA)+1);
            kill(pidC,SIGKILL);

        } else {
            /* read from the pipe */
            read(BC[READ_END], read_msgBC, BUFFER_SIZE);
            printf("Child C read %s\n",read_msgBC);
            sleep(3);

            struct timeval t4;
            time_t curentTime4;
            gettimeofday(&t4, NULL);
            curentTime4=t4.tv_sec;
            strftime(write_msgCB,30,"%m-%d-%Y  %T.",localtime(&curentTime4));
            printf("C is writing the time to pipe\n");
            write(CB[WRITE_END], write_msgCB, strlen(write_msgCB)+1);
        }
        /* close the write end of the pipe */
        close(AB[READ_END]);
    }
    exit(0);



}
