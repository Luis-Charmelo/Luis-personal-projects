// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

unsigned int hash_primeras_letras(const char *word);
unsigned long hash_longitud(int cantidad_caracteres);
unsigned int contador = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned long N = 250000;

// Hash table
node *table[LENGTH][N]; // Usaremos una tabla hash de dos dimensiones, primero clasificamos por
                        // longitud de caracteres y luego las clasificamos por las primeras 3 letras

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int cantidad_caracteres = strlen(word);

    if (cantidad_caracteres < 1)
    { // Palabras vacias no son validas
        return false;
    }

    int posicion_longitud = hash_longitud(cantidad_caracteres);
    int posicion_letras = hash_primeras_letras(word);

    node *nodo_actual = table[posicion_longitud]
                             [posicion_letras]; // Segun nuestra funcion hash, creamos un apuntador
                                                // a donde deberia estar la palabra que buscamos

    while (nodo_actual != NULL)
    {

        if (strcasecmp(nodo_actual->word, word) == 0)
        { // Comparamos las palabras en el nodo (sin case sensitive)
          //  y si son iguales devolvemos true

            return true;
        }
        nodo_actual = nodo_actual->next;
    }

    return false; // Si la palabra no esta en el diccionario, devolvemos false
}

// Hashes word to a number

unsigned long hash_longitud(int cantidad_caracteres)
{
    return cantidad_caracteres %
           LENGTH; // Calcula el modulo con respecto a la cantidad maxima permitida de caracteres
                   // Eso nos dara un rango entre 0 y 45
}

unsigned int hash_primeras_letras(const char *word)
{ // Clasificams por las primeras 3 letras, multiplicamos por 26
    // una escala de 26 para darle mas peso al primer caracter y evitar colisiones
    unsigned int valor_hash = 0;

    int caracteres = strlen(word); // Calculamos la longitud de la palabra para asegurarnos que
                                   // maneje bien palabras menores a 3 letras

    if (caracteres >= 3)
    {
        valor_hash = (toupper(word[0]) - 'A') * 26 * 26 + (toupper(word[1]) - 'A') * 26 +
                     (toupper(word[2]) - 'A');
    }
    else if (caracteres == 2)
    { // Para palabras de 2 letras

        valor_hash = (toupper(word[0]) - 'A') * 26 + (toupper(word[1]) - 'A');
    }
    else
    { // Para palabras de 1 letra

        valor_hash = toupper(word[0]) - 'A';
    }

    return (valor_hash);
}

void agregar(const char *word)
{ // Llamamos a las dos funciones hash en el orden deseado

    int cantidad_caracteres = strlen(word); // Contamos la cantidad de caracteres

    int posicion_longitud =
        hash_longitud(cantidad_caracteres); // Aplicamos la primera funcion hash para saber la
                                            // primera posicion del arreglo

    int posicion_letras =
        hash_primeras_letras(word); // Aplicamos la segunda funcion hash para saber la poscion segun
                                    // las primeras 3 letras

    // Creamos listas enlazadas con los nodos para almacenar las colisiones

    node *nuevo_nodo = malloc(sizeof(node));
    strcpy(nuevo_nodo->word, word);
    nuevo_nodo->next = table[posicion_longitud][posicion_letras];
    table[posicion_longitud][posicion_letras] = nuevo_nodo;

    contador++; // Contamos cada palabra que se agrega al diccionario
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *archivo = fopen(dictionary, "r");
    if (archivo == NULL)
    {
        return false;
    }   

    char word[LENGTH + 1];

    while (fscanf(archivo, "%s", word) != EOF)
    {

        agregar(word); // Llamamos a la función para agregar la palabra a la tabla hash
    }

    fclose(archivo);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return contador;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < LENGTH; i++)
    { // Recorremos la tabla nodo por nodo

        for (int j = 0; j < N; j++)
        {

            node *nodo_actual = table[i][j]; // Creamos un apuntador que se mueva por toda la tabla

            while (nodo_actual != NULL)
            {

                node *tmp = nodo_actual; // Creamos uno auxiliar para ir borrando la memoria sin
                                         // perder el siguiente elemento

                nodo_actual = nodo_actual->next;

                free(tmp);
            }
        }
    }
    contador = 0;
    return true;
}
