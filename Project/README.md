
# Projet Rover Run!
Contributeurs: SHAN Yanick, TARZET Elyas, GUIEME Victor

liens github: https://github.com/elyasefrei/projet_c_efrei/tree/main/Project

Notre projet consiste a crée un mini jeu d'un robot sur mars qui doit retrouver son chemin pour aller a la base. Chaque phase le robot devra trouvez la combinaison de mouvement le plus efficace pour etre le plus proche de la base qui est la condition de fin de notre jeu.

## Prérequis

- Un IDE de votre choix
- Compilateur C

## Installation

- Clonez le repository GitHub sur votre environnement local.
- Importez tous les fichiers dans votre IDE.
- Compilez et exécutez le programme.

## Utilisation 
Comment le programme fonctionne

### 1) Création de la map 
1)  createMapFromFile() : Elle permet de créer une carte de Mars à partir du fichier example1.map
2) Afficher une map où on a les costs , et une map où on a les différents type de terrain possible.

### 2) Initialisation du robot 
1) On utilise avec la structure t_localisation 
- La structure t_localisation contient pos et ori
- pos représente les coordonnées (x, y) du robot.
- ori représente l’orientation du robot.

### 3) Création de l'arbre n-aires 
1) On va d'abord crée la racine de l'arbre avec un create_node
2) Ensuite avec cette racine on va pouvoir crée tous les noeuds de arbres avec create_children(root,max_depth).
-  Cette fonction crée tous les noeuds avec leurs parents et leurs profondeurs correspondantes. À ce stade, les valeurs et les mouvements restent NULL car ils n’ont pas encore été définis.
3) Un parent fictif a été créé pour pallier le problème de l’absence de parent pour la racine 
4) Par la suite on a crée le tableau aléatoire qui va être découper en deux partie:
-La première étape consiste à créer un tableau avec tous les mouvements possibles et leurs probabilités respectives.
- La deuxième étape consiste à réorganiser ce tableau de manière aléatoire. 
5) Après la création du tableau avec les mouvements aléatoire on peut enfin remplir notre arbre avec notre fonction "remplir_arbre"

#### - Dans cette fonction, certaines conditions sont déjà posées :
- Par exemple, pour un terrain de type Erg, on utilise la fonction Erg() si ce type est rencontré. Cette fonction applique différents effets aux mouvements du robot.
- Dans la fonction remplir_arbre, si la position du robot dépasse les limites de la carte, le coût est automatiquement fixé à 10 000. De plus, si le coût du parent du noeud est supérieur ou égal à 10 000, le remplissage de cette branche est arrêté, et on passe à la suivante.
-  Enfin, pour éviter que les mouvements du robot survolent des crevasses lors du remplissage des nœuds, deux fonctions, Survol1 et Survol2, sont utilisées. Ces deux fonctions permettent de vérifier respectivement les mouvements 20 et 30 pour déterminer si le robot survole ou non une crevasse pendant son déplacement. Si oui, la valeur du noeud est fixée à 10 000.

### 4) Trouver le chemin le plus avec le cost minimal 
-  La fonction dfs(t_node *node, t_node **tableau, int *compteur, int max_depth) est utilisée: Elle permet de convertir l’arbre n-aire en un tableau contenant tous ses nœuds.
- Ensuite, grâce à la fonction low_node(t_node **tableau, int taille, int max_depth), on identifie le noeud avec le coût minimal.
- Enfin, deux fonctions sont implémentées : la première récupère les mouvements à effectuer depuis le noeud au coût minimal en remontant avec ses parents, et la deuxième applique ces mouvements.

#### les deux instructions sont :
-    
        t_node* Bestnode = low_node(tableau, compteur,max_depth);
        printf("VALEUR %d\n", Bestnode->value);

        printf("\nROBOT DEBUT DE PHASE : %d %d %s\n", robot.pos.x, robot.pos.y, getoriAsString(robot.ori));

        // Récupérer les mouvements depuis le meilleur noeud
        int tab_mvt[max_depth];
        for (int i = max_depth - 1; i >= 0; i--) {
            tab_mvt[i] = Bestnode->movement;
            Bestnode = Bestnode->parent;
        }

-
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



