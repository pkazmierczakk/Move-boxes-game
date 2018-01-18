#include <stdlib.h>
#include "game.h"
#include "playersupport.h"

void printMap(struct MapOfGame * m) {
    int c;
    int ifPlayerWon = 1;
    for (int i = 0; i < MAP_SIZE_Y; i++) {
        for (int j = 0; j < MAP_SIZE_X; j++) {

            if (i == m->posY && j == m->posX) {
                if (m->map[i][j] == DESTINATION) {
                    printf("%-4s",CHAR_PLAYER_IN_DESTINATION);
                } else {
                    printf("%-4s",CHAR_PLAYER);
                }
                continue;
            }

            c = m->map[i][j];
            switch (c) {
                case BOX:
                    // If at least one box is on the board that means that player still does not won.
                    ifPlayerWon = 0;
                    printf("%-4s",CHAR_BOX);
                    break;
                case PLAYER_IN_DESTINATION:
                    printf("%-4s",CHAR_PLAYER_IN_DESTINATION);
                    break;
                case BOX_IN_DESTINATION:
                    printf("%-4s",CHAR_BOX_IN_DESTINATION);
                    break;
                case DESTINATION:
                    printf("%-4s",CHAR_DESTINATION);
                    break;
                case '+':
                    printf("%-4s", CHAR_WALL);
                    break;
                case '|':
                    printf("%-4s", CHAR_WALL);
                    break;
                case '-':
                    printf("%-4s", CHAR_WALL);
                    break;
                default:
                    printf("%-2s", "");
            }
        }
        printf("\n");
    }
    m->playerWon = ifPlayerWon;
}
int getFieldUnderBox(struct MapOfGame *m, int x, int y) {
    if (m->map[y][x] == BOX_IN_DESTINATION) {
        return DESTINATION;
    } else {
        return EMPTY_FIELD;
    }
}
int canPushBox(struct MapOfGame *m, int nextX, int nextY, int prevX, int prevY) {
    int *c = &m->map[m->posY+nextY][m->posX+nextX];

    if (*c == EMPTY_FIELD) {
        m->map[m->posY+prevY][m->posX+prevX] = getFieldUnderBox(m, m->posX + prevX, m->posY + prevY);
        *c = BOX;
        return 1;
    } else if (*c == DESTINATION) {
        m->map[m->posY+prevY][m->posX+prevX] = getFieldUnderBox(m, m->posX + prevX, m->posY + prevY);
        *c = BOX_IN_DESTINATION;
        return 1;
    }
    return 0;
}
void movePlayer(struct MapOfGame * m, int direction) {
    int c;
    m->steps++;
    if (direction == P_UP) {
        c = m->map[m->posY-1][m->posX];
        if (c == EMPTY_FIELD || c == DESTINATION) {
            m->posY--;
        } else if (c == BOX || c == BOX_IN_DESTINATION) {
            if (canPushBox(m, 0, -2, 0, -1) == 1) {
                m->posY--;
            }
        }
    } else if (direction == P_LEFT) {
        c = m->map[m->posY][m->posX-1];
        if (c == EMPTY_FIELD || c == DESTINATION) {
            m->posX--;
        } else if (c == BOX || c == BOX_IN_DESTINATION) {
            if (canPushBox(m, -2, 0, -1, 0) == 1) {
                m->posX--;
            }
        }
    } else if (direction == P_DOWN) {
        c = m->map[m->posY+1][m->posX];
        if (c == EMPTY_FIELD || c == DESTINATION) {
            m->posY++;
        } else if (c == BOX || c == BOX_IN_DESTINATION) {
            if (canPushBox(m, 0, 2, 0, 1) == 1) {
                m->posY++;
            }
        }
    } else if (direction == P_RIGHT) {
        c = m->map[m->posY][m->posX+1];
        if (c == EMPTY_FIELD || c == DESTINATION) {
            m->posX++;
        } else if (c == BOX || c == BOX_IN_DESTINATION) {
            if (canPushBox(m, 2, 0, 1, 0) == 1) {
                m->posX++;
            }
        }
    }
}
int getch()
{
    system ("/bin/stty raw");
    int ret = getchar();
    system ("/bin/stty cooked");
    return ret;
}

void startGame(struct MapOfGame * m) {
    int c = 0;
    while(c != P_EXIT && m->playerWon != 1) {
        system("clear");
        printMap(m);
        c = getch();
        movePlayer(m, c);
    }

    m->steps--;
}