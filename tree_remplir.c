#include <stdlib.h>

#include "tree.h"
#include "loc.h"
#include "map.h"
#include "moves.h"
#include "stdio.h"

//En cours//
void remplir_arbre(t_node* node, t_localisation robot,t_map* map, int* tableaualeatoire) {
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
        if(robot_temp.pos.x>map->x_max || robot_temp.pos.y>map->y_max || robot_temp.pos.x<0 || robot_temp.pos.y<0 || node->parent->value>=500) {
           node->sons[i]->value=10000;

        }
        else {
            node->sons[i]->value=map->costs[robot_temp.pos.x][robot_temp.pos.y];
        }


        for (int j = 0; j < node->nbSons; j++) {
            if (j != i) {
                tableau[k] = tableaualeatoire[j];
                k++;

            }
        }k=0;
        printf("POSITION ROBOT : %d %d et orientation : %d  et cout : %d\n",robot_temp.pos.x,robot_temp.pos.y,robot_temp.ori,node->sons[i]->value);

        remplir_arbre(node->sons[i],robot_temp,map,tableau);





    }
    free(tableau);

}

void printTree(t_node* root) {
    if (root == NULL) {
        return;  // Arbre vide ou fin de branche
    }

    // Afficher les informations du nœud actuel
    printf("Valeur: %d, Mouvement: %d, Profondeur: %d, NbSons: %d\n",
           root->value, root->movement, root->depth, root->nbSons);

    // Parcourir tous les fils
    for (int i = 0; i < root->nbSons; i++) {
        printTree(root->sons[i]);  // Appel récursif sur chaque fils
    }
}
