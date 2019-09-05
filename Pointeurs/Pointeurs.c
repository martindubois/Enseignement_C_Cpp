
#include <stdio.h>

int main()
{
    unsigned int i;
    int        * P;
    int          Tableau[12];

    for (i = 0; i < 12; i++)
    {
        printf("%p\n", &Tableau[i]);
    }

    printf("Seconde partie\n");

    P = &Tableau[0];

    printf("%p\n", P);

    P++;

    printf("%p\n", P);

    printf("Troisieme partie\n");

    printf("%p\n", &P[6]);
}