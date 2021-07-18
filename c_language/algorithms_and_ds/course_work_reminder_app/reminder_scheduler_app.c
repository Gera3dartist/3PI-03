#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

#define MAXLENGTH 32
#define PROCESSING_WORKER_SLEEP 5


typedef struct { 
    char message[MAXLENGTH];
    time_t notify_time;
    int done;
} Reminder;



typedef struct Node {
    Reminder info;
    struct Node *next;
} Node;


void insertNode(Node *node, Node **head);
void removeNode(Node *node, Node **list);
Node *searchNode(time_t notify_time, Node **list);

void printList(Node **list);
void printNode(Node *list);
Node *createNode();

void freeLinkedList(Node** list);
Reminder *createReminder();
void printReminder(Reminder *employee);
void *show_ui(void *list);

void *whatch_for_updates(void *list);


static volatile int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
}


int main()
{   
    Node *list = NULL;
    pthread_t thread1;
    pthread_t thread2;
    insertNode(createNode(), (Node**)&list);

    // Thread for UI
    pthread_create(&thread2, NULL, whatch_for_updates, (void *)list);
    pthread_create(&thread1, NULL, show_ui, (void *)list);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}


void *show_ui(void *list){
    int choice, shouldStop = 0;
    while (keepRunning) {
        printf("1. List scheduled items\n");
        printf("2. Add reminder \n");
        printf("3. Exit\n");
        printf("4. Idle for 10 sec");
        printf("\n\n\nEnter your choice\t:\t");
 
        scanf("%d", &choice);
 
        switch (choice) {
            case 1:
                printList((Node**)&list);
                break;
            case 2:
                insertNode(createNode(), (Node**)&list);
                break;
            case 3:
                system("read -p \"Press enter to continue\"");
                shouldStop = 1;
                break;
            case 4:
                sleep(10);
                break;
            default:
                printf("\nInvalid Choice :-(\n");
                system("read -p \"Press enter to continue\"");
                break;
        }
    if (shouldStop == 1) {
        break;
    }
    }
}


Node *searchNode(time_t notify_time, Node **list) {
    double diff_t;
    
    if ((*list) == NULL) return NULL;
    if (difftime(notify_time, (*list)->info.notify_time) > 0 && (*list)->info.done == 0) 
        return (*list);
    return searchNode(notify_time, &((*list)->next));
}


void printList(Node **list) {
    Node *current = (*list);
    if (current == NULL) {
        printf("Порожній список \n");
        return;
    }
    while (current != NULL)
    {
        if (current->info.done == 0) printNode(current);
        current = current->next;
    }

}

void printNode(Node *node) {
    if (node == NULL) printf("Not found\n");
    else {
        printf("\n=========================\n");
        printReminder(&(node->info));
    }
}

void printReminder(Reminder *reminder) {
    printf("Повідомлення: %s\n", reminder->message);
    printf("Дата: %s\n", asctime(localtime(&reminder->notify_time)));
    printf("Виконана: %d\n", reminder->done);

}

Node *createNode() 
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->info = *(createReminder());
    node->next = NULL;
    return node;
}

Reminder *createReminder() {
    time_t *result;

    char message[MAXLENGTH];
    int size = 0;
    int year = 0, month = 0, day = 0, hour = 0, min = 0;
    Reminder *reminder = (Reminder *)malloc(sizeof(Reminder));
    printf("Specify message: \n");
    scanf("%s", message);

    strcpy(reminder->message, message);
    reminder->done = 0;

    printf("Specify time, when to display message in form: \"YYYY.MM.DD HH:MM\"\n");
    if (scanf("%4d.%2d.%2d %2d:%2d", &year, &month, &day, &hour, &min) == 5) {
        struct tm breakdown = {0};
        breakdown.tm_year = year - 1900;
        breakdown.tm_mon = month - 1;
        breakdown.tm_mday = day;
        breakdown.tm_hour = hour - 1;
        breakdown.tm_min = min;
        result = (time_t *) malloc(sizeof(time_t));
        if ((*(result) = mktime(&breakdown)) == (time_t)-1) {
            fprintf(stderr, "Could not convert to time, try again\n");
        }
        reminder->notify_time = *(result);
        
    }
    return reminder;
}

void insertNode(Node *node, Node **head) {
    if ((*head) == NULL) {
        (*head) = node;
    } else {
        Node *current = (*head);
        while (current->next != NULL) 
            current = current->next;
        current->next = node;
    }
}


void freeLinkedList(Node **list)
{
   Node * tmp;
   while ((*list) != NULL)
   {
       tmp = (*list);
       (*list) = tmp->next;
       tmp->next = NULL;
       free(tmp);
    }
}

void *whatch_for_updates(void *list) {
    time_t rawtime;
    struct tm *timeinfo;
    
    while (keepRunning)
    {
        time(&rawtime);
        Node *candidate = searchNode(rawtime, (Node**)&list);
        if (candidate != NULL) {
            printf("\n>>>>>>>>>> Показую нагадування: <<<<<<<<\n");
            candidate->info.done = 1;
            printNode(candidate);
            printf("\n>>>>>>>>>> Готово <<<<<<<<\n");
            continue;
        }
        sleep(PROCESSING_WORKER_SLEEP);
        
    }
    

}

