#include <cs50.h>
#include <stdio.h>

//Implémentation de fonction
long long expo (int a, int b);
int longueur (long long n);
int digit (long long n, int k);
int checksum (long long n);


///////////FONCTION PRINCIPALE////////////////

int main (void)
{
    long long number = get_long_long("Number: ");
    int nbe_digit = longueur (number);
    printf("le nombre comporte %d digits !\n", nbe_digit);
    printf("le dernier digits est : %d \n", digit(number, longueur (number)));
    printf("Le checksum = %d \n", checksum(number));

//Vérification de la validité de la carte
    if ((checksum (number) % 10 ) == 0 )     //appel de la fonction "checksum" qui retourne un nombre issu d'un argorithme de Luhn
    {
        //AMEX : 15 digits
        //Start with 34, 37

        if (nbe_digit == 15 && (digit (number, 1) == 3 ) && ((digit (number, 2) == 4) || (digit (number, 2) == 7 )))
        {
           printf("AMEX\n") ;
        }

        //Mastercard : 16 digits
        //Start with 51, 52, 53, 54, 55

        else if (nbe_digit == 16 && (digit (number, 1) == 5 ) && ((digit (number, 2) == 1) || (digit (number, 2) == 2 ) || (digit (number, 2) == 3 ) || (digit (number, 2) == 4 ) || (digit (number, 2) == 5 )))
        {
            printf("MASTERCARD\n");
        }

        //Visa : 13 ou 16 digits
        //Start with 4

        else if (((nbe_digit == 13) || (nbe_digit == 13)) && (digit (number, 1) == 3 ))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}



///////////FONCTIONS////////////////

long long expo (int a, int b)
{
    long long c = a;

    if (b==0)
    {
        return 1;
    }
    else
    {
        for (int i=1; i<b; i++)
        {
            c *= a;
        }
    return c;
    }
}

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


//retourne le k digit en partant du début
int digit (long long n, int k)
{
    return (n/expo(10, longueur(n)-k) )%10;
}


//retourne le nombre obtenu par le Luhn’s algorithm
int checksum (long long n)
{
    int l = longueur (n);
    int sum = 0;
    for (int i=2; i<=l; i +=2)
    {
        if (digit (n, i) * 2 < 10)
        {
            sum += digit (n, i) * 2;
        }
        else
        {
            sum = sum + ((digit (n, i) * 2 )% 10) + 1;
        }
        printf ("%d ) sum = %d \n", i, sum);
    }
    for (int i=1; i<=l; i +=2)
    {
        sum += digit (n, i);
        printf ("%d ) sum = %d \n", i, sum);
    }
        return sum;
}
