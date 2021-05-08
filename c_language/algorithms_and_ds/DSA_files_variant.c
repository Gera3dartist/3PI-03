#include <stdio.h>
#define ROWS 4
#define COLS 3


void print_into_stream_headers(FILE *stream);
void print_array_into_stream(int *parray, int rows, int cols, FILE *stream, int width);


int main(void) {
  FILE *stream;

  stream = fopen("output.txt","w+");

  // result from lab work 1
  int result[12] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0};

  // print into stdout
  print_into_stream_headers(stdout);
  print_array_into_stream(result, ROWS, COLS, stdout, 5);

  // output into file
  print_into_stream_headers(stream);
  print_array_into_stream(result, ROWS, COLS, stream, 5);
  fclose(stream);
  return 0;
}

void print_into_stream_headers(FILE *stream) {

  fprintf(stream, "|----------------------------|\n");
  fprintf(stream, "| Виконала | ЗПІ-03 Піх      |\n");
  fprintf(stream, "|----------------------------|\n");
}

void print_array_into_stream(int *parray, int rows, int cols, FILE *stream, int width) {

  for (int i=0; i<rows; i++) {
    for (int j=0; j<cols; j++) {
      fprintf(stream, " %*d ", width, *(parray + i * cols + j));
    }
    fprintf(stream, " \n");
  }
}