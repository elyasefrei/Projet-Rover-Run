#include <stdlib.h>
#include  "moves.h"
#include "tree.h"


/* prototype of local functions */
/* local functions are used only in this file, as helper functions */

int* create_tableau(int n);


/*-------------------------------------------------------------------------------------------------------------------- */
/* 
* @brief Création d'un tableau qui recensera tous les mouvements possibles que le robot peut adopter, ainsi que leur probabilité associé
* @param n : paramètre qui designe la taille de notre tableau
* @return il va nous retourner un tableau avec tous les mouvements possible 
*/
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

/*-------------------------------------------------------------------------------------------------------------------- */
/* 
* @brief Permet d'obtenir un tableau contenant tous les mouvements du robot, arrangés de manière aléatoire. 
* @param n : paramètre qui designe la taille de notre tableau aléatoire
* @return il va nous retourner un tableau avec tous les mouvements possible, arrangés de manière aléatoire.
*/
int* mouvement_aleatoire(int n ) {
    int* tableau = create_tableau(MVT_TOTAL); // va faire un appel pour crée le tableau avec tous les mouvements possibles
    int* tableau_aleatoire = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        int rdm = rand()%(MVT_TOTAL - i);
        tableau_aleatoire[i] = tableau[rdm];
        tableau[rdm] = tableau[MVT_TOTAL - i - 1];
    }

    free(tableau); // libérer le tableau mouvement du robot ( pas ranger aléatoirement)



    return tableau_aleatoire; // retourne le tableau aléatoire
}


