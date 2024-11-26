#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "loc.h"
#include "map.h"
#include "moves.h"
#include "time.h"


t_node * create_node(int depth, int nbSons, t_node* parent,int max_depth) {
    t_node *node = malloc(sizeof(t_node));
    node->value = 0;
    node->depth = depth;
    if(depth==max_depth) {
        node->nbSons=0;
    }
    else {
        node->nbSons=nbSons;
    }
    node->sons = malloc(nbSons * sizeof(t_node *));
    node->movement=0;
    node->parent=parent;
    for (int i = 0; i < nbSons; i++) {
        node->sons[i] = NULL;
    }
    return node;
}


void create_children(t_node *parent, int max_depth) {
    if (parent->depth >= max_depth) {
        return;
    }

    for (int i = 0; i < parent->nbSons; i++) {
        parent->sons[i] = create_node(parent->depth + 1, parent->nbSons - 1,parent,max_depth);
        create_children(parent->sons[i],max_depth);
    }
}



void remplir_arbre(t_node* node, t_localisation robot,t_map* map, int* tableaualeatoire, int max_depth) {

    int* tableau=malloc(sizeof(int)*(node->nbSons-1));


    if(node->depth==max_depth) {
        return;
    }

    for (int i=0;i<node->nbSons;i++)
    {
        t_localisation robot_temp=robot;
        if(map->soils[robot_temp.pos.y][robot_temp.pos.x]==2)
            {
            Erg(&robot_temp,tableaualeatoire[i]);
        }
        else {
            updateLocalisation(&robot_temp,tableaualeatoire[i]);

        }
        node->sons[i]->movement=tableaualeatoire[i];



        if(robot_temp.pos.x>=map->x_max || robot_temp.pos.y>=map->y_max || robot_temp.pos.x<0 || robot_temp.pos.y<0 || node->parent->value>=500) {
        node->sons[i]->value=10000;
        }
        else if(tableaualeatoire[i]==1)
        {
            if(Survol1(robot,map)) {
                node->sons[i]->value=10000;
            }
            else {
                node->sons[i]->value=map->costs[robot_temp.pos.y][robot_temp.pos.x];
            }


        }
        else if(tableaualeatoire[i]==2)
        {
            if(Survol2(robot,map)) {
                node->sons[i]->value=10000;
            }
            else {
                node->sons[i]->value=map->costs[robot_temp.pos.y][robot_temp.pos.x];
            }

        }

        else {
            node->sons[i]->value=map->costs[robot_temp.pos.y][robot_temp.pos.x];
        }

        int k = 0;
        for (int j = 0; j < node->nbSons; j++) {
            if (j != i) {
                tableau[k] = tableaualeatoire[j];
                k++;

            }
        }k=0;
        if (node->sons[i]->value>500) {
            node->sons[i]->nbSons=0;
            node->sons[i]->depth=max_depth;
        }
        //printf("POSITION ROBOT : %d %d et orientation : %d  et cout : %d\n",robot_temp.pos.x,robot_temp.pos.y,robot_temp.ori,node->sons[i]->value);//

        remplir_arbre(node->sons[i],robot_temp,map,tableau,max_depth);





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

int Survol1(t_localisation robot,t_map* map) {
    t_localisation robot_temp=robot;
    updateLocalisation(&robot_temp,0);

    if(robot_temp.pos.x>=map->x_max || robot_temp.pos.y>=map->y_max || robot_temp.pos.x<0 || robot_temp.pos.y<0) {
        return 1;
    }
     if(map->costs[robot_temp.pos.y][robot_temp.pos.x]>500) {
        return 1;

    }
        return 0;

}
int Survol2(t_localisation robot,t_map* map) {
    if(Survol1(robot,map)) {
        return 1;
    }
    t_localisation robot_temp=robot;
    updateLocalisation(&robot_temp,1);

    if(robot_temp.pos.x>=map->x_max || robot_temp.pos.y>=map->y_max || robot_temp.pos.x<0 || robot_temp.pos.y<0) {
        return 1;
    }
    if(map->costs[robot_temp.pos.y][robot_temp.pos.x]>500) {
        return 1;

    }
    return 0;

}



void Erg(t_localisation* robot,t_move mouvement) {
    if (mouvement == 0 || mouvement == 3 || mouvement == 4 || mouvement == 5) {
        return;
    }
    if (mouvement == 1) {
        updateLocalisation(robot,0);
        return;
    }
    if (mouvement == 2) {
        updateLocalisation(robot,1);
        return;
    }
    if (mouvement == 6) {


        srand(time(NULL));
        int direction=(rand() % 2)+4;
        updateLocalisation(robot, direction);
        return;
    }




}








//allocation de la mémoire de tableau dans le main//
void dfs(t_node *node,t_node**tableau,int*   compteur,int max_depth)
{

    tableau[*compteur]=node;
    (*compteur)++;
    if(node->depth<max_depth && node->value<=500) {
        for (int i=0;i<node->nbSons;i++) {
            dfs(node->sons[i],tableau,compteur,max_depth);
        }
    }

}

//taille c'est le compteur de la fonction d'au dessus//
t_node* low_node(t_node **tableau,int taille,int max_depth) {
    int  min_cost=COST_UNDEF;
    t_node* pbestnode=NULL;
    for (int i=0;i<taille;i++) {

        if(tableau[i]->value < min_cost && tableau[i]->depth==max_depth) {
            min_cost=tableau[i]->value;
            pbestnode=tableau[i];
        }

    }
    return  pbestnode;
}



int produit(int nbMouvements, int d) {
    int resultat = 1;
    for (int k = 0; k < d; k++) {
        resultat *= (nbMouvements - k);
    }
    return resultat;
}


int calculer_total_noeuds(int nbMouvements,int max_depth) {
    int total = 0;

    for (int d = 0; d <= max_depth; d++) {
        total += produit(nbMouvements, d);
    }

    return total;
}

void free_tree(t_node* node) {
    if (!node) return;
    for (int i = 0; i < node->nbSons; i++) {
        free_tree(node->sons[i]);
    }
    free(node);
}


