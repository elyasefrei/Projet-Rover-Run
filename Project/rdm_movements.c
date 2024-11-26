#include <stdlib.h>
#include  "moves.h"
#include "tree.h"

int* create_tableau(int n) {
    int* tableau = malloc(n * sizeof(int));
    int proportion[] = {22, 15, 7, 7, 21, 21, 7};
    int indice = 0;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < proportion[i]; j++)
            {

                tableau[indice] = i;
                indice++;
            }
    }
    return tableau;
}

int* mouvement_aleatoire(int n ) {
    int* tableau = create_tableau(MVT_TOTAL);
    int* tableau_aleatoire = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        int rdm = rand()%(MVT_TOTAL - i);
        tableau_aleatoire[i] = tableau[rdm];
        tableau[rdm] = tableau[MVT_TOTAL - i - 1];
    }

    free(tableau);



    return tableau_aleatoire;
}


