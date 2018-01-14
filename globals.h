//
// Created by ziken on 13.01.18.
//

#ifndef PROJEKT_5_GLOBALS_H
#define PROJEKT_5_GLOBALS_H

#include <stdlib.h>
#include <string.h>

#define MAP_SIZE_X 20
#define MAP_SIZE_Y 15
struct MapOfGame {
    int map[MAP_SIZE_Y][MAP_SIZE_X];
    int posX;
    int posY;
    int steps;
    int playerWon;
    int isError;
};

#endif //PROJEKT_5_GLOBALS_H
