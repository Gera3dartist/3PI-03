#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLENGTH 32 


typedef struct { 
    char city[MAXLENGTH];
    char street[MAXLENGTH];
    char apt_number[MAXLENGTH];
    char name[MAXLENGTH];
    char last[MAXLENGTH];
    char surname[MAXLENGTH];
    unsigned int medical_card_num;
    unsigned int insurance_policy_num;
} Patient;



typedef struct Node {
    Patient info;
    struct Node *next;

} Node;

// Public API single linked list
void removeNode(char *info, Node **list);
void saveToFile(FILE *fp, Node **list);
void insertNode(Node *node, Node **head);
Node *editNode(Patient *new_info, char *last, Node **list);
Node *searchNode(char *last, Node **list);
Node *loadFromFile(FILE *fp);



void printList(Node **list);
void printNode(Node *list);
Node *createNode(
    char *name, char *last, char *surname, char *city, 
    char *street, char *apt_number, int medical_card_num, int insurance_policy_num);
void freeLinkedList(Node** list);
Patient *createPatient(char *name, char *last, char *surname, char *city, 
    char *street, char *apt_number, int medical_card_num, int insurance_policy_num);
void printPatient(Patient *employee);
int item_found (Node *node, char * query);

int main() {
    Node *list = NULL, *single, *tmp, *result;
    Patient *new_emp_data;
    char search_query[30];
    FILE *output;
    printf("so far so good\n");

    // Додаєм елементи у список
    insertNode(createNode("Name1", "Lname1", "Sname1", "Kyiv", "street1", "43/5", 200, 2001), &list);
    insertNode(createNode("Name2", "Lname2", "Sname2", "Kyiv", "street2", "42/5", 202, 2003), &list);
    insertNode(createNode("Name3", "Lname3", "Sname3", "Kyiv", "street3", "44/5", 204, 2004), &list);



    // Видалення, пошук, редагування, працює по прізвищах

    strcpy(search_query, "Lname3");
    new_emp_data = createPatient(NULL, NULL, NULL, NULL, NULL, NULL, 102, 3002);
    editNode(new_emp_data, search_query, &list);
    free(new_emp_data);
    removeNode("Lname3", &list);
    
    printf(" ------Список до вивантаження у файл ------\n");
    printList(&list);

    output = fopen("patient_linked_list.dat", "wb");
    saveToFile(output, &list);
    fclose(output);

    output = fopen("patient_linked_list.dat", "rb");
    result = loadFromFile(output);

    printf("\n------ Список після читання з файлу ------\n");
    printList(&result);

    fclose(output);
    freeLinkedList(&list);
    freeLinkedList(&result);
    return 0;
}

void printList(Node **list) {
    Node *current = (*list);
    if (current == NULL) {
        printf("Порожній список \n");
        return;
    }
    while (current != NULL)
    {

        printNode(current);
        current = current->next;
    }

}

void printNode(Node *node) {
    if (node == NULL) printf("Not found\n");
    else {
        printf("\n=========================\n");
        printPatient(&(node->info));
    }
}

void printPatient(Patient *patient) {
    printf("Iм'я: %s\n", patient->name);
    printf("Прізвище: %s\n", patient->last);
    printf("По-батькові: %s\n", patient->surname);
    printf("Місто: %s\n", patient->city);
    printf("Вулиця: %s\n", patient->street);
    printf("Номер помешканя: %s\n", patient->apt_number);
    printf("Номер медичної карти: %d\n", patient->medical_card_num);
    printf("Номер страхового поліса: %d\n", patient->insurance_policy_num);

}

Node *createNode(
    char *name, char *last, char *surname, char *city, 
    char *street, char *apt_number, int medical_card_num, int insurance_policy_num) 
{
    Node *node = (Node *)malloc(sizeof(Node));
    strcpy(node->info.name, name);
    strcpy(node->info.last, last);
    strcpy(node->info.surname, surname);
    strcpy(node->info.city, city);
    strcpy(node->info.street, street);
    strcpy(node->info.apt_number, apt_number);

    node->info.medical_card_num = medical_card_num;
    node->info.insurance_policy_num = insurance_policy_num;
    node->next = NULL;
    return node;
}

Patient *createPatient(char *name, char *last, char *surname, char *city, 
    char *street, char *apt_number, int medical_card_num, int insurance_policy_num) {
    Patient *patient = (Patient *)malloc(sizeof(Patient));
    if (name != NULL) strcpy(patient->name, name);
    if (last != NULL) strcpy(patient->last, last);
    if (surname != NULL) strcpy(patient->surname, surname);
    if (city != NULL) strcpy(patient->city, city);
    if (street != NULL) strcpy(patient->street, street);
    if (apt_number != NULL) strcpy(patient->apt_number, apt_number);
    if (medical_card_num > 0) patient->medical_card_num = medical_card_num;
    if (insurance_policy_num > 0) patient->insurance_policy_num = insurance_policy_num;

    return patient;
}

// PUBLIC API
Node *searchNode(char *last, Node **list) {
    if ((*list) == NULL) return NULL;
    if (strcmp((*list)->info.last, last) == 0) {
        return (*list);
    }
    return searchNode(last, &((*list)->next));
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

Node *editNode(Patient *new, char *last, Node **list) {
    Node *node;
    if ((node = searchNode(last, &(*list)))!= NULL){
        if (strcmp(new->city, "\0") != 0)
            strcpy(node->info.city, new->city);
        if (strcmp(new->street, "\0") != 0)
            strcpy(node->info.street, new->street);
        if (strcmp(new->apt_number, "\0") != 0)
            strcpy(node->info.apt_number, new->apt_number);
        if (strcmp(new->name, "\0") != 0)
            strcpy(node->info.name, new->name);
        if (strcmp(new->last, "\0") != 0)
            strcpy(node->info.last, new->last);
        if (strcmp(new->surname, "\0") != 0)
            strcpy(node->info.surname, new->surname);
        if (new->medical_card_num != node->info.medical_card_num)
            node->info.medical_card_num = new->medical_card_num;
        if (new->insurance_policy_num != node->info.insurance_policy_num)
            node->info.insurance_policy_num = new->insurance_policy_num;
        return node;
    }
    return NULL;
}

void removeNode(char *info, Node **list) {
    Node *cursor, *new_next;

    cursor = (*list);
    if (cursor == NULL) {
        return;
    }
    if (strcmp(cursor->info.last, info) == 0) {
        free((*list));
        (*list) = cursor->next;
        return;
    }

    while (cursor != NULL)
    {
        if (cursor->next == NULL && item_found(cursor, info) == 0) {
            free(cursor);
            cursor = NULL;
            break;
        }

        if (item_found(cursor->next, info) == 0) {
            new_next = cursor->next->next;
            free(cursor->next);
            cursor->next = new_next;
            break;
        }
        cursor = cursor->next;
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

void saveToFile(FILE *fp, Node **list) 
{
    Node *current = (*list);
    if (current == NULL) {
        return;
    }
    while (current != NULL)
    {   
        fwrite(current, sizeof(Node), 1, fp);
        current = current->next;
    }
}

Node *loadFromFile(FILE *fp) {
    Node *head, *current, *temp = NULL;
    head = (Node*) malloc(sizeof(Node));
    current = head;
    while (fread(current, sizeof(Node), 1, fp) == 1) {
        if (temp != NULL) {
            temp->next = current;
        }
        temp = current;
        current = (Node*) malloc(sizeof(Node));
    }
    current->next = NULL;
    return head;
}

int item_found (Node *node, char * query) {
    return strcmp(node->info.last, query);
}
