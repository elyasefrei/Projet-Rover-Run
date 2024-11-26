#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "tree.h"
#include "moves.h"
#include "loc.h"


int main() {
    // Création de la carte
    t_map map = createMapFromFile("..\\maps\\example1.map");
    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);

    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }

    // Affichage des coûts alignés à gauche (5 caractères)
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);

    // Initialisation de la localisation du robot
    t_localisation robot = loc_init(5, 4, NORTH);

    // Boucle principale
    int max_depth_next=MAX_DEPTH_INIT;
    while (robot.pos.x < map.x_max && robot.pos.y < map.y_max &&
           robot.pos.x >= 0 && robot.pos.y >= 0 &&
           map.costs[robot.pos.y][robot.pos.x] < 1000 &&
           map.costs[robot.pos.y][robot.pos.x] != 0) {

       int max_depth=max_depth_next;
        max_depth_next=MAX_DEPTH_INIT;
        // Création de l'arbre pour chaque itération
        t_node *root = create_node(0, NBR_MVT, NULL,max_depth); // Racine avec NBR_MVT mouvements possibles
        create_children(root,max_depth); // Création récursive des enfants
        t_node *parent_fictif = create_node(0, 1, NULL,max_depth); // Parent fictif
        root->parent = parent_fictif;


        printf("Arbre cree jusqu'a une profondeur de %d.\n", max_depth);

        // Génération aléatoire des mouvements
        int* tableau_aleatoire = mouvement_aleatoire(NBR_MVT);

        for (int i = 0; i < NBR_MVT; i++) {
            printf("mouvement %d %d\n", i, tableau_aleatoire[i]);
        }

        // Remplir l'arbre avec les mouvements aléatoires
        remplir_arbre(root, robot, &map, tableau_aleatoire,max_depth);
        free(tableau_aleatoire); // Libération immédiate après utilisation

        // Allocation du tableau pour DFS
        t_node** tableau = malloc(sizeof(t_node*) * calculer_total_noeuds(NBR_MVT,max_depth));

        int compteur = 0;
        dfs(root, tableau, &compteur,max_depth);

        // Trouver le meilleur nœud
        t_node* Bestnode = low_node(tableau, compteur,max_depth);
        printf("VALEUR %d\n", Bestnode->value);

        printf("\nROBOT DEBUT DE PHASE : %d %d %s\n", robot.pos.x, robot.pos.y, getoriAsString(robot.ori));

        // Récupérer les mouvements depuis le meilleur nœud
        int tab_mvt[max_depth];
        for (int i = max_depth - 1; i >= 0; i--) {
            tab_mvt[i] = Bestnode->movement;
            Bestnode = Bestnode->parent;
        }

        // Appliquer les mouvements
        for (int i = 0; i < max_depth; i++) {
            if (map.soils[robot.pos.y][robot.pos.x] == 2) {

                printf("ERG[%s]->", getMoveAsString(tab_mvt[i]));
                Erg(&robot, tab_mvt[i]);
                if(tab_mvt[i]==6) {
                    printf("new ori[%s]->",_oris[robot.ori]);
                }

            }

            else {
                if(map.soils[robot.pos.y][robot.pos.x] == 3 && max_depth_next >0) {
                    max_depth_next--;
                }
                updateLocalisation(&robot, tab_mvt[i]);
                printf("%s->", getMoveAsString(tab_mvt[i]));
            }
        }

        printf("\nposition robot fin de phase x y : %d %d %s ", robot.pos.x, robot.pos.y, getoriAsString(robot.ori));
        printf("\ncout associe:%d\n", map.costs[robot.pos.y][robot.pos.x]);
        printf(" \n %d REG SOILS ENCOUNTER %d MOVEMENT FOR NEXT PHASE\n",MAX_DEPTH_INIT-max_depth_next,max_depth_next);

        // Libération de l'arbre et du tableau DFS après utilisation
        free(tableau);
        free_tree(root);
        free_tree(parent_fictif);

    }

    return 0;
}
