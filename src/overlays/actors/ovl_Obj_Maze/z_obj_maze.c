/*
 * File: z_obj_maze.c
 * Overlay: ovl_Obj_Maze
 * Description: Maze generator
 */

#include "z_obj_maze.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_0 | ACTOR_FLAG_2 | ACTOR_FLAG_4)

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
    /**/ OBJECT_GAMEPLAY_KEEP,
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
// ones digit is direction & if it's part of maze, tens digit is right wall, hundreds digit is top wall?
// to not have to modify existing code much, 8 would be left direction with both walls, 118 would be with no walls
void ObjMaze_Init(Actor* thisx, PlayState* play) {
    ObjMaze* this = (ObjMaze*)thisx;
    this->next = gSaveContext.save.dayTime + play->gameplayFrames;

    int i;
    int j;
    u8 current;
    u8 direction;
    u8 mazeCount = 0;
    u8 start = rand(this, 90, 10);
    u8 end = rand(this, 0, 10);
    
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            this->maze[i][j] = 0;
        }
    }

    this->maze[0][end] = MAZE_UP + NO_TOP_WALL;
    mazeCount++;
    while (mazeCount < 100) {
        current = start;
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
        
        current = start;
        while (this->maze[current / 10][current % 10] % 10 < MAZE_UP) {
            this->maze[current / 10][current % 10] += 4;
            mazeCount++;
            switch (this->maze[current / 10][current % 10]) {
                case MAZE_UP:
                    if (this->maze[current / 10][current % 10] < 100) {
                        this->maze[current / 10][current % 10] += NO_TOP_WALL;
                    }
                    current -= 10;
                    break;
                case MAZE_DOWN:
                    current += 10;
                    if (this->maze[current / 10][current % 10] < 100) {
                        this->maze[current / 10][current % 10] += NO_TOP_WALL;
                    }
                    break;
                case MAZE_RIGHT:
                    if (this->maze[current / 10][current % 10] % 100 < 10) {
                        this->maze[current / 10][current % 10] += NO_RIGHT_WALL;
                    }
                    current += 1;
                    break;
                case MAZE_LEFT:
                    current -= 1;
                    if (this->maze[current / 10][current % 10] % 100 < 10) {
                        this->maze[current / 10][current % 10] += NO_RIGHT_WALL;
                    }
                    break;
            }
        }

        start = findEmptyCell(this);
    }

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            osSyncPrintf("%d\t", this->maze[i][j]);
        }
        osSyncPrintf("\n");
    }
}

void ObjMaze_Destroy(Actor* thisx, PlayState* play) {
    ObjMaze* this = (ObjMaze*)thisx;
}

void ObjMaze_Update(Actor* thisx, PlayState* play) {
    ObjMaze* this = (ObjMaze*)thisx;
}

void ObjMaze_Draw(Actor* thisx, PlayState* play) {
    ObjMaze* this = (ObjMaze*)thisx;

    int i;
    int j;

    OPEN_DISPS(play->state.gfxCtx, "../z_obj_maze.c", 147);

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            int cell = this->maze[i][j];
            int x = this->actor.world.pos.x + (j * 50) - 225;
            int y = this->actor.world.pos.y;
            int z = this->actor.world.pos.z + (i * 50) - 225;
            Matrix_Translate(x, y + 2.5, z, MTXMODE_NEW);
            Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx, "../z_obj_chess.c", 175), G_MTX_MODELVIEW | G_MTX_LOAD);
            
            if (cell < 110) {
                if (cell > 100) {
                    gSPDisplayList(POLY_OPA_DISP++, gBombchuDL);
                } else if (cell > 10) {
                    gSPDisplayList(POLY_OPA_DISP++, gDebugPyramidDL);
                } else {
                    gSPDisplayList(POLY_OPA_DISP++, gLiftableRockDL);
                }
                
            }
        }
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
