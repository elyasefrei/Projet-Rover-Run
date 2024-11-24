#include "tree.h"
#include <stdio.h>
#include "map.h"

//allocation de la mémoire de tableau dans le main//
void dfs(t_node *node,t_node**tableau,int*   compteur)
{

    tableau[*compteur]=node;
    (*compteur)++;
    if(node->depth<MAX_DEPTH && node->value<=500) {
        for (int i=0;i<node->nbSons;i++) {
            dfs(node->sons[i],tableau,compteur);
        }
    }

}

//taille c'est le compteur de la fonction d'au dessus//
t_node* low_node(t_node **tableau,int taille) {
    int  min_cost=COST_UNDEF;
    t_node* pbestnode=NULL;
    for (int i=0;i<taille;i++) {

        if(tableau[i]->value < min_cost && tableau[i]->depth==MAX_DEPTH) {
            min_cost=tableau[i]->value;
            pbestnode=tableau[i];
        }

    }
    return  pbestnode;
}


//Recursif mais ne marche pas//
/*t_node* ResearchVal(t_node *node, int MAX_DEPTH, int min_cost,t_node *Bestnode) {
    if (node->depth != MAX_DEPTH) {
        for(int i=0;i<node->nbSons;i++) {
            ResearchVal(node->sons[i], MAX_DEPTH, min_cost,Bestnode);
        }
    }
    else {
        if(node->value<min_cost){
            min_cost=node->value;
            Bestnode=node;
            return Bestnode;

        }
    }
}*/



int produit(int nbMouvements, int d) {
    int resultat = 1;
    for (int k = 0; k < d; k++) {
        resultat *= (nbMouvements - k);
    }
    return resultat;
}


int calculer_total_noeuds(int nbMouvements) {
    int total = 0;

    for (int d = 0; d <= MAX_DEPTH; d++) {
        total += produit(nbMouvements, d);
    }

    return total;
}
