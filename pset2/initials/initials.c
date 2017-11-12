#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main (void)
{
    string name = get_string();
    for (int i = 0; i < strlen(name); i++)
    {
        if ((int) name[i] != 32 && ((int) name[i - 1] == 32 || i == 0))
        {
            printf ("%c", toupper(name[i]));
        }
    }
    printf("\n");
    return 0;
}