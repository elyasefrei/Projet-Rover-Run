#include <stdio.h>
#include <stdlib.h>
#include "tree.h"


t_node * create_node(int value, int depth, int nbSons) {
    t_node *node = malloc(sizeof(t_node));
    node->value = value;
    node->depth = depth;
    node->nbSons = nbSons;
    node->sons = malloc(nbSons * sizeof(t_node *));
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
        parent->sons[i] = create_node(parent->value + 1, parent->depth + 1, parent->nbSons - 1);
        create_children(parent->sons[i], maxDepth);
    }
}

