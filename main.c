#include "globals.h"
#include "game.h"
#include "filesupport.h"

int main()
{
    struct MapOfGame p = getMap("level1.txt");
    if (p.isError != 1) {
        printf("Map is good\n");
    }
//    printf("\u23fa \u25cb \u25C9 \u25A0 \u25A2 \u25A3\n");
    startGame(p);
    return 0;
}