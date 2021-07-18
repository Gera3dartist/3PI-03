#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#define CMD_LENGTH 128

typedef struct { 
    unsigned int pid;
    char * cmd[CMD_LENGTH];
} ProcData;

static volatile int shouldRun = 1;

void cancellHandler(int dummy) {
    shouldRun = 0;
}

void list_processes();

int main()
{
    int choice, shouldStop = 0;
    int pid;
    while (shouldRun) {
        printf("1. Disk check\n");
        printf("2. List of processes \n");
        printf("3. Kill process \n");
        printf("\n\n\nEnter your choice\t:\t");
 
        scanf("%d", &choice);
 
        switch (choice) {
            case 1:
                printf("do disk check");
                break;
            case 2:
                list_processes();
                printf("do process list check");
                break;
            case 3:
                printf("Provide process id: \n");
                scanf("%d", &pid);
                kill(pid, SIGKILL);
                break;
            default:
                printf("\nInvalid Choice :-(\n");
                system("read -p \"Press enter to continue\"");
                shouldStop = 1;
        }
        if (shouldStop == 1) break;
    }
    
    
    return 0;
}

void list_processes() {
    FILE *fp;
    char path[1035];
    
    fp = popen("/bin/ps -o pid,command", "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(path, sizeof(path), fp) != NULL) {
        printf("%s", path);
    }
    pclose(fp);
}
