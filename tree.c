#include <stdio.h>
#include <stdlib.h>
#include "tree.h"


#include <stdio.h>
#include <stdlib.h>
#include "tree.h"


t_node * create_node(int depth, int nbSons, t_node* parent) {
    t_node *node = malloc(sizeof(t_node));
    node->value = 0;
    node->depth = depth;
    node->nbSons = nbSons;
    node->sons = malloc(nbSons * sizeof(t_node *));
    node->movement=0;
    node->parent=parent;
    for (int i = 0; i < nbSons; i++) {
        node->sons[i] = NULL;
    }
    return node;
}


void create_children(t_node *parent, int maxDepth) {
    if (parent->depth >= maxDepth) {
        return;
    }

    for (int i = 0; i < parent->nbSons; i++) {
        parent->sons[i] = create_node(parent->depth + 1, parent->nbSons - 1,parent);
        create_children(parent->sons[i], maxDepth);
    }
}

void printTree(t_node* root) {
    if (root == NULL) {
        return;  // Arbre vide ou fin de branche
    }

    printf("Valeur: %d, Mouvement: %d, Profondeur: %d, NbSons: %d\n",
           root->value, root->movement, root->depth, root->nbSons);

    // Parcourir tous les fils
    for (int i = 0; i < root->nbSons; i++) {
        printTree(root->sons[i]);  
    }
}


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
}
*/

