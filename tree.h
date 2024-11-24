#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H
#define MVT_TOTAL 100
#define NBR_MVT 8
#define MAX_DEPTH 5
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

t_node * create_node(int depth, int nbSons, t_node* parent);
void create_children(t_node *parent);
int* mouvement_aleatoire(int n );
int* create_tableau(int n);
void dfs(t_node *node,t_node**tableau,int* compteur);
t_node* low_node(t_node **tableau,int taille);
void remplir_arbre(t_node* node, t_localisation robot,t_map* map, int* tableaualeatoire);
void printTree(t_node* root);
int calculer_total_noeuds(int nbMouvements);
int produit(int nbMouvements, int d);

#endif //UNTITLED1_TREE_H
