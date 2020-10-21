/* 21.10.2020*/
//  Work #2  //
// 

#include <stdio.h>
#define N 3

int i = 1;

int main(void) {
  int i = 10;
  char ch = 'W';
  int n;
  int az;
  

  float farray[N] = {0.1, 0.2, 0.3};
  char charray[N] = {'s', 'e', 'l'};

  printf("Змінна \t A - %d %c,  i = %d\n", ch, ch, i);

  printf("faray[0..2] - %.2f %.3e %g\n", farray[0], farray[1], farray[2]);

  for(n = 0; n < N; n++)
  {
    printf("faray[%i] - %.2f %.3e %g\n", n, farray[n], farray[n], farray[n]);
  }

  for(n = 0; n < N; n++)
  {
    printf("faray[%i] - \' %c ' %d %i\n", n, charray[n], charray[n], charray[n]);
  }

  for(az = 'A'; n < 'Z'; n++)
  {
    printf("char - %c number: %d\n", n, n);
  }
  return 0;
}

/*
if () else

switch()
{
  case ...;
  default

}

for()
while()
do ... while() garanteed ran once

*/