#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MNAME 32
#define PNAME 16

/*
 * Вивчити і реалізувати механізми 
 *    + додавання нових записів у список, 
 *    + пошуку записів у списку за певними полями, 
 *    + видалення записів зі списку
 *    + редагування знайдених записів, 
 *    + збереження всього списку у файлі
 *    + зчитування списку із файлу до пам’яті з відновленням всіх зв’язків.
 *    
 * Матеріали:
 * https://www.zentut.com/c-tutorial/c-linked-list/
 * https://en.wikipedia.org/wiki/Linked_list
 */


typedef struct { 
    char first[MNAME];
    char last[MNAME];
    char surname[MNAME];
} PersonalInfo;

typedef struct { 
    PersonalInfo personal;
    char position[PNAME];
    float salary;
} Employee;

typedef struct Node {
    Employee info;
    struct Node *next;

} Node;

// Public API single linked list

void add_item(Node *node, Node **head);
Node *edit_item(Employee *new_info, char *last, Node **list);
void remove_item(char *info, Node **list);
void dump_into_file(FILE *fp, Node **list);
Node *search_item(char *last, Node **list);
Node *load_list_from_file(FILE *fp);


// utilities
void _edit_item(Employee *new_data, Node *node);
void print_list(Node **list);
void print_node(Node *list);
Node *create_node(char *first, char *last, char *surename, char *position, int salary);
void free_list(Node** list);
Employee *create_employee(char *first, char *last, char *surename, char *position, float salary);
void print_empoyee(Employee *employee);
int item_found (Node *node, char * query);

int main() {
    Node *list = NULL, *single, *tmp, *result;
    Employee *new_emp_data;
    char search_query[30];
    FILE *output;

    // Демонстрація API
    // Додавання елементів у список
    add_item(create_node("Василь", "Кук", "Васильович", "Генерал", 100), &list);
    add_item(create_node("Тарас", "Шевченко", "Григорович", "Поет", 110), &list);
    add_item(create_node("Микола", "Міхновський", "Іванович", "адвокат", 108), &list);
    add_item(create_node("Foo", "BAR", "BAR", "bar", 10), &list);

    // Видалення, пошук, редагування, працює по прізвищах

    strcpy(search_query, "Міхновський");
    new_emp_data = create_employee(NULL, NULL, NULL, NULL, 1000);
    edit_item(new_emp_data, search_query, &list);
    free(new_emp_data);
    remove_item("BAR", &list);
    
    printf(" ------Список до вивантаження у файл ------\n");
    print_list(&list);

    output = fopen("single_linked_list.dat", "wb");
    dump_into_file(output, &list);
    fclose(output);

    output = fopen("single_linked_list.dat", "rb");
    result = load_list_from_file(output);

    printf("\n------ Список після завантаження з файлу ------\n");
    print_list(&result);

    fclose(output);
    free_list(&list);
    free_list(&result);
    return 0;
}

void print_list(Node **list) {
    Node *current = (*list);
    if (current == NULL) {
        printf("Порожній список \n");
        return;
    }
    while (current != NULL)
    {
        print_node(current);
        current = current->next;
    }

}

void print_node(Node *node) {
    if (node == NULL) printf("Not found\n");
    else {
        print_empoyee(&(node->info));
    }
}

void print_empoyee(Employee *employee) {
    printf("\n -------------------- \n");
    printf("Iм'я: %s\n", employee->personal.first);
    printf("Прізвище: %s\n", employee->personal.last);
    printf("По-батькові: %s\n", employee->personal.surname);
    printf("Посада: %s\n", employee->position);
    printf("Заробітна плата: %.2f\n", employee->salary);
}

Node *create_node(char *first, char *last, char *surename, char *position, int salary) {
    Node *node = (Node *)malloc(sizeof(Node));
    strcpy(node->info.personal.first, first);
    strcpy(node->info.personal.last, last);
    strcpy(node->info.personal.surname, surename);
    strcpy(node->info.position, position);
    node->info.salary = salary;
    node->next = NULL;
    return node;
}

Employee *create_employee(char *first, char *last, char *surname, char *position, float salary) {
    Employee *employee = (Employee *)malloc(sizeof(Employee));
    if (first != NULL) strcpy(employee->personal.first, first);
    if (last != NULL) strcpy(employee->personal.last, last);
    if (surname != NULL) strcpy(employee->personal.surname, surname);
    if (position != NULL) strcpy(employee->position, position);
    if (salary > 0) employee->salary = salary;

    return employee;
}

// PUBLIC API
Node *search_item(char *last, Node **list) {
    if ((*list) == NULL) return NULL;
    if (strcmp((*list)->info.personal.last, last) == 0) {
        return (*list);
    }
    return search_item(last, &((*list)->next));
}

void add_item(Node *node, Node **head) {
    if ((*head) == NULL) {
        (*head) = node;
    } else {
        Node *current = (*head);

        while (current->next != NULL) 
            current = current->next;
        current->next = node;
    }
}

void _edit_item(Employee *new_data, Node *node) {
    if (strcmp(new_data->personal.first, "\0") != 0) strcpy(node->info.personal.first, new_data->personal.first);
    if (strcmp(new_data->personal.last, "\0") != 0) strcpy(node->info.personal.last, new_data->personal.last);
    if (strcmp(new_data->personal.surname,  "\0") != 0) strcpy(node->info.personal.surname, new_data->personal.surname);
    if (strcmp(new_data->position,  "\0") != 0) strcpy(node->info.position, new_data->position);
    if (new_data->salary != node->info.salary) node->info.salary = new_data->salary;
}

Node *edit_item(Employee *new_info, char *last, Node **list) {
    Node *node;
    if ((node = search_item(last, &(*list)))!= NULL){
        _edit_item(new_info, node);
        return node;
    }
    return NULL;
}

void remove_item(char *info, Node **list) {
    Node *cursor, *new_next;

    cursor = (*list);
    if (cursor == NULL) {
        return;
    }
    // edge case: only single node in list
    if (strcmp(cursor->info.personal.last, info) == 0) {
        free((*list));
        (*list) = cursor->next;
        return;
    }

    while (cursor != NULL)
    {
        // last node in list
        if (cursor->next == NULL && item_found(cursor, info) == 0) {
            printf(">>>>HERE");
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

void free_list(Node **list)
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

void dump_into_file(FILE *fp, Node **list) 
{
    Node *current = (*list);
    if (current == NULL) {
        printf("Empty list.\n");
        return;
    }
    while (current != NULL)
    {   
        fwrite(current, sizeof(Node), 1, fp);
        current = current->next;
    }
}

Node *load_list_from_file(FILE *fp) {
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
    return strcmp(node->info.personal.last, query);
}
