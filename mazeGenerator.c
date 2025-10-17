#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


int checkMovement(int maze[][201], int x, int y, int size, int specifier, int lookingFor) {
    int moves = 0;
    // printf("%d\n", size);

    // specifier = 0
    if (specifier == 0) {
        if (maze[x+1][y] == lookingFor && x < size-1) moves++; 
        if (maze[x-1][y] == lookingFor && x > 0)      moves++; 
        if (maze[x][y+1] == lookingFor && y < size-1) moves++; 
        if (maze[x][y-1] == lookingFor && y > 0)      moves++; 
    }
    else {
        if (maze[x+1][y] == lookingFor && specifier == 2 && x < size-1) moves++; 
        if (maze[x-1][y] == lookingFor && specifier == 4 && x > 0)      moves++; 
        if (maze[x][y+1] == lookingFor && specifier == 1 && y < size-1) moves++; 
        if (maze[x][y-1] == lookingFor && specifier == 3 && y > 0)      moves++; 
    }
    
    //1 up
    //2 right
    //3 down
    //4 left
    
    return moves;
}

int generateMaze(char maze[][201], int size) {
    int mapSize = 2 * size + 1;
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            maze[i][j] = '#';
            // if (i == 0 || i == mapSize-1 || j == 0 || j == mapSize-1 || (i % 2 == 0 && j % 2 == 0)) {
            //     maze[i][j] = '#';
            // } else {
            //     maze[i][j] = '.';
            // }
        }
    }

    //  0 = empty
    //  1 = checked
    // -1 = back tracked
    int mazeModel[201][201];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mazeModel[i][j] = 0;
        }
    }

    // choose starting point ======================================================
    int moleX = rand() % size;
    int moleY = rand() % size;
    mazeModel[moleX][moleY] = 1;
    maze[moleX * 2 + 1][moleY * 2 + 1] = ' ';

    // creating -===================================================================
    int complete = 0;
    int backTracking = 0;
    int step = 2;
    while (!complete) {
        if (!backTracking) {
            int totalMovements = checkMovement(mazeModel, moleX, moleY, size, 0, 0);
            if (totalMovements > 0) {
                // decide where to go and just go i guess =====================================
                int turns = rand() % totalMovements + 1;
                int count = 0;
                for (int i = 1; i <= 4; i++) {
                    if (checkMovement(mazeModel, moleX, moleY, size, i, 0) > 0) count++;
                    if (count == turns) {
                        if (i == 1) {
                            moleY++; 
                            maze[moleX * 2 + 1][moleY * 2] = ' ';
                        }
                        if (i == 2) {
                            moleX++; 
                            maze[moleX * 2][moleY * 2 + 1] = ' ';
                        }
                        if (i == 3) {
                            moleY--; 
                            maze[moleX * 2 + 1][moleY * 2 + 2] = ' ';
                        }
                        if (i == 4) {
                            moleX--; 
                            maze[moleX * 2 + 2][moleY * 2 + 1] = ' ';
                        }
                        maze[moleX * 2 + 1][moleY * 2 + 1] = ' ';
                        mazeModel[moleX][moleY] = step;
                        step++;
                        break;
                    }
                }
            } 
            else {
                backTracking = 1;
                // step we will be looking for
                step -= 2;
                // complete = 1;
                // maze[moleX * 2 + 1][moleY * 2 + 1] = 'b';
            }
        } 

        else {
            //backtracking========================================================================
            
            int totalMovements = checkMovement(mazeModel, moleX, moleY, size, 0, 0);
            if (totalMovements > 0) {
                step += 2;
                backTracking = 0;
            } 
            else {
                mazeModel[moleX][moleY] = -1;
                if      (checkMovement(mazeModel, moleX, moleY, size, 1, step) > 0) {
                    moleY++;
                }
                else if (checkMovement(mazeModel, moleX, moleY, size, 2, step) > 0) {
                    moleX++;    
                }
                else if (checkMovement(mazeModel, moleX, moleY, size, 3, step) > 0) {
                    moleY--;
                }
                else if (checkMovement(mazeModel, moleX, moleY, size, 4, step) > 0) {
                    moleX--;
                }
                step--;
            }
        }
 
        int numOfBacktracked = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (mazeModel[i][j] == -1) numOfBacktracked++;
            }
        }
        if (numOfBacktracked == size*size) complete = 1;
    }
    // int debugX = 0;
    // int debugY = 0;
    // printf("%d\n", checkMovement(mazeModel, debugX, debugY, size, 0));
    // mazeModel[debugX][debugY] = 1;
    // maze[debugX * 2 + 1][debugY * 2 + 1] = ' ';

    return 0;
}

int main() {
    // system("chcp 65001");
    system("chcp 65001 > nul");
    srand(time(NULL));
    char maze[201][201];
    int mazeSize = 15;

    while (mazeSize > 0) {
        generateMaze(maze, mazeSize);

        // print maze
        for (int i = 0; i < mazeSize*2 + 1; i++) {
            for (int j = 0; j < mazeSize*2 + 1; j++) {
                if (maze[i][j] == '#') printf("\u2588\u2588");
                if (maze[i][j] == ' ') printf("  ");
                // else printf("%c", maze[i][j]);
            }
            printf("\n");
        }
        scanf("%d", &mazeSize);
    }
}