#include <cs50.h>
#include <stdio.h>

//Implémentation de fonction
void repeat (char c, int n);


int main (void)
{
//Déclaration variables
    int h ;

//Demande la hauteur h tant que h n'est pas valide (int >0 <23)
    do
    {
        h = get_int("Height: ");
    }
    while (h < 0 || h > 23);

//Boucle principale qui va compter les rangées
//utilisation de la fonction repeat pour simplifier (pas de boucle dans les boucles)
    for (int j = 1; j < h + 1; j++)
    {
        repeat (' ', h - j);
        repeat ('#', j);
        repeat (' ', 2);
        repeat ('#', j);
        printf("\n");
    }
}



//définition fonction repeat
//ne retourne rien (effets secondaires)
void repeat (char c, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c", c);
    }
}