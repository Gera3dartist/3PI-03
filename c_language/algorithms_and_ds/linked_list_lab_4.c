#include <stdio.h>
#include <stdlib.h>
#define DATA_LENGTH = 20

/*
 * Вивчити і реалізувати механізми 
 *    + додавання нових записів у список, 
 *    + пошуку записів у списку за певними полями, 
 *    + видалення записів зі списку
 *    + редагування знайдених записів, 
 *    + збереження всього списку у файлі
 *    + зчитування списку із файлу до пам’яті з відновленням всіх зв’язків.
 *    + 
 * Матеріали:
 * https://www.zentut.com/c-tutorial/c-linked-list/
 * https://en.wikipedia.org/wiki/Linked_list
 */



typedef struct Node {
    int info;
    struct Node *next;

} Node;

// Public API single linked list

void add_item(int info, Node **list);
Node *edit_item_in_list(int new_info, int old_info, Node **list);
void remove_item(int info, Node **list);
void dump_into_file(FILE *fp, Node **list);
Node *search_item(int info, Node **list);
Node *load_list_from_file(FILE *fp);
Node *radd_item(int info, Node **head);

// utilities
void edit_item(int info, Node *node);
void print_list(Node **list);
void print_node(Node *list);
Node *create_node(int info);
void free_list(Node** list);



int main() {
    Node *list = NULL, *single = NULL, *result;
    add_item(1, &list);
    add_item(2, &list);
    add_item(3, &list);
    // remove_item(3, &list);
    // print_list(&list);
    
    // edit_item_in_list(100, 3, &list);
    // single = search_item(100, &list);
    // print_node(single);
    FILE *output = fopen("single_linked_list.dat", "wb");
    dump_into_file(output, &list);
    fclose(output);

    output = fopen("single_linked_list.dat", "rb");
    result = load_list_from_file(output);

    printf("Print list after un-packing");

    print_list(&result);
    fclose(output);
    free_list(&list);
    free_list(&result);
    return 0;
}

void print_list(Node **list) {
    printf("Printing list: \n");
    Node *current = (*list);
    if (current == NULL) {
        printf("Empty list: \n");
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
    else printf("Node data is: %d\n", node->info);
}


Node *create_node(int info) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->info = info;
    node->next = NULL;
    return node;
}

// PUBLIC API

Node *search_item(int info, Node **list) {
    if ((*list) == NULL) return NULL;
    if ((*list)->info == info) {
        return (*list);
    }
    return search_item(info, &((*list)->next));
}


void add_item(int info, Node **head) {
    if ((*head) == NULL) {
        (*head) = create_node(info);
    } else {
        Node *current = (*head);

        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = create_node(info);
    }
}

Node *radd_item(int info, Node **head) {
    // add item in constant time (stack-like behaviour)
    Node *new_node = create_node(info);
    new_node->next = (*head);
    return new_node;
}

void edit_item(int info, Node *node) {
    node->info = info;
}


/*
 * return 1 if updated
 * return 0 if not updated
 */
Node *edit_item_in_list(int new_info, int old_info, Node **list) {
    Node *node;

    if ((node =search_item(old_info, &(*list)))!= NULL){
        edit_item(new_info, node);
        return node;
    }
    return NULL;
}

void remove_item(int info, Node **list) {
    Node *cursor, *to_remove;

    cursor = (*list);
    if (cursor == NULL) {
        return;
    }
    // edge case: only single node in list
    if (cursor->info == info && cursor->next == NULL) {
        free((*list));
        (*list) = NULL;
        return;
    }

    while (cursor->next != NULL)
    {
        if (cursor->next->info == info) {
            to_remove = cursor->next;
            cursor->next = to_remove->next;
            free(to_remove);
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
        printf("Empty list: \n");
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