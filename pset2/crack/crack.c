#define _XOPEN_SOURCE
#include <unistd.h>

#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define SALT "50"

//Inclusion des fonctions
char lettre_suivante (char lettre);
string suivant (string mdp);


//Fonction Principale
int main (int argc, string argv[])
{
    //Vérification de la validité de la ligne de commande
    if (argc != 2)
    {
        printf ("Usage: %s hash\n", argv[0]);
        return 1;
    }

    string hash = argv[1];
    //crack du mot de passe
    // Salt = 50
    //const char *c	= pointeur vers caractère constant

    //Initialisation mot de passe à la première valeur
    char mdp[5] = {'a', '\0', '\0', '\0', '\0'};
    while (strcmp(mdp, "ZZZZ" ) != 0)
    {
        //printf("%s\n", mdp);
        //Test de la validité du mot de passe
        if  (strcmp(crypt(mdp, SALT), hash) == 0)
        {
            break;
        }
        else
        {
            //Mot de passe suivant
            strcpy(mdp, suivant (mdp));
        }

    }
    printf("%s\n", mdp);
    return 0;
}

//Incrémente l'ASCII d'un char
//Gère le passage de 'z' à 'A' et de 'Z'
//Retourne la lettre suivante

char lettre_suivante (char lettre)
{
    switch (lettre)
    {
    case 'z':
        return 'A';
        break;

    case 'Z':
        return 'a';
        break;
    case '\0':
        return '\0';
        break;

    default:
        return (char) ((int) (lettre +1));
    }
}


//Prend un mot de passe supposé valide
//et le change parmi ceux possibles
// (alphaet <= 4)
//Appele 4 fois la meme fonction de cht de char
//Controle les passage "nZZ" --> "oaa"
string suivant (string mdp)
{
    //Parcourt chaque lettre du mdp en partant de la fin
    for (int n = strlen (mdp) - 1; n >= 0; n--)
    {
        //Cas "normal" : la (dernière) lettre est incrémentée
        mdp[n] = lettre_suivante(mdp[n]);

        //Si la lettre "boucle"...
        // && vérification de la présence de lettre sur la gauche
        if (mdp [n] == 'a')
        {
            //Si c'est la dernière lettre
            if (n == 0)
            {
                //ajoute une unité sur la gauche
                char a[6] = {'a', '\0', '\0', '\0', '\0', '\0'};
                return strcat(a, mdp);
            }
            //Cas normal : Incrémente la lettre suivante
            else
            {
                continue;
            }
        }

        break;
    }
    return mdp;
}



