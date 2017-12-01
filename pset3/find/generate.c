/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */

#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // TODO: si nbe d'arg dans la ligne de commande invalide (0 ou > à 2)
    // --> redemande de taper la commande avec une indic sur comment l'utiliser
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // TODO: place le premier arg dans la var. n converti en int
    int n = atoi(argv[1]);

    // TODO: Si arg optionnel donné (seed)
    // initialise drand avec avec ce dernier
    // sinon initialise drand avec un seed qui va tjrs changer (time(NULL))
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        srand48((long) time(NULL));
    }

    // TODO: print n fois nmbre pseudorandom
    // pour que le nombre soit inclus dans [0,LIMIT] au lieu de [0;1], on multiplie par LIMIT
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
