#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


//Inclusion des fonctions
int ascii_to_alphabet (char letter);
char alphabet_to_ascii (int alphabet, bool lower);
int shift (string key, int *j);


//Fonction Principale
int main (int argc, string argv[])
{
    //Vérification de la validité de la ligne de commande
    if (argc == 1)
    {
        printf ("Usage: %s k\n", argv[0]);
        return 1;
    }
    string k = argv[1];
    for (int i = 0; i < strlen(k); i++)
    {
        if (argc > 2 || !isalpha(k[i]))
        {
            printf ("Usage: %s k\n", argv[0]);
            return 1;
        }
    }

    //Si absence d'erreur le programme peut continuer
    string plain = get_string("plaintext: ");
    int l = strlen(plain);
    char cipher[l + 1];
    int j = -1;

    //Parcoure le plaintext et encrypte char par char
    for (int i = 0; i < l; i++)
    {
        //Vérifie si lettre ou non
        if (isalpha(plain[i]))
        {
            //Mise en mémoire de la casse pour la restituer après chiffrement
            bool lower = 1;
            if isupper (plain[i])
            {
                lower = 0;
            }
            cipher[i] = alphabet_to_ascii ((ascii_to_alphabet(plain[i]) + shift (k, &j)) % 26, lower);
        }
        else
        {
            cipher[i] = plain[i];
        }
    }
    //printf("cipher[l] = %c \n", cipher[l]);
    cipher[l] = '\0';
    printf ("ciphertext: %s\n", cipher);
    return 0;
}

//1
int ascii_to_alphabet (char letter)
{
    if islower (letter)
    {
        return (int) (letter - 97) ;
    }
    else
    {
        return (int) (letter - 65) ;
    }
}

//2
char alphabet_to_ascii (int alphabet, bool lower)
{
    if (lower == 1)
    {
        return (char) (alphabet + 97) ;
    }
    else
    {
        return (char) (alphabet + 65) ;
    }
}
//Décalage selon la clé (utilise le plaintext pour se repérer)
int shift (string key, int *j)
{
    (*j)++;
    int n = strlen(key);
    return ascii_to_alphabet(key[*j % n]);
}