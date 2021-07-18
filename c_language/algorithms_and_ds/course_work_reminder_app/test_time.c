#include <time.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
  time_t date1, date2;
  // initialize date1 and date2...
  time(&date1);
  sleep(3);
  time(&date2);

  double seconds = difftime(date2, date1);
  printf("Diff:  > %lf\n", seconds);
  if (seconds > 0) {
    printf("Date2 > Date1\n");
  }
  printf("Date1:  > %ld\n", (long) date1);
  printf("Date2:  > %ld\n", (long) date2);

  return 0;
}