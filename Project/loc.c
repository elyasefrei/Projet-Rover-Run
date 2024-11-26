//
// Created by flasque on 19/10/2024.
//

#include "loc.h"


// structure de la localisation du robot
t_localisation loc_init(int x, int y, t_orientation ori)
{
    t_localisation loc;
    loc.pos.x = x;
    loc.pos.y = y;
    loc.ori = ori;
    return loc;
}
/*-------------------------------------------------------------------------------------------------------------------- */
/* 
* @brief fonction qui permet de savoir si la position ou la nouvelle position du robot est comprise dans la map
* @param loc : prend la position du robot
* @param x_max : prend la taille maximal en x de la map
* @param y_max : prend la taille maximal en y de la map
* @return 0 si la position n'est pas valide et 1 si la position est valide
*/
int isValidLocalisation(t_position loc, int x_max, int y_max)
{
    return (loc.x >= 0 && loc.x < x_max && loc.y >= 0 && loc.y < y_max);
}
/*-------------------------------------------------------------------------------------------------------------------- */
/*
* @brief    fonction qui permet de faire bouger le robot à gauche
* @param pos : prend la position du robot
* @return la nouvelle position du robot 
*/
    
t_position LEFT(t_position pos)
{
    t_position new_pos;
    new_pos.x = pos.x - 1;
    new_pos.y = pos.y;
    return new_pos;
}

/*-------------------------------------------------------------------------------------------------------------------- */
/*
* @brief  fonction qui permet de faire bouger le robot à droite
* @param pos : prend la position du robot
* @return la nouvelle position du robot 
*/

t_position RIGHT(t_position pos)
{
    t_position new_pos;
    new_pos.x = pos.x + 1;
    new_pos.y = pos.y;
    return new_pos;
}
/*-------------------------------------------------------------------------------------------------------------------- */
/*
* @brief  fonction qui permet de faire monter un rang la position du robot
* @param pos : prend la position du robot
* @return la nouvelle position du robot 
*/

t_position UP(t_position pos)
{
    t_position new_pos;
    new_pos.x = pos.x;
    new_pos.y = pos.y - 1;
    return new_pos;
}
/*-------------------------------------------------------------------------------------------------------------------- */
/*
* @brief   fonction qui permet de faire descendre un rang la position du robot
* @param pos : prend la position du robot
* @return la nouvelle position du robot 
*/

t_position DOWN(t_position pos)
{
    t_position new_pos;
    new_pos.x = pos.x;
    new_pos.y = pos.y + 1;
    return new_pos;
}

