#ifndef PROJEKT_5_GLOBALS_H
#define PROJEKT_5_GLOBALS_H

#include <stdlib.h>
#include <string.h>

#define MAP_SIZE_X      20
#define MAP_SIZE_Y      15
#define DIR_WITH_MAPS   "../maps/"
#define FILE_WITH_SCORE "../score.txt"
#define CLEAR_COMMAND   "clear"

// Markings on the map
#define EMPTY_FIELD             ' '
#define PLAYER                  'P'
#define BOX                     'B'
#define DESTINATION             'D'
#define PLAYER_IN_DESTINATION   'C'
#define BOX_IN_DESTINATION      'G'

// Graphical representation (Unicode chars)
#define CHAR_PLAYER                 "\u23e3"
#define CHAR_BOX                    "\u25A2"
#define CHAR_DESTINATION            "\u25A0"
#define CHAR_PLAYER_IN_DESTINATION  "\u25C9"
#define CHAR_BOX_IN_DESTINATION     "\u25A3"
#define CHAR_WALL                   "\u25A8"

// player controls
#define P_UP    'w'
#define P_LEFT  'a'
#define P_DOWN  's'
#define P_RIGHT 'd'
#define P_EXIT  'k'

struct MapOfGame {
    int     map[MAP_SIZE_Y][MAP_SIZE_X];
    int     posX;
    int     posY;
    int     steps;
    int     playerWon;
    char    mapName[50];
};
#endif //PROJEKT_5_GLOBALS_H
