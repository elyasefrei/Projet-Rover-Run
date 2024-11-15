#include "tree.h"
#include <stdio.h>
#include "map.h"

//allocation de la mémoire de tableau dans le main//
void dfs(t_node *node, int MAX_DEPTH,t_node**tableau,int* compteur)
{

    tableau[*compteur]=node;
    compteur++;
    if(node->depth<MAX_DEPTH && node->value<=500) {
        for (int i=0;i<node->nbSons;i++) {
            dfs(node->sons[i],MAX_DEPTH,tableau,compteur);
        }
    }

}

//taille est le compteur de la fonction d'au dessus//
t_node* low_node(t_node **tableau,int taille, int MAX_DEPTH) {
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
/*
t_node* ResearchVal(t_node *node, int MAX_DEPTH, int min_cost,t_node *Bestnode) {
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
