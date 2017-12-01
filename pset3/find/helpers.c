/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm

    if (n <= 0)
    {
        return false;
    }

    int i = 0;
    int j = n;
    int middle;

    while (n >= 0)
    {
        middle = (i + j) / 2;
        if (value == values[middle])
        {
            return true;
        }
        else if (value > values[middle])
        {
            i = middle + 1;
        }
        else
        {
            j = middle - 1;
        }

        //Nouvelle longueur
        n = j - i;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{

    // Création counting array 0-->65,535
    int count[65536] = {0};


    //Remplissage counting array
    for (int i = 0; i < n; i++)
    {
        count[values[i]]++;
    }

    //Generate sorted array
    // i--> count
    // j--> sorted
    // K--> dernière position
    int k = 0;
    for (int i = 0; i < 65536; i++)
    {
        for (int j = 0; j < count[i]; j++)
        {
            values[j + k] = i;

            if (j == count[i] - 1)
            {
                k += (j + 1);
            }
        }
    }
}
