#include <stdlib.h>
// 5 to 35
void gen_rand()
{
  int num;
  
  srand((unsigned int)time((time_t *)NULL));
  num = rand()%30+5;
}
