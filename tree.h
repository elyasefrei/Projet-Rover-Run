#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H
#define MVT_TOTAL 100
#define NBR_MVT 8
#define MAX_DEPTH 5
#include "moves.h"
#include "map.h"
/**
 * @brief Structure représentant un nœud de l'arbre de mouvements
 */
typedef struct s_node
{
    int value;
    int movement;
    int depth;
    struct s_node **sons;
    int nbSons;
    struct s_node *parent;
} t_node;

/**
 * @brief Fonction pour créer un nœud
 * @param depth La profondeur du nœud
 * @param nbSons Le nombre d'enfants du nœud
 * @param parent Pointeur vers le parent du nœud
 * @return Le nœud créé
 */
t_node * create_node(int depth, int nbSons, t_node* parent);

/**
 * @brief Fonction pour créer les enfants d'un nœud
 * @param parent Le parent du nœud
 * @return Aucun retour
 */
void create_children(t_node *parent);

/**
 * @brief Fonction pour générer un tableau de mouvements aléatoires
 * @param n La taille du tableau
 * @return Le tableau de mouvements
 */
int* mouvement_aleatoire(int n );

/**
 * @brief Fonction pour créer un tableau
 * @param n La taille du tableau
 * @return Le tableau créé
 */
int* create_tableau(int n);

/**
 * @brief Fonction de recherche DFS
 * @param node Le nœud à explorer
 * @param tableau Tableau de nœuds explorés
 * @param compteur Compteur pour les nœuds
 * @return Aucun retour
 */
void dfs(t_node *node,t_node**tableau,int* compteur);

/**
 * @brief Fonction pour trouver le nœud avec la valeur la plus basse
 * @param tableau Tableau de nœuds
 * @param taille Taille du tableau
 * @return Le nœud avec la valeur la plus basse
 */
t_node* low_node(t_node **tableau,int taille);

/**
 * @brief Fonction pour remplir l'arbre
 * @param node Le nœud à explorer
 * @param robot Localisation du robot
 * @param map La carte
 * @param tableaualeatoire Tableau des mouvements
 * @return Aucun retour
 */
void remplir_arbre(t_node* node, t_localisation robot,t_map* map, int* tableaualeatoire);

/**
 * @brief Fonction pour imprimer l'arbre
 * @param root Le nœud racine
 * @return Aucun retour
 */
void printTree(t_node* root);

/**
 * @brief Fonction pour calculer le total des nœuds
 * @param nbMouvements Nombre de mouvements
 * @return Le nombre total de nœuds
 */
int calculer_total_noeuds(int nbMouvements);

/**
 * @brief Fonction pour calculer le produit du nombre de mouvements et de la profondeur
 * @param nbMouvements Nombre de mouvements
 * @param d La profondeur
 * @return Le produit des deux
 */
int produit(int nbMouvements, int d);

/**
 * @brief Fonction de survol 1
 * @param robot La localisation du robot
 * @param map La carte
 * @return Le coût de l'option
 */
int Survol1(t_localisation robot,t_map* map);

/**
 * @brief Fonction de survol 2
 * @param robot La localisation du robot
 * @param map La carte
 * @return Le coût de l'option
 */
int Survol2(t_localisation robot,t_map* map);

#endif //UNTITLED1_TREE_H
