#include "globals.h"
#include "playersupport.h"
#include <dirent.h>

struct MapOfGame getMap(char * name) {
    struct MapOfGame m;
    FILE * f;
    char fileName[50] = DIR_WITH_MAPS;
    int c;
    strcat(fileName, name);
    f = fopen(fileName, "r");

    if (f == NULL) {
        printf("Error: Cannot load map.\n");
        exit(1);
    }

    for (int i = 0; i < MAP_SIZE_Y; i++) {
        for (int j = 0; j < MAP_SIZE_X; j++) {
            c = getc(f);
            if (c == PLAYER || c == PLAYER_IN_DESTINATION) {
                m.posX = j;
                m.posY = i;
            }
            m.map[i][j] = c;
        }
        getc(f); // ignore last char (new line)
    }
    fclose(f);

    // delete field with player
    if (m.map[m.posY][m.posX] == PLAYER) {
        m.map[m.posY][m.posX] = EMPTY_FIELD;
    } else {
        m.map[m.posY][m.posX] = DESTINATION;
    }

    m.steps = 0;
    return m;
}
void showGreetings() {
    printf("------------------\n");
    printf("Player controls\n");
    printf("UP\t=>\t%c\n", P_UP);
    printf("DOWN\t=>\t%c\n", P_DOWN);
    printf("LEFT\t=>\t%c\n", P_LEFT);
    printf("RIGHT\t=>\t%c\n", P_RIGHT);
    printf("EXIT\t=>\t%c\n", P_EXIT);
    printf("------------------\n");
    printf("Your aim:\n");
    printf("Push boxes %-4s around in a board, trying to get them to storage locations %-4s with player %-4s\n", CHAR_BOX, CHAR_DESTINATION, CHAR_PLAYER);
    printf("------------------\n");

}
void showScore() {
    struct Score {
        char    mapName[50];
        int     score;
    };
    struct Score scores[100];
    char levelName[50];
    int score = 0;
    int amountOfMaps = 0;

    system(CLEAR_COMMAND);
    FILE *f = fopen(FILE_WITH_SCORE, "r");
    if (f == NULL) {
        printf("Cannnot open file with scores");
        exit(1);
    }
    printf("SCOREBOARD:\n");
    while (fscanf(f, "%s %d", levelName, &score) != EOF) {
        int i = amountOfMaps-1;
        while (strcmp(levelName, scores[i].mapName) < 0 && i >= 0) {
            scores[i+1] = scores[i];
            i--;
        }
        strcpy(scores[i+1].mapName, levelName);
        scores[i+1].score = score;
        amountOfMaps++;
    }

    for (int i = 0; i < amountOfMaps; i++) {
        printf("%-60s %d\n", scores[i].mapName, scores[i].score);
    }
}
int getChoice(char maps[100][50], int amountOfMaps) {
    int choice = 0;
    while (1) {
        system(CLEAR_COMMAND);
        showGreetings();
        printf("Choose:\n");
        for (int i = 0; i < amountOfMaps; i++) {
            printf("[%-3d]\t%s\n", i+1, maps[i]);
        }
        printf("[%-3d]\t%s\n", amountOfMaps+1, "Show score");
        printf("[%-3d]\t%s\n", amountOfMaps+2, "Exit");
        printf("Your choice: ");
        scanf("%d", &choice);
        if (choice > 0 && choice <= amountOfMaps) {
            return choice;
        } else if (choice == amountOfMaps+1) {
            showScore();
            exit(0);
        } else if (choice == amountOfMaps+2) {
            exit(0);
        }
    }
}
struct MapOfGame getChosenMap() {
    struct MapOfGame p;
    char mapsName[100][50];
    int amountOfMaps = 0;
    int mapID = 0;
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir (DIR_WITH_MAPS)) != NULL) {
        /* get all the name maps within map directory */
        while ((ent = readdir (dir)) != NULL) {
            if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {

                int i = amountOfMaps-1;
                while (strcmp(ent->d_name, mapsName[i]) < 0 && i >= 0) {
                    strcpy(mapsName[i+1], mapsName[i]);
                    i--;
                }
                strcpy(mapsName[i+1], ent->d_name);
                amountOfMaps++;
            }
        }
        closedir (dir);
    } else {
        printf("Cannot open directory with maps.\n");
        exit(1);
    }
    mapID = getChoice(mapsName, amountOfMaps);

    p = getMap(mapsName[mapID-1]);
    strcpy(p.mapName, mapsName[mapID-1]);
    return p;
}
void saveScore(struct MapOfGame m) {
    if (m.playerWon == 0) {
        printf("You exit the game.\n");
        return ;
    }
    printf("You won the level '%s' with %d steps!\n", m.mapName, m.steps);

    char mapName[50];
    int lastScore = 0;
    FILE *f = fopen(FILE_WITH_SCORE, "r+");
    if (f == NULL) {
        //File not exists
        f = fopen(FILE_WITH_SCORE, "w+");
        if (f == NULL) {
            printf("Cannot create file %s", FILE_WITH_SCORE);
            exit(1);
        }
    }

    while (fscanf(f, "%s %d", mapName, &lastScore) != EOF) {
        // update score
        if (strcmp(mapName, m.mapName) == 0) {
            if (m.steps < lastScore || lastScore == 0) {
                printf(" Your last score was %d steps.\n", lastScore);
                fseek(f, -10, SEEK_CUR);
                fprintf(f, "%10d", m.steps);
                fclose(f);
            }
            return;
        }
    }
    fprintf(f, "%s %10d\n", m.mapName, m.steps);
    fclose(f);
}