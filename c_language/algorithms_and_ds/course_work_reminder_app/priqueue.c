#include <time.h>
#include <stdio.h>
#include <stdlib.h>
 
int main(void) {
   char message [32];
   int num;

    printf("Specify message: ");
    scanf("%[^\n]%*c", message);
    
    printf("Specify num: ");
    scanf("%d", &num);
}