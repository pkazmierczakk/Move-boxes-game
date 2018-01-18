#include "globals.h"
#include "game.h"
#include "playersupport.h"

int main()
{
    struct MapOfGame p = getChosenMap();
    startGame(&p);
    system(CLEAR_COMMAND);
    saveScore(p);
    return 0;
}