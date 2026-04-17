#include <cs50.h>
#include <stdio.h>
#include <math.h>

int digitos(long numero_tarjeta);
int suma_pares(long numero_tarjeta);
long y = 0;
long z = 0;


int main(void)
{
  long numero_tarjeta = 4003600000000014;
  long a = numero_tarjeta;
  int suma = 0;

  for( int i = 1; i < 32; i= i+2)
  {

    z = (a/(long)pow(10,i))%10;

    printf("valores de z %li\n", z);

    long numeros = ((z*2)%10 + (z*2)/10);

    suma = suma + numeros;


  } return suma;

}





 if(digitos(numero_tarjeta) == 15 && suma_total%10 == 0)
  {
    t = ((numero_tarjeta)/((long)pow(10, 13)))%10;
  } else if ( t == 7 || t == 4)
    {
      t1 = ((numero_tarjeta)/((long)pow(10, 14)))%10;

    } else if (t1 == 3)
      {
        printf("AMEX");

      } else
        {
          printf("INVALID");
        }
