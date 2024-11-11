#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

    typedef struct s_node
    {
        int value;
        int depth;
        struct s_node **sons;
        int nbSons;
    } t_node;

t_node * create_node(int value, int depth, int nbSons);

void create_children(t_node *parent, int maxDepth);

#endif //UNTITLED1_TREE_H
