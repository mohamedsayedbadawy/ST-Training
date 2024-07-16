#include<stdio.h>
#include"function.h"
int expected_salary =5000;
int real_salary ;
const int increasing=1000;
 int main ()

{
  printf("please enter your expected salary\n");
  scanf("%d",&expected_salary);
  printf("please enter your real salary\n");
  scanf("%d",&real_salary);
  print_data(expected_salary,real_salary,increasing);
  return 0;
}
