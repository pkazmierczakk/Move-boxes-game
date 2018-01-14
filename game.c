#include <stdlib.h>
#include "game.h"
#include "filesupport.h"

void printMap(struct MapOfGame * m) {
    int c;
    int ifPlayerWon = 1;
    for (int i = 0; i < MAP_SIZE_Y; i++) {
        for (int j = 0; j < MAP_SIZE_X; j++) {
            if (i == m->posY && j == m->posX) {
                if (m->map[i][j] == DESTINATION) {
                    printf("%4s",CHAR_PLAYER_IN_DESTINATION);
                } else {
                    printf("%4s",CHAR_PLAYER);
                }
                continue;
            }
            c = m->map[i][j];
            switch (c) {
                case BOX:
                    ifPlayerWon = 0;
                    printf("%4s",CHAR_BOX);
                    break;
                case PLAYER_IN_DESTINATION:
                    printf("%4s",CHAR_PLAYER_IN_DESTINATION);
                    break;
                case BOX_IN_DESTINATION:
                    printf("%4s",CHAR_BOX_IN_DESTINATION);
                    break;
                case DESTINATION:
                    printf("%4s",CHAR_DESTINATION);
                    break;
                case '+':
                    printf("%4s", "\u256c");
                    break;
                case '|':
                    printf("%4s", "\u2551");
                    break;
                case '-':
                    printf("%4s", "\u2550");
                    break;
                default:
                    printf("%2s", "");
            }
        }
        printf("\n");
    }
    m->playerWon = ifPlayerWon;
}
int getField(struct MapOfGame * m, int x, int y) {
    if (m->map[y][x] == BOX_IN_DESTINATION) {
        return DESTINATION;
    } else {
        return ' ';
    }
}
int canMoveBox(struct MapOfGame *m, int nextX, int nextY, int prevX, int prevY) {
    int *c = &m->map[m->posY+nextY][m->posX+nextX];

    if (*c == ' ') {
        m->map[m->posY+prevY][m->posX+prevX] = getField(m, m->posX+prevX, m->posY+prevY);
        *c = BOX;
        return 1;
    } else if (*c == DESTINATION) {
        m->map[m->posY+prevY][m->posX+prevX] = getField(m, m->posX+prevX, m->posY+prevY);
        *c = BOX_IN_DESTINATION;
        return 1;
    }
    return 0;
}
void movePlayer(struct MapOfGame * m, int direction) {
    int c;
    m->steps++;
    if (direction == 'w') {
        c = m->map[m->posY-1][m->posX];
        if (c == ' ' || c == DESTINATION) {
            m->posY--;
        } else if (c == BOX || c == BOX_IN_DESTINATION) {
            if (canMoveBox(m, 0, -2, 0, -1) == 1) {
                m->posY--;
            }
        }
    } else if (direction == 'a') {
        c = m->map[m->posY][m->posX-1];
        if (c == ' ' || c == DESTINATION) {
            m->posX--;
        } else if (c == BOX || c == BOX_IN_DESTINATION) {
            if (canMoveBox(m, -2, 0, -1, 0) == 1) {
                m->posX--;
            }
        }
    } else if (direction == 's') {
        c = m->map[m->posY+1][m->posX];
        if (c == ' ' || c == DESTINATION) {
            m->posY++;
        } else if (c == BOX || c == BOX_IN_DESTINATION) {
            if (canMoveBox(m, 0, 2, 0, 1) == 1) {
                m->posY++;
            }
        }
    } else if (direction == 'd') {
        c = m->map[m->posY][m->posX+1];
        if (c == ' ' || c == DESTINATION) {
            m->posX++;
        } else if (c == BOX || c == BOX_IN_DESTINATION) {
            if (canMoveBox(m, 2, 0, 1, 0) == 1) {
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

void startGame(struct MapOfGame m) {
    int c = 0;
    while(c != 'k' && m.playerWon != 1) {
        system("clear");
        printMap(&m);
        c = getch();
        movePlayer(&m, c);
    }
    if (m.playerWon == 1) {
        system("clear");
        printf("You won the level with %d steps!\n", m.steps-1);
        return;
    }
}