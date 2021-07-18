#include <stdio.h>      /* puts, printf */
#include <time.h>       /* time_t, struct tm, time, localtime */
#include <unistd.h>

int main ()
{
  time_t rawtime;
  time_t rawtime2;
  struct tm *timeinfo;
  struct tm *timeinfo1;
  struct tm *timeinfo2;

  time (&rawtime);
  timeinfo1 = localtime(&rawtime);
  sleep(3);
  time (&rawtime2);
  timeinfo2 = localtime(&rawtime2);

  if (rawtime2 > rawtime) {
    printf ("t2 %s > t1 %s", asctime(timeinfo2), asctime(timeinfo1));
  }

  timeinfo = localtime(&rawtime);
  printf ("Current local time and date: %s", asctime(timeinfo));

  return 0;
}