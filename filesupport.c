#include "globals.h"
#include "filesupport.h"

struct MapOfGame getMap(char * name) {
    struct MapOfGame m;
    FILE * f;
    m.isError = 0;
    char fileName[50] = "../maps/";
    int c;
    strcat(fileName, name);
    //TODO CHANGE TO CORRECT PATH
//    printf("%s", fileName);
    f = fopen(fileName, "r");

    if (f == NULL) {
        printf("Error: Cannot open file, restart game\n");
        m.isError = 1;
        return m;
    }

    for (int i = 0; i < MAP_SIZE_Y; i++) {
        for (int j = 0; j < MAP_SIZE_X; j++) {
            c = getc(f);
            if (c == 'P' || c == 'C') {
                m.posX = j;
                m.posY = i;
                c = ' ';
            }
            m.map[i][j] = c;
        }
        getc(f); // ignore last char (new line)
    }
    fclose(f);

    m.steps = 0;
    return m;
}
