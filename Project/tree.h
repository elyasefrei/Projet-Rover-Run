#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H
#define MVT_TOTAL 100
#define NBR_MVT 9
#define MAX_DEPTH_INIT 5
#include "moves.h"
#include "map.h"


/**
 * @brief Structure du noeud
 */
typedef struct s_node
{
    int value; // le cost
    int movement;// mouvement robot
    int depth; // possition du noeud dans l'arbre
    struct s_node **sons; // Pointeur vers un tableau de nœuds enfants. Chaque nœud peut avoir plusieurs enfants.
    int nbSons; // nombres d'enfant possibles ( le reste des mouvements possibles)
    struct s_node *parent; // Pointeur vers son noeud parent
} t_node;

/**
* @brief Création d'un noeud 
* @param depth : La pronfondeur du noeud crée
* @param nbSons : Le nombres de fils qu'il possède ( les mouvements possibles )
* @param parent : le parent du noeud 
* @param max_depth : pronfondeur maximal de l'arbre
* @return the string corresponding to the move
*/
t_node * create_node(int depth, int nbSons, t_node* parent,int max_depth);

/**
 * @brief Fonction récursive qui crée des noeuds enfants à partir d'un nœud parent, jusqu'à atteindre une certaine profondeur maximale
 * @param parent : parent du noeud
 * @return 
 */
void create_children(t_node *parent,int max_depth);

/**
 * @brief Ajoute les nœuds dans le tableau fourni
 * @param node : Désigne un noeud dans l'arbre
 * @param tableau : tableau vide qui prend que des noeuds 
 * @param compteur : Indicateur de la position où le nœud doit être placé dans le tableau.
 * @param max_depth : Profondeur maximal de l'arbre.
 * @return
 */
void dfs(t_node *node,t_node**tableau,int* compteur,int max_depth);

/**
* @brief Fonction qui permet de chercher le noeud avec le coût minimal 
* @param tableau : Le tableau est rempli avec les nœuds de l'arbre.
* @param taille :  La taille du tableau, c'est-à-dire le nombre de noeuds présents dans le tableau.
* @param max_depth : Profondeur maximal de l'arbre.
* @return le noeud avec le coût minimal.
*/
t_node* low_node(t_node **tableau,int taille,int max_depth);

/**
* @brief Fonction qui remplit l'arbre n-aires en ajoutant les "costs", les nouvelles positions du robot et les mouvements effectués par le robot
* @param node : Prend en paramètre un noeud.
* @param robot : Prend en paramètre les coordonnées du robot.
* @param map : Prend en paramètre la carte générée ( carte qui représente mars ).
* @param tableau_aleatoire : Prend en paramètre le tableau aléatoire.
* @param max_depth: Profondeur maximal de l'arbre.
* @return 
*/
void remplir_arbre(t_node* node, t_localisation robot,t_map* map, int* tableau_aleatoire,int max_depth);

/* 
* @brief Fonction qui permet d'afficher l'ensemble de l'arbre avec les informations associées.
* @param root : Prend en paramètre la racine donc tous l'arbre en question.
* @return 
*/
void printTree(t_node* root);

/**
 * @brief Fonction qui va calculer le nombre totale de noeud
 * @param nbMouvements : nombres de mouvements possibles
 * @param max_depth : Profondeur maximal 
 * @return Un entier qui désigne le nombre total de noeuds dans l'arbre.
 */
int calculer_total_noeuds(int nbMouvements,int max_depth);

/**
 * @brief Fonction récursive qui calcule le produit des nombres de mouvements possibles sous forme de factorielle.
 * @param nbMouvement : nombres de mouvements possibles
 * @param d : un entier qui va être la valeur maximum qui soustrait nbMouvement
 * @return le produit
 */
int produit(int nbMouvements, int d);

/* 
* @brief Fonction qui permet de vérifier si le déplacement de 20 ne survole pas une crevasse.
* @param robot : Prend en paramètre les coordonées du robot.
* @param map : Prend en paramètre la map de mars.
* @return 0 si il ne survole pas une creuvasse ou qu'il est pas en dehors de la map, 1 si c'est le contraire
*/
int Survol1(t_localisation robot,t_map* map);

/* 
* @brief Fonction qui permet de vérifier si le déplacement de 30 ne survole pas une crevasse.
* @param robot : Prend en paramètre les coordonées du robot.
* @param map : Prend en paramètre la map de mars.
* @return 0 si il ne survole pas une creuvasse ou qu'il est pas en dehors de la map, 1 si c'est le contraire
*/
int Survol2(t_localisation robot,t_map* map);

/* 
* @brief Fonction qui permet d'appliquer l'effet d'Erg sur le robot.
* @param robot : Prend en paramètre les coordonées du robot.
* @param mouvement : Elle prend en paramètre le mouvement que va effectuer le robot
* @return
*/

void Erg(t_localisation* robot,t_move mouvement);

/**
 * @brief Fonction qui permet de libérer tous l'arbre
 * @param node : le noeud ou commence la suppression
 * @return 
 */
void free_tree(t_node* node);




#endif //UNTITLED1_TREE_H
