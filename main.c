#include <stdio.h>
#include "map.h"
#include <stdlib.h>
#include <windows.h>
#include "robot.h"
#include "robot.c"

/* pas encore fini pour les mouvement, probleme avec les
*/

//const char* orientation_names[] = {"NORTH", "EAST", "SOUTH", "WEST"};

int main() {
    //t_map map = createMapFromFile("..\\maps\\example1.map");
    t_map map = createMapFromFile("C:\\Users\\yanic\\Desktop\\MARC-master\\MARC-master\\maps\\example1.map");
    t_localisation robot;
    t_localisation *probot = &robot;
    robot = loc_init(4,6,NORTH);
    printf("%d %d %d \n",robot.pos.y,robot.pos.x,robot.ori);
    updateLocalisation(probot,T_LEFT);
    printf("%d %d %d \n",probot->pos.y,probot->pos.x,robot.ori);

    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++){
            printf("%d ", map.soils[i][j]);

        }
        printf("\n");
    }

    // teste pour voir
    /*
    printf("%c", robot.id);
    printf("%d",map.soils[6][5]);
    printf("\n");
*/
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
           printf("%-5d ", map.costs[i][j]);

        }
        printf("\n");
    }
    displayMap(map);
    return 0;
}
