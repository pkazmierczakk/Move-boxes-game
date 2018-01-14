#ifndef PROJEKT_5_GAME_H
#define PROJEKT_5_GAME_H

#include "globals.h"
#define PLAYER 80 // P
#define BOX 66 // B
#define DESTINATION 68 // D
#define PLAYER_IN_DESTINATION 67 // C
#define BOX_IN_DESTINATION 71 // G

#define CHAR_PLAYER "\u25cb"
#define CHAR_BOX "\u25A2"
#define CHAR_DESTINATION "\u25A0"
#define CHAR_PLAYER_IN_DESTINATION "\u25C9"
#define CHAR_BOX_IN_DESTINATION "\u25A3"


// printf("\u23fa \u25cb \u25C9 \u25A0 \u25A2 \u25A3\n");
void startGame(struct MapOfGame);

#endif //PROJEKT_5_GAME_H
