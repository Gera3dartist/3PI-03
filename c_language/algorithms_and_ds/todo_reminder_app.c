#include <stdio.h>
#include <stdlib.h>

void seetodo();
void createtodo();
void deletetodo();


// Driver Code
int main()
{
    int choice;

 
    while (1) {
 
        // Change console color and
        // text color
        // system("Color 3F");
        system("clear");

 
        printf("1. List scheduled items\n");
        printf("2. Add reminder \n");
        printf("3. Delete scheduled item\n");
        printf("4. Exit");
        printf("\n\n\nEnter your choice\t:\t");
 
        scanf("%d", &choice);
 
        switch (choice) {
 
        case 1:
            // seetodo();
            break;
        case 2:
            // createtodo();
            break;
        case 3:
            // deletetodo();
            break;
        case 4:
            exit(1);
            break;
        default:
            printf("\nInvalid Choice :-(\n");
            system("pause");
        }
    }
    return 0;
}