#include <cs50.h>
#include <stdio.h>
#include <string.h> // Agregamos esta libreria para poder utlizar la funcion strcmp que compara los strings

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    { // Recorremos el arreglo donde estan los nombres de los candidatos

        if (strcmp(candidates[i].name, name) == 0)
        { // Comparamos el nombre ingresado por el usuario hasta hallar la posicion
          // del candidato que escogio
            preferences[voter][rank] = i; // Guardamos en la posicion correspondiente del votante y
                                          // el ranking, el candidato escogido
            return true;
        }
    }
    return false; // Devolvemos false si el nombre del candidato no es valido
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    { // Revisamos a cada elector

        for (int j = 0; j < candidate_count; j++)
        { // Revisamos sus candidatos en orden de preferencia

            if (candidates[preferences[i][j]].eliminated == false)
            { // Hasta encontrar el primero que no este eliminado

                candidates[preferences[i][j]].votes++; // Le sumamos un voto a ese candidato
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    { // Revisamos la cantidad de votos para cada candidato

        int mayoria = voter_count / 2; // Hayamos la mayoria de votos
        if (candidates[i].votes > mayoria)
        { // Chequeamos si hay algun candidato que tiene mas votos que la mayoria

            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = voter_count; // Iniciamos revisando a partir del maximo numero de votos que puede
                           // tener un candidato

    for (int i = 0; i < candidate_count; i++)
    { // Chequeamos para cada candidato que no este eliminado su numero de votos

        if (candidates[i].eliminated == false && candidates[i].votes < min)
        {

            min = candidates[i].votes; // Vamos actualizando el valor del minimo
        }
    }
    return min; // Cuando lo hallamos lo retornamos al finalizar
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {

        if (candidates[i].eliminated == false && candidates[i].votes != min)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place

void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    { // Recorremos el arreglo de candidatos en la seccion del conteo de votos

        if (candidates[i].votes == min)
        {

            candidates[i].eliminated =
                true; // Actualizamos el estado del candidato si su conteo de votos es el minimo
        }
    }
    return;
}
