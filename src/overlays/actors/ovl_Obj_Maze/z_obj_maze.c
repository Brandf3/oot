/*
 * File: z_obj_maze.c
 * Overlay: ovl_Obj_Maze
 * Description: Maze generator
 */

#include "z_obj_maze.h"
#include "assets/objects/object_maze/gMazeWallDL.h"

#define FLAGS (ACTOR_FLAG_4 | ACTOR_FLAG_5)

void ObjMaze_Init(Actor* thisx, PlayState* play);
void ObjMaze_Destroy(Actor* thisx, PlayState* play);
void ObjMaze_Update(Actor* thisx, PlayState* play);
void ObjMaze_Draw(Actor* thisx, PlayState* play);

u8 rand(ObjMaze* this, int offset, int range);
u8 move(ObjMaze* this, int row, int column);
u8 findEmptyCell(ObjMaze* this);

ActorInit Obj_Maze_InitVars = {
    /**/ ACTOR_OBJ_MAZE,
    /**/ ACTORCAT_BG,
    /**/ FLAGS,
    /**/ OBJECT_MAZE,
    /**/ sizeof(ObjMaze),
    /**/ ObjMaze_Init,
    /**/ ObjMaze_Destroy,
    /**/ ObjMaze_Update,
    /**/ ObjMaze_Draw,
};

typedef enum {
    EMPTY,
    UP,
    DOWN,
    RIGHT,
    LEFT,
    MAZE_UP,
    MAZE_DOWN,
    MAZE_RIGHT,
    MAZE_LEFT,
    NO_RIGHT_WALL = 10,
    NO_TOP_WALL = 100
} Direction;

void ObjMaze_Init(Actor* thisx, PlayState* play) {
    ObjMaze* this = (ObjMaze*)thisx;
    this->next = gSaveContext.save.dayTime + play->gameplayFrames;

    // Wilson's Maze Algorithm
    int i;
    int j;
    u8 current;
    u8 direction;
    u8 mazeCount = 0;
    this->frameCount = 0;
    this->originShiftPoint = rand(this, 0, 100);
    this->start = rand(this, 90, 10);
    u8 end = rand(this, 0, 10);
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            this->maze[i][j] = 0;
        }
    }

    this->maze[0][end] = MAZE_UP + NO_TOP_WALL;
    mazeCount++;
    while (mazeCount < 100) {
        current = this->start;
        while (this->maze[current / 10][current % 10] < MAZE_UP) {
            direction = move(this, current / 10, current % 10);
            this->maze[current / 10][current % 10] = direction;

            switch (direction) {
                case UP:
                    current -= 10;
                    break;
                case DOWN:
                    current += 10;
                    break;
                case RIGHT:
                    current += 1;
                    break;
                case LEFT:
                    current -= 1;
                    break;
            }
        }

        current = this->start;
        while (this->maze[current / 10][current % 10] % 10 < MAZE_UP) {
            this->maze[current / 10][current % 10] += 4;
            mazeCount++;
            switch (this->maze[current / 10][current % 10] % 10) {
                case MAZE_UP:
                    this->maze[current / 10][current % 10] += NO_TOP_WALL;
                    current -= 10;
                    break;
                case MAZE_DOWN:
                    current += 10;
                    this->maze[current / 10][current % 10] += NO_TOP_WALL;
                    break;
                case MAZE_RIGHT:
                    this->maze[current / 10][current % 10] += NO_RIGHT_WALL;
                    current += 1;
                    break;
                case MAZE_LEFT:
                    current -= 1;
                    this->maze[current / 10][current % 10] += NO_RIGHT_WALL;
                    break;
            }
        }

        this->start = findEmptyCell(this);
    }
}

void ObjMaze_Destroy(Actor* thisx, PlayState* play) {
    ObjMaze* this = (ObjMaze*)thisx;
}

void ObjMaze_Update(Actor* thisx, PlayState* play) {
    ObjMaze* this = (ObjMaze*)thisx;

    // Origin Shift Algorithm
    u8 direction;
    u8 row;
    u8 column;
    u8 curValue;
    
    this->frameCount += 1;
    if (this->frameCount % 5 == 0)
    {
        this->frameCount = 0;
        row = this->originShiftPoint / 10;
        column = this->originShiftPoint % 10;
        switch (this->maze[row][column] % 10) {
            case MAZE_UP:
                this->maze[row][column] -= NO_TOP_WALL;
                break;
            case MAZE_DOWN:
                this->maze[row + 1][column] -= NO_TOP_WALL;
                break;
            case MAZE_RIGHT:
                this->maze[row][column] -= NO_RIGHT_WALL;
                break;
            case MAZE_LEFT:
                this->maze[row][column - 1] -= NO_RIGHT_WALL;
                break;
        }

        direction = move(this, row, column);
        this->maze[row][column] += direction + 4 - (this->maze[row][column] % 10);
        switch (this->maze[row][column] % 10) {
            case MAZE_UP:
                this->maze[row][column] += NO_TOP_WALL;
                this->originShiftPoint -= 10;
                break;
            case MAZE_DOWN:
                this->maze[row + 1][column] += NO_TOP_WALL;
                this->originShiftPoint += 10;
                break;
            case MAZE_RIGHT:
                this->maze[row][column] += NO_RIGHT_WALL;
                this->originShiftPoint += 1;
                break;
            case MAZE_LEFT:
                this->maze[row][column - 1] += NO_RIGHT_WALL;
                this->originShiftPoint -= 1;
                break;
        }
    }

    // TODO 
    // Create a wall actor & spawn 4 of it on init. 
    // In update check player location to identify maze cell they're located in
    // Move the walls to surround that cell, if there's a path there move the wall under the map
}

void ObjMaze_Draw(Actor* thisx, PlayState* play) {
    ObjMaze* this = (ObjMaze*)thisx;

    int i;
    int j;

    OPEN_DISPS(play->state.gfxCtx, "../z_obj_maze.c", 147);

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            int cell = this->maze[i][j];
            int x = this->actor.world.pos.x + (j * 100) - 450;
            int y = this->actor.world.pos.y;
            int z = this->actor.world.pos.z + (i * 100) - 450;
            Matrix_Translate(x, y + 2.5, z, MTXMODE_NEW);
            Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);
            
            if (!(cell >= 100 && cell % 100 >= 10)) { // Skip drawing walls if both walls are removed
                if (cell > 100) { // only right wall
                    Matrix_RotateY(DEG_TO_RAD(270), MTXMODE_APPLY);
                } else if (cell > 10) { // only top wall
                    // Don't need to rotate
                } else { // both walls
                    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx, "../z_obj_maze.c", 158), G_MTX_MODELVIEW | G_MTX_LOAD);
                    gSPDisplayList(POLY_OPA_DISP++, gMazeWallDL);
                    Matrix_Translate(x, y + 2.5, z, MTXMODE_NEW);
                    Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);
                    Matrix_RotateY(DEG_TO_RAD(270), MTXMODE_APPLY);
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
                }
                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx, "../z_obj_maze.c", 158), G_MTX_MODELVIEW | G_MTX_LOAD);
                gSPDisplayList(POLY_OPA_DISP++, gMazeWallDL);
            }
        }
    }

    for (i = 0; i < 10; i++) {
        if (i != this->start % 10) {
            int x = this->actor.world.pos.x + (i * 100) - 450;
            int y = this->actor.world.pos.y;
            int z = this->actor.world.pos.z + 550;
            Matrix_Translate(x, y + 2.5, z, MTXMODE_NEW);
            Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx, "../z_obj_maze.c", 158), G_MTX_MODELVIEW | G_MTX_LOAD);
            gSPDisplayList(POLY_OPA_DISP++, gMazeWallDL);
        }
    }

    for (i = 0; i < 10; i++) {
        int x = this->actor.world.pos.x - 550;
        int y = this->actor.world.pos.y;
        int z = this->actor.world.pos.z + (i * 100) - 450;
        Matrix_Translate(x, y + 2.5, z, MTXMODE_NEW);
        Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);
        Matrix_RotateY(DEG_TO_RAD(270), MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx, "../z_obj_maze.c", 158), G_MTX_MODELVIEW | G_MTX_LOAD);
        gSPDisplayList(POLY_OPA_DISP++, gMazeWallDL);
    }

    CLOSE_DISPS(play->state.gfxCtx, "../z_obj_maze.c", 169);
}

u8 rand(ObjMaze* this, int offset, int range) {
    this->next = this->next * 1103515245 + 12345;
    return (unsigned int)(this->next/65536) % range + offset;
}

u8 move(ObjMaze* this, int row, int column) {
    u8 choice = rand(this, 0, 4);
    while (true) {
        if (choice == 0 && row > 0) {
            return UP;
        } else if (choice == 1 && row < 9) {
            return DOWN;
        } else if (choice == 2 && column < 9) {
            return RIGHT;
        } else if (choice == 3 && column > 0) {
            return LEFT;
        }
        choice += rand(this, 1, 3);
    }
}

u8 findEmptyCell(ObjMaze* this) {
    u8 i;
    u8 j;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if (this->maze[i][j] < MAZE_UP) {
                return (i * 10) + j;
            }
        }
    }

    return 0;
}
