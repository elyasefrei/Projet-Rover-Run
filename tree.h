#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H
#define MVT_TOTAL 100
#define NBR_MVT 9
    typedef struct s_node
    {
        int value;
        int movement;
        int depth;
        struct s_node **sons;
        int nbSons;
        struct s_node *parent;
    } t_node;

t_node * create_node(int depth, int nbSons, t_node* parent);
void create_children(t_node *parent, int maxDepth);
int* mouvement_aleatoire(int n );
int* create_tableau(int n);
void dfs(t_node *node, int MAX_DEPTH,t_node**tableau,int* compteur);
t_node* low_node(t_node **tableau,int taille, int MAX_DEPTH);

#endif //UNTITLED1_TREE_H
