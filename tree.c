#include <stdio.h>
#include <stdlib.h>
#include "tree.h"


t_node * create_node(int depth, int nbSons, t_node* parent) {
    t_node *node = malloc(sizeof(t_node));
    node->value = 0;
    node->depth = depth;
    if(depth==MAX_DEPTH) {
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


void create_children(t_node *parent) {
    if (parent->depth >= MAX_DEPTH) {
        return;
    }

    for (int i = 0; i < parent->nbSons; i++) {
        parent->sons[i] = create_node(parent->depth + 1, parent->nbSons - 1,parent);
        create_children(parent->sons[i]);
    }
}

