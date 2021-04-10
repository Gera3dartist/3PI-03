#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * ЗАВДАННЯ:
 * Розробити програмний алгоритм, вибрати оптимальний тип даних та написати програму для знаходження матриці А-1 оберненої до заданої матриці А розмірності N * N та виконати перевірку А * А-1.

 * Алгоритм обов’язково повинен включати наступні основні блоки:
 * 1. Створення файлу (ім’я – indata.txt), в який записуються розмірність та початкові значення всіх елементів матриці А (згідно зі своїм варіантом завдання).
 * 2. Читання початкових даних із файлу indata.txt та запис їх у масив для якого динамічно виділяється пам’ять.
 * 3. Знаходження оберненої матриці А-1, якщо визначник матриці не дорівнює 0.
 * 4. Виконання перевірки (А * А-1 == 0).
 * 5. Створення файлу (ім’я – outdata.txt), в який записуються результуючі значення всіх елементів (із динамічного масиву) матриці А-1.
 * 6. Відображення всіх результатів (включно з повідомленнями про помилки та попередження) виконання програмного коду на екрані монітора.
 * ЗВІТ розмістити у Classroom.
 * References: 
 * 1. The Determinant of a Square Matrix https://people.richland.edu/james/lecture/m116/matrices/determinant.html
 * 2. Matrix mutliplication: https://www.studypug.com/algebra-help/multiplying-a-matrix-by-another-matrix
 * 3. Mat is fun: https://www.mathsisfun.com/algebra/matrix-inverse-minors-cofactors-adjugate.html
 * 
 */
float* inverse_matrix(float* matrix, int size, float det);
float find_determinant(float* matrix, int size);
float* multiply_square_matrices(float* matrix1, float* matrix2, int size);
float* multiply_by_scalar(float* matrix, int size, float scalar);
float* get_cofactor(float* matrix, int size, int row, int col);
float* get_adjoint_matrix(float* matrix, int size);
int equals(float* matrix1, float* matrix2);
void show_array (float *parray, int rows, int cols);
float *get_minor_matrix(float* matrix, int size);


int main(void) {
    /*
     * input matrix: 
     * 3 5 2 1 
     * 2 1 2 4
     * 1 3 4 2
     * 4 3 1 3
     */
    int size = 4;
    float *inversed, *identity1, *identity2, det;

    // input matrix
    float input_matrix[16] = {3, 5, 2, 1, 2, 1, 2, 4, 1, 3, 4, 2, 4, 3, 1, 3};
    
    det = find_determinant(input_matrix, size);

    printf("Determinant is: %f", det);
    if (det == 0) {
        printf("matrix can not be inverted");
    }
    printf("\noriginal matrix: \n");
    show_array(input_matrix, size, size);

    inversed = inverse_matrix(input_matrix, size, det);
   
    printf("Inversed matrix: \n");
    show_array(inversed, size, size);

    identity1 = multiply_square_matrices(input_matrix, inversed, size);
    identity2 = multiply_square_matrices(inversed, input_matrix, size);

    printf("Identity1 matrix: \n");
    show_array(identity1, size, size);

    printf("Identity2 matrix: \n");
    show_array(identity2, size, size);


    free(inversed);
    free(identity1);
    free(identity2);
    return 0;
}


void show_array (float *parray, int rows, int cols) {
  for (int i=0; i<rows; i++) {
    for (int j=0; j<cols; j++) {
        printf("%.3f, ", *(parray + i * cols + j));
    }
    printf("\n");
    }
}


float* get_cofactor(float* matrix, int size, int row, int col) {
    int cm_i = 0, cm_j, cofactor_size = size - 1;
    float *cofactor_matrix = calloc(cofactor_size*cofactor_size, sizeof(float));
    
    // iterating over main matrix skipping row, col
    // and creating new cofactor matrix
    for (int i = 0; i < size; i++) {
        if (i == row)
            continue;
        cm_j = 0;
        for (int j = 0; j < size; j++) {
            if (j == col)
                continue;
            *(cofactor_matrix + cm_i * cofactor_size + cm_j++) = *(matrix + i * size + j);
        }
        cm_i++;
        
    }
    return cofactor_matrix;
}


float find_determinant(float* matrix, int size) {
    float sign = 1, det = 0, *cofactor;

    if (size == 1) {
        return *(matrix);
    }

    for (int i=0; i < size; i++) {
        cofactor = get_cofactor(matrix, size, 0, i);
        det += sign * (*(matrix + i)) * find_determinant(cofactor, size - 1);
        sign *= -1;
        free(cofactor);
    }
    return det;
}


float *get_minor_matrix(float* matrix, int size) {
    float *cofactor;
    float *minor = calloc(size*size, sizeof(float));
    int sign;

    for (int i=0; i < size; i++) {

        sign = ((i % 2) != 0) ? -1 : 1;
        for (int j = 0; j < size; j++) {
            cofactor = get_cofactor(matrix, size, i, j);
            *(minor + i * size + j) = sign * find_determinant(cofactor, size - 1);
            sign = sign * -1;
            free(cofactor);
        }
    }

    return minor;
}


float* get_adjoint_matrix(float* matrix, int size) {
    float *addjoint = calloc(size*size, sizeof(float));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                 *(addjoint + i * size + j) = *(matrix + i * size + j);
                 break;
            }
            *(addjoint + i * size + j) = *(matrix + j * size + i);
            *(addjoint + j * size + i) = *(matrix + i * size + j);
        }
    }
    return addjoint;
}


float* multiply_by_scalar(float* matrix, int size, float scalar) {
    float *resulting_matrix = calloc(size*size, sizeof(float));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(resulting_matrix + i * size + j) = (*(matrix + i * size + j) * scalar);
        }
    }
    return resulting_matrix;

}


float* inverse_matrix(float* matrix, int size, float det) {
    float *minor, *adjoint_matrix, *inverse_matrix;

    minor = get_minor_matrix(matrix, size);
    adjoint_matrix = get_adjoint_matrix(minor, size);
    inverse_matrix = multiply_by_scalar(adjoint_matrix, size, 1/det);

    free(minor);
    free(adjoint_matrix);
    return inverse_matrix;
}


float* multiply_square_matrices(float* matrix1, float* matrix2, int size) {
    float *resulting_matrix, temp_res = 0;
    resulting_matrix = calloc(size*size, sizeof(float));
    //naive approach
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                *(resulting_matrix + i * size + j) += *(matrix1 + i * size + k) * (*(matrix2 + k * size + j));
            }
        }
    }
    return resulting_matrix;
}
