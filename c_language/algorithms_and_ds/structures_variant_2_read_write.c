#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MNAME 32
#define PNAME 16


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


void print_employee(Employee *emp);


/*
    ЗАВДАННЯ:

    1. необхідно написати код програми, що створює масив структур згідно з
    індивідуальним завданням та виконує запис даних в файл у вигляді структурних
    блоків (елементів масиву структур). Ім'я файлу – «імя_структури».txt.

    2. Реалізувати читання із файлу «імя_структури».txt
    окремих елементів масиву структур за заданим індексом масиву.


    РЕЗУЛЬТАТ РОБОТИ:

    1. Роздрукувати (вивести на екран)
    попередньо сформовані та підготовлені для запису в файл дані.

    2. Роздрукувати (вивести на екран)
    результат виконання операції читання даних із файлу.


    // Варіант 2: Структура «Співробітник»: 
    прізвище, ім’я, по батькові, посада, рік народження, заробітна плата.


    // variant 9: Структура «Пацієнт»: 
    прізвище, ім’я, по батькові, домашня адреса, номер медичної карти, номер страхового поліса.

 */


int main(void) {
    int size, index = 0;
    Employee *records, *result;

    printf("Вкажіть кількість працівників: \n");
    scanf("%d", &size);

    //allocate space for array of Employee and store into pointer first location
    records = (Employee*)malloc(size * sizeof(Employee));
    
    // fill records
    for (int i=0;i<size;i++) {
        printf("\n----------- Данні для працівника з індексом %d ----------- \n\n", i);
        printf("Вкажіть ім'я: \n");
        scanf("%s", (records + i)->personal.first);

        printf("Вкажіть прізвище: \n");
        scanf("%s", (records + i)->personal.last);

        printf("Вкажіть по-батькові: \n");
        scanf("%s", (records + i)->personal.surname);

        printf("Вкажіть позицію: \n");
        scanf("%s", (records + i)->position);

        printf("Вкажіть Заробітну плату: \n");
        scanf("%f", &(records + i)->salary);
    }

    // display records before dumping into file
    printf("Список працівників перед збереженням\n");
    for (int i=0; i<size; i++) {
        printf("----------- Номер працівника -  %d -----------\n", i);
        print_employee((records + i));
    }
    
    // write into file
    FILE *output = fopen("spivrobitnyk.dat", "wb");
    fwrite(records, sizeof(Employee), size, output);

    // close output file
    fclose(output);
    // freeing records
    free(records);
    

    output = fopen("spivrobitnyk.dat", "rb");
    result = (Employee*) malloc(sizeof(Employee));
    
    printf("\nВкажіть номер працівника для відображення починаючи з 0 і до %d\n", size-1);
    scanf("%d", &index);
    // offset  file cursor
    fseek(output, sizeof(Employee) * index, SEEK_SET);

    // read once sizeof(Employee) bytes  from current cursor position
    fread(result, sizeof(Employee), 1, output);
    print_employee(result);

    fclose(output);
    free(result);
    return 0;
}


void print_employee(Employee *emp) {
    printf("Iм'я: %s\n", emp->personal.first);
    printf("Прізвище: %s\n", emp->personal.last);
    printf("По-батькові: %s\n", emp->personal.surname);
    printf("Посада: %s\n", emp->position);
    printf("Заробітна плата: %.2f\n", emp->salary);

}
