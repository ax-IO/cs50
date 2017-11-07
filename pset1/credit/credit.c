#include <cs50.h>
#include <stdio.h>

//Implémentation de fonction
int longueur (long long n);
int checksum (long long n);
int digit (long long n, int k);


///////////FONCTION PRINCIPALE////////////////

int main (void)
{
    long long number = get_long_long("Number: ");

    int nbe_digit = longueur (number);
    printf("le nombre comporte %d digits !\n", nbe_digit);

//Test du checksum
    if (checksum (number) % 10 != 0)
    {
        if (nbe_digit == 15 && digit (number, 1) == 3)
        {
            ;
        }
    }
    else
    {
        ;
    }
    return 0;
}



///////////FONCTIONS////////////////


//retourne le nombre de digits
int longueur (long long n)
{
    int l = 0;
    while (n >= 10)
    {
        n/=10;
        l++;
    }
    return l+1;
}


//retourne le nombre obtenu par le Luhn’s algorithm
int checksum (long long n)
{
    int l = longueur (n);
    if (l % 2 == 0)
    {
        return 0; //cas ou le nombre est pair
    }
    else
    {
        return 1; // cas où le nombre est impair
    }
}

//retourne le k digit en partant du début
int digit (long long n, int k)
{
    int l = longueur (n) ;
    printf("k=%d et %d",k,l);
    return 0;
}