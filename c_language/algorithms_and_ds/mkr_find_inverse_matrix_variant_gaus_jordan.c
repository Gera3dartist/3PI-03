#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WIDTH 7
/*
 * Reference: 
 1. Algorithm https://www.codesansar.com/numerical-methods/matrix-inverse-using-gauss-jordan-method-c-program.htm
 2. Matrix as pointer: https://www.cs.cmu.edu/~ab/15-123S09/lectures/Lecture%2006%20-%20%20Pointer%20to%20a%20pointer.pdf
 */


float **inverseMatrix(float **matrix, int size);
float **readMatrixFromFile(FILE *fp, int size);
float **resizeMatrix(float **parray, int rows, int cols, int old_cols);
float **multiply_square_matrices(float** matrix1, float** matrix2, int size);
void dumpArrayIntoFile(float **parray, int rows, int cols, FILE *stream);
void showArrayPointer(float **parray, int rows, int cols);


int main()
{
  float **input_matrix, **inversed_matrix, **identity;
  int size;

  FILE *input_file, *outfile;

  input_file = fopen("input.txt", "r");
  // outfile = fopen("outfile.txt", "w");
  if (input_file==NULL)
  {
      printf("no such file.");
      return 0;
  }
  // 1. read size and matrix from file
  fscanf(input_file, "%d", &size);
  
  // 2. read matrix from file
  input_matrix = readMatrixFromFile(input_file, size);
  fclose(input_file);

  printf("\nOriginal matrix: \n");
  showArrayPointer(input_matrix, size, size);

  inversed_matrix = inverseMatrix(input_matrix, size);

  printf("\nInversed matrix: \n");
  showArrayPointer(inversed_matrix, size, size);

  // 4. Do verifications:  А * А-1 == 0 &&  А-1 * A == 0 
  identity = multiply_square_matrices(input_matrix, inversed_matrix, size);
  printf("\n А * А-1 == 0 result: \n");
  showArrayPointer(identity, size, size);
  free(identity);

  identity = multiply_square_matrices(inversed_matrix, input_matrix, size);
  printf("\n А-1 * А == 0 result: \n");
  showArrayPointer(identity, size, size);

  // 5. store inversed matrix into file
  outfile = fopen("outdata.txt", "w+");
  dumpArrayIntoFile(inversed_matrix, size, size, outfile);

  // 6. free pointers and files
  free(identity);
  free(input_matrix);
  free(inversed_matrix);
  fclose(outfile);

  return 0;
}

float** multiply_square_matrices(float** matrix1, float** matrix2, int size) {
    float **resulting_matrix, *row;
    resulting_matrix = (float**)calloc(size, sizeof(float*));
    //naive approach
    for (int i = 0; i < size; i++) {
        row = calloc(size, sizeof(float));
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                *(row + j) += *(*(matrix1 + i) + k) *  (*(*(matrix2 + k) + j));
            }
        }
        *(resulting_matrix + i) = row;
    }
    return resulting_matrix;
}


void showArrayPointer(float **parray, int rows, int cols) {
  for (int i=0; i<rows; i++) {
    for (int j=0; j<cols; j++) {
        printf("%*.3f, ", WIDTH, *(*(parray + i) + j));
    }
    printf("\n");
    }
}

void dumpArrayIntoFile(float **parray, int rows, int cols, FILE *stream) {

  for (int i=0; i<rows; i++) {
    for (int j=0; j<cols; j++) {

      fprintf(stream, " %*.3f ", WIDTH, *(*(parray + i) + j));
    }
    fprintf(stream, " \n");
  }
}

float **readMatrixFromFile(FILE *fp, int size) {
    float *row, **input_matrix;

    // 2D arrray to store the matrix
    input_matrix = (float**)malloc(size*sizeof(float*));

    char *to_parse = calloc(size*size*2, sizeof(char));
    int row_counter = 0, counter = 0;

    // read from fp into array to_parse
    while(fgets(to_parse, 255, fp));

	char *end = to_parse;

	while(*end) {
        // row is filled
        if (counter == 0) {
          row = calloc(size, sizeof(float));
        }

        if (counter < size) {
          *(row + counter) = strtof(to_parse, &end);
          counter++;
        }
        if (counter == size) {
          // add row to matrix and increment row counter
          *(input_matrix + row_counter) = row;
          counter = 0;
          row_counter++;
        }

		while (*end == ',') {
			end++;
		}
		to_parse = end;
	}
	return input_matrix;
}

float **resizeMatrix(float **parray, int rows, int cols, int old_cols) {
  float **tempMatrix, *row;

  tempMatrix = (float**)malloc(rows*sizeof(float*));
  
  for (int i=0; i<rows; i++) {
      row = calloc(cols, sizeof(float));
      for (int j=0; j<old_cols; j++) {
        *(row + j) = *(*(parray + i) + j);
      }
     *(tempMatrix + i) = row;
  }
  return tempMatrix;
}

float **inverseMatrix(float **matrix, int size) {
  int i,j,k;
  float **inversedMatrix, **resized_matrix, *row, temp;


  /* 1. Adding Identity Matrix of size */
  resized_matrix = resizeMatrix(matrix, size, size*2, size);
  for(i=0; i<size; i++)
  {
    for(j=0; j<size; j++)
    {
        if(i==j) 
        *(*(resized_matrix + i) + j + size) = 1;
        else 
        *(*(resized_matrix + i) + j + size) = 0;
    }
  }

  // 2. Partial pivoting, swapping rows
  for(int i = size - 1; i > 1; --i)
  {   
      if( *(*(resized_matrix + i-1) + 1) < *(*(resized_matrix + i) + 1))
      {
          for(int j = 0; j <2*size; ++j)
          {
              temp = *(*(resized_matrix + i) + j);
              *(*(resized_matrix + i) + j) = *(*(resized_matrix + i-1) + j);
              *(*(resized_matrix + i-1) + j) = temp;
          }
      }
  }

  // 3. Reducing To Diagonal Matrix
  for(i = 0; i < size; ++i)
  {
      for(j = 0; j < size; ++j)
      {
          if( j != i )
          {
              temp = *(*(resized_matrix + j) + i) / *(*(resized_matrix + i) + i);
              for(k = 0; k < size*2; ++k)
              {
                  *(*(resized_matrix + j) + k) -= *(*(resized_matrix + i) + k) * temp;
              }
          }
      }
  }

  // 4. Reducing To Unit Matrix
  for(i = 0; i < size; ++i)
  {
      temp = *(*(resized_matrix + i) + i);
      for( j = 0; j < 2*size; ++j)
      {
          *(*(resized_matrix + i) + j) = *(*(resized_matrix + i) + j)/temp;
      }
  }

  // 5. constructing inversed matrix
  inversedMatrix = (float**) malloc(size*sizeof(float*));
  for(i = 0; i < size; i++)
  {   
    row = calloc(size, sizeof(float));
    for( j = 0; j < size; j++)
    {
        *(row + j) = *(*(resized_matrix + i) + j + size);
    }
    *(inversedMatrix + i) = row;
  }
  return inversedMatrix;
}