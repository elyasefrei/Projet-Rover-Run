#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "loc.h"
#include "map.h"
#include "moves.h"
#include "time.h"

/*-------------------------------------------------------------------------------------------------------------------- */
/* 
* @brief Création d'un noeud de l'arbre 
* @param depth : Depth permet d'assigner la profondeur de notre nouveau nœud créé.
* @param nbSons : Il désigne le nombre de fils possibles, plus précisément le nombre de choix de mouvements que le robot peut effectuer.
* @param parent : parent désigne le noeud parent du noeud crée 
* @param max_depth : max_depth représente la profondeur maximale que notre arbre peut atteindre.
* @return il va nous retourner un nouveau noeud 
*/
t_node * create_node(int depth, int nbSons, t_node* parent,int max_depth) {
    t_node *node = malloc(sizeof(t_node));
    node->value = 0;
    node->depth = depth;
    if(depth==max_depth) {
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

/*-------------------------------------------------------------------------------------------------------------------- */
/* 
* @brief Fonction récursive qui crée des nœuds enfants à partir d'un nœud parent, jusqu'à atteindre une certaine profondeur maximale
* @param parent : parent désigne le noeud parent de l'enfant crée 
* @param max_depth : max_depth représente la profondeur maximale que notre arbre peut atteindre.
* @return Un arbre n-aires 
*/
void create_children(t_node *parent, int max_depth) {
    if (parent->depth >= max_depth) {
        return;
    }

    for (int i = 0; i < parent->nbSons; i++) {
        parent->sons[i] = create_node(parent->depth + 1, parent->nbSons - 1,parent,max_depth);
        create_children(parent->sons[i],max_depth);
    }
}


/*-------------------------------------------------------------------------------------------------------------------- */
/* 
* @brief Fonction qui remplit l'arbre n-aires en ajoutant les "costs", les nouvelles positions du robot et les mouvements effectués par le robot
* @param node : Prend en paramètre un noeud.
* @param robot : Prend en paramètre les coordonnées du robot.
* @param map : Prend en paramètre la carte générée ( carte qui représente mars ).
* @param tableau_aleatoire : Prend en paramètre le tableau aléatoire.
* @param max_depth : max_depth représente la profondeur maximale que notre arbre peut atteindre.
* @return 
*/
void remplir_arbre(t_node* node, t_localisation robot,t_map* map, int* tableau_aleatoire, int max_depth) {

    int* tableau=malloc(sizeof(int)*(node->nbSons-1));


    if(node->depth==max_depth) {// si la profondeur de du noeud est égal a max_depth on sort de la fonction 
        return;
    }

    for (int i=0;i<node->nbSons;i++)
    {
        t_localisation robot_temp=robot;
        if(map->soils[robot_temp.pos.y][robot_temp.pos.x]==2)// si le robot atteint une case Erg
            {
            Erg(&robot_temp,tableau_aleatoire[i]); // il entre dans la fonction Erg
        }
        else {
            updateLocalisation(&robot_temp,tableau_aleatoire[i]); // sinon il entre dans la fonction updateLocalisation

        }
        node->sons[i]->movement=tableau_aleatoire[i];


        // si la position du robot est dehors de la map alors on met son cost a 10000
        if(robot_temp.pos.x>=map->x_max || robot_temp.pos.y>=map->y_max || robot_temp.pos.x<0 || robot_temp.pos.y<0 || node->parent->value>=500) {
        node->sons[i]->value=10000;
        }
        else if(tableau_aleatoire[i]==1)// si on tombe sur avancer de 10
        {
            if(Survol1(robot,map)) {
                node->sons[i]->value=10000;
            }
            else {
                node->sons[i]->value=map->costs[robot_temp.pos.y][robot_temp.pos.x];
            }


        }
        else if(tableau_aleatoire[i]==2)
        {
            if(Survol2(robot,map)) {
                node->sons[i]->value=10000;
            }
            else {
                node->sons[i]->value=map->costs[robot_temp.pos.y][robot_temp.pos.x];
            }

        }

        else {
            node->sons[i]->value=map->costs[robot_temp.pos.y][robot_temp.pos.x];
        }
        // Permet de retirer le mouvement qui a déjà été utilisé
        int k = 0;
        for (int j = 0; j < node->nbSons; j++) {
            if (j != i) {
                tableau[k] = tableau_aleatoire[j];
                k++;

            }
        }k=0;
        // Permet d'arrêter la fonction de remplissage de l'arbre si le coût dépasse 10 000.
        if (node->sons[i]->value>500) {
            node->sons[i]->nbSons=0;
            node->sons[i]->depth=max_depth;
        }
        //printf("POSITION ROBOT : %d %d et orientation : %d  et cout : %d\n",robot_temp.pos.x,robot_temp.pos.y,robot_temp.ori,node->sons[i]->value);//

        remplir_arbre(node->sons[i],robot_temp,map,tableau,max_depth);





    }
    free(tableau);

}

/*-------------------------------------------------------------------------------------------------------------------- */
/* 
* @brief Fonction qui permet d'afficher l'ensemble de l'arbre avec les informations associées.
* @param root : Prend en paramètre la racine donc tous l'arbre en question.
* @return 
*/
void printTree(t_node* root) {
    if (root == NULL) {
        return;  // Arbre vide ou fin de branche
    }

    // Afficher les informations du nœud actuel
    printf("Valeur: %d, Mouvement: %d, Profondeur: %d, NbSons: %d\n",
           root->value, root->movement, root->depth, root->nbSons);

    // Parcourir tous les fils
    for (int i = 0; i < root->nbSons; i++) {
        printTree(root->sons[i]);  // Appel récursif sur chaque fils
    }
}
/*-------------------------------------------------------------------------------------------------------------------- */
/* 
* @brief Fonction qui permet de vérifier si le déplacement de 20 ne survole pas une crevasse.
* @param robot : Prend en paramètre les coordonées du robot.
* @param map : Prend en paramètre la map de mars.
* @return 0 si il ne survole pas une creuvasse ou qu'il est pas en dehors de la map, 1 si c'est le contraire
*/
int Survol1(t_localisation robot,t_map* map) {
    t_localisation robot_temp=robot;
    updateLocalisation(&robot_temp,0);

    if(robot_temp.pos.x>=map->x_max || robot_temp.pos.y>=map->y_max || robot_temp.pos.x<0 || robot_temp.pos.y<0) {
        return 1;
    }
     if(map->costs[robot_temp.pos.y][robot_temp.pos.x]>500) {
        return 1;

    }
        return 0;

}
/*-------------------------------------------------------------------------------------------------------------------- */
/* 
* @brief Fonction qui permet de vérifier si le déplacement de 30 ne survole pas une crevasse.
* @param robot : Prend en paramètre les coordonées du robot.
* @param map : Prend en paramètre la map de mars.
* @return 0 si il ne survole pas une creuvasse ou qu'il est pas en dehors de la map, 1 si c'est le contraire
*/
int Survol2(t_localisation robot,t_map* map) {
    if(Survol1(robot,map)) {
        return 1;
    }
    t_localisation robot_temp=robot;
    updateLocalisation(&robot_temp,1);

    if(robot_temp.pos.x>=map->x_max || robot_temp.pos.y>=map->y_max || robot_temp.pos.x<0 || robot_temp.pos.y<0) {
        return 1;
    }
    if(map->costs[robot_temp.pos.y][robot_temp.pos.x]>500) {
        return 1;

    }
    return 0;

}

/*-------------------------------------------------------------------------------------------------------------------- */
/* 
* @brief Fonction qui permet d'appliquer l'effet d'Erg sur le robot.
* @param robot : Prend en paramètre les coordonées du robot.
* @param mouvement : Elle prend en paramètre le mouvement que va effectuer le robot
* @return
*/
void Erg(t_localisation* robot,t_move mouvement) {
    if (mouvement == 0 || mouvement == 3 || mouvement == 4 || mouvement == 5) {
        return;
    }
    if (mouvement == 1) {
        updateLocalisation(robot,0);
        return;
    }
    if (mouvement == 2) {
        updateLocalisation(robot,1);
        return;
    }
    if (mouvement == 6) {


        srand(time(NULL));
        int direction=(rand() % 2)+4;
        updateLocalisation(robot, direction);
        return;
    }




}








//allocation de la mémoire de tableau dans le main//
void dfs(t_node *node,t_node**tableau,int*   compteur,int max_depth)
{

    tableau[*compteur]=node;
    (*compteur)++;
    if(node->depth<max_depth && node->value<=500) {
        for (int i=0;i<node->nbSons;i++) {
            dfs(node->sons[i],tableau,compteur,max_depth);
        }
    }

}

//taille c'est le compteur de la fonction d'au dessus//
t_node* low_node(t_node **tableau,int taille,int max_depth) {
    int  min_cost=COST_UNDEF;
    t_node* pbestnode=NULL;
    for (int i=0;i<taille;i++) {

        if(tableau[i]->value < min_cost && tableau[i]->depth==max_depth) {
            min_cost=tableau[i]->value;
            pbestnode=tableau[i];
        }

    }
    return  pbestnode;
}



int produit(int nbMouvements, int d) {
    int resultat = 1;
    for (int k = 0; k < d; k++) {
        resultat *= (nbMouvements - k);
    }
    return resultat;
}


int calculer_total_noeuds(int nbMouvements,int max_depth) {
    int total = 0;

    for (int d = 0; d <= max_depth; d++) {
        total += produit(nbMouvements, d);
    }

    return total;
}

void free_tree(t_node* node) {
    if (!node) return;
    for (int i = 0; i < node->nbSons; i++) {
        free_tree(node->sons[i]);
    }
    free(node);
}


