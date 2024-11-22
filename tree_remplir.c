#include <stdlib.h>

#include "tree.h"
#include "loc.h"
#include "map.h"
#include "moves.h"
#include "stdio.h"

//En cours//
void remplir_arbre(t_node* node, t_localisation robot,t_map* map, int* tableaualeatoire, int MAX_DEPTH) {
    t_localisation robot_temp=robot;
    int* tableau=malloc(sizeof(int)*(node->nbSons-1));
    int k = 0;
    if(node->depth==MAX_DEPTH) {
        return;
    }

    for (int i=0;i<node->nbSons;i++)
    {
        updateLocalisation(&robot_temp,tableaualeatoire[i]);
        node->sons[i]->movement=tableaualeatoire[i];
        if(robot_temp.pos.x>map->x_max || robot_temp.pos.y>map->y_max) {
            return;
        }
        node->sons[i]->value=map->costs[robot_temp.pos.x][robot_temp.pos.y];

        for (int j = 0; j < node->nbSons; j++) {
            if (j != i) {
                tableau[k] = tableaualeatoire[j];
                printf("tableau k : %d",tableau[k]);
                k++;

            }
        }k=0;

        remplir_arbre(node->sons[i],robot_temp,map,tableau,MAX_DEPTH);




    }
    free(tableau);

}



    // Parcourir tous les fils
    for (int i = 0; i < root->nbSons; i++) {
        printTree(root->sons[i]);  // Appel récursif sur chaque fils
    }
}
