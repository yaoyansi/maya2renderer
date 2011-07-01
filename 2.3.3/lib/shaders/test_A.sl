//#include "test_B.sl"
void 
test_B(
output float b0;
output float b1;
)
{
  printf("B b0=%f, b1=%f\n", b0, b1);

  b0=1;
  b1=2;
}

surface
test_A()
{
   float a=0;
   float c=-1;

   test_B(a, c);

   printf("A a=%f, c=%f\n", a, c);
   
}