#include <cs50.h>
#include <math.h>
#include <stdio.h>

int digitos(long numero_tarjeta); // todas las variables declaradas usadas en el programa.
int suma_pares(long numero_tarjeta);
int suma_impares(long numero_tarjeta);
long y = 0;
long z = 0;
long x = 0;
long t = 0;
long t1 = 0;
long t2 = 0;
long t3 = 0;
long t4 = 0;

int main(void)
{
    long numero_tarjeta =
        get_long("Por favor introduce tu numero de tarjeta:\n\n"); // pido al usuario introducir su
                                                                   // numero de tarjeta

    digitos(numero_tarjeta); // llamo a la funcion digitos (cuenta los digitos de la tarjeta)

    y = digitos(numero_tarjeta); // igualo la salida de digitos a una variable por si quiero usarla

    suma_pares(
        numero_tarjeta); // llamo a la funcion suma_pares(multiplica por 2 y suma los digitos)

    z = suma_pares(
        numero_tarjeta); // igualo la salida de suma_pares a una variable por si quiero usarla

    suma_impares(numero_tarjeta); // llamo a la funcion suma_impares(suma los digitos impares)

    x = suma_impares(
        numero_tarjeta); // igualo la salida de suma_impares a una variable por si quiero usarla

    int suma_total = suma_impares(numero_tarjeta) +
                     suma_pares(numero_tarjeta); // sumo tanto suma_impares y sumas_pares

    if (suma_total % 10 == 0) // condicional para saber si cumple con el algoritmo de Luhn.
    {
        if (digitos(numero_tarjeta) ==
            15) // condicion para saber si los digitos son 15 y coincide con AMEX
        {
            t = ((numero_tarjeta) / ((long) pow(10, 13))) %
                10; // verifico el valor del segundo digito

            if (t == 7 || t == 4) // si es igual a 4 0 7 el segundo digito es probable que sea AMEX
            {
                t1 = ((numero_tarjeta) / ((long) pow(10, 14))) % 10;
                if (t1 == 3) // con esto se termina de verificar si es AMEX
                {
                    printf("AMEX\n"); // se imprime en pantalla AMEX
                }
                else
                {
                    printf("INVALID\n"); // si el primer digito es distinto de 3 no es AMEX
                }
            }
            else
            {
                printf("INVALID\n"); // si el segundo digito no es 4 o 7 no es AMEX
            }
        }
        else if (digitos(numero_tarjeta) ==
                 16) // ahora verifico si el numero de digitos de la tarjeta es de 16
        {
            t2 = ((numero_tarjeta) / ((long) pow(10, 14))) %
                 10; // se selecciona el segundo digito de la tarjeta
            t3 = ((numero_tarjeta) / ((long) pow(10, 15))) %
                 10; // se selecciona el primer digito de la tarjeta

            if (t2 <= 5 && t2 >= 1 && t3 == 5) // si cumplen el primer digito = 5 y el segundo esta
                                               // entre 1 y 5 es mastercard
            {
                printf("MASTERCARD\n"); // se imprime
            }
            else if (t3 == 4) // si la tarjeta de 16 digitos comienza en 4 entonces es VISA
            {
                printf("VISA\n"); // se imprime visa
            }
            else
            {
                printf("INVALID\n"); // de no ser el primer digito 4, es invalido y se imprime
            }
        }
        else if (digitos(numero_tarjeta) == 13) // se verifica para 13 digitos de tarjeta
        {
            t4 = ((numero_tarjeta) / ((long) pow(10, 12))) %
                 10; // se verifica el primer digito que debe ser 4

            if (t4 == 4)
            {
                printf("VISA\n"); // si el primer digito es 4, se inprime visa
            }
            else
            {
                printf("INVALID\n"); // de no ser 4 es invalido y se imprime
            }
        }
        else // si los digitos de la tarjeta es distinto de 13 es invalido
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n"); // si no cumple con el algoritmo de Luhn es invalido
    }
}

// funciones usadas el main :

int digitos(long numero_tarjeta) // cuenta la cantidad de digitos de la tarjeta
{
    long u = numero_tarjeta;
    int i = 0;
    while (u != 0)
    {
        u = u / 10;
        i++;
    }
    return i;
}

int suma_pares(long numero_tarjeta) // selecciona los numeros de izq. a der.de dos en dos,
                                    // multiplica cada digito por 2 y los suma.
{
    long a = numero_tarjeta;
    int suma = 0;

    for (int i = 1; i < 32; i = i + 2)
    {

        z = (a / (long) pow(10, i)) % 10;

        long numeros = ((z * 2) % 10 + (z * 2) / 10);

        suma = suma + numeros;
    }
    return suma;
}

int suma_impares(long numero_tarjeta) // suma los numeros de comenzando por el primero de izquierda
                                      // a derecha de dos en dos.
{
    long a = numero_tarjeta;
    int suma_impares = 0;

    for (int i = 0; i < 32; i = i + 2)
    {

        z = (a / (long) pow(10, i)) % 10;

        long numeros_impares = z;

        suma_impares = suma_impares + numeros_impares;
    }
    return suma_impares;
}
