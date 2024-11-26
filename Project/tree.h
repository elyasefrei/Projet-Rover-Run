#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H
#define MVT_TOTAL 100
#define NBR_MVT 9
#define MAX_DEPTH_INIT 5
#include "moves.h"
#include "map.h"
    typedef struct s_node
    {
        int value;
        int movement;
        int depth;
        struct s_node **sons;
        int nbSons;
        struct s_node *parent;
    } t_node;

t_node * create_node(int depth, int nbSons, t_node* parent,int max_depth);
void create_children(t_node *parent,int max_depth);

void dfs(t_node *node,t_node**tableau,int* compteur,int max_depth);
t_node* low_node(t_node **tableau,int taille,int max_depth);
void remplir_arbre(t_node* node, t_localisation robot,t_map* map, int* tableaualeatoire,int max_depth);
void printTree(t_node* root);
int calculer_total_noeuds(int nbMouvements,int max_depth);
int produit(int nbMouvements, int d);
int Survol1(t_localisation robot,t_map* map);
int Survol2(t_localisation robot,t_map* map);
void Erg(t_localisation* robot,t_move mouvement);
void free_tree(t_node* node);


#endif //UNTITLED1_TREE_H