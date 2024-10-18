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

void ObjMaze_SetCellToOrigin(ObjMaze* this, u8 row, u8 column, s8 removedWallIdx);
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
    ORIGIN,
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
    this->start = rand(this, 90, 10);
    u8 end = rand(this, 0, 10);
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            this->maze[i][j].type = 0;
            this->maze[i][j].topWallIdx = -1;
            this->maze[i][j].rightWallIdx = -1;
        }
    }

    this->originShiftPoint = end;
    this->maze[0][end].type = ORIGIN + NO_TOP_WALL;
    mazeCount++;
    while (mazeCount < 100) {
        current = this->start;
        while (this->maze[current / 10][current % 10].type < MAZE_UP) {
            direction = move(this, current / 10, current % 10);
            this->maze[current / 10][current % 10].type = direction;

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
        while (this->maze[current / 10][current % 10].type % 10 < MAZE_UP) {
            this->maze[current / 10][current % 10].type += 4;
            mazeCount++;
            switch (this->maze[current / 10][current % 10].type % 10) {
                case MAZE_UP:
                    this->maze[current / 10][current % 10].type += NO_TOP_WALL;
                    current -= 10;
                    break;
                case MAZE_DOWN:
                    current += 10;
                    this->maze[current / 10][current % 10].type += NO_TOP_WALL;
                    break;
                case MAZE_RIGHT:
                    this->maze[current / 10][current % 10].type += NO_RIGHT_WALL;
                    current += 1;
                    break;
                case MAZE_LEFT:
                    current -= 1;
                    this->maze[current / 10][current % 10].type += NO_RIGHT_WALL;
                    break;
            }
        }

        this->start = findEmptyCell(this);
    }

    u8 wallCount = 0;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            int cell = this->maze[i][j].type;
            int x = this->actor.world.pos.x + (j * 100) - 450;
            int y = this->actor.world.pos.y + 2.5;
            int z = this->actor.world.pos.z + (i * 100) - 450;
            
            if (!(cell >= 100 && cell % 100 >= 10)) { // Skip spawning walls if both walls are removed
                if (cell > 100) { // only right wall
                   this->wallActors[wallCount] = Actor_Spawn(&play->actorCtx, play, ACTOR_OBJ_MAZE_WALL, x + 50, y, z, 0, DEG_TO_BINANG(90), 0, 1);
                   this->maze[i][j].rightWallIdx = wallCount;
                   this->maze[i][j].topWallIdx = -1;
                   wallCount += 1;
                } else if (cell > 10) { // only top wall
                    this->wallActors[wallCount] = Actor_Spawn(&play->actorCtx, play, ACTOR_OBJ_MAZE_WALL, x, y, z - 50, 0, 0, 0, 1);
                    this->maze[i][j].topWallIdx = wallCount;
                    this->maze[i][j].rightWallIdx = -1;
                    wallCount += 1;
                } else { // both walls
                    this->wallActors[wallCount] = Actor_Spawn(&play->actorCtx, play, ACTOR_OBJ_MAZE_WALL, x + 50, y, z, 0, DEG_TO_BINANG(90), 0, 1);
                    this->maze[i][j].rightWallIdx = wallCount;
                    wallCount += 1;
                    this->wallActors[wallCount] = Actor_Spawn(&play->actorCtx, play, ACTOR_OBJ_MAZE_WALL, x, y, z - 50, 0, 0, 0, 1);
                    this->maze[i][j].topWallIdx = wallCount;
                    wallCount += 1;
                }
            }
        }
    }

    for (i = 0; i < 10; i++) {
        if (i != this->start % 10) {
            int x = this->actor.world.pos.x + (i * 100) - 450;
            int y = this->actor.world.pos.y + 2.5;
            int z = this->actor.world.pos.z + 500;
            Actor_Spawn(&play->actorCtx, play, ACTOR_OBJ_MAZE_WALL, x, y, z, 0, 0, 0, 1);
        }
    }

    for (i = 0; i < 10; i++) {
        int x = this->actor.world.pos.x - 500;
        int y = this->actor.world.pos.y + 2.5;
        int z = this->actor.world.pos.z + (i * 100) - 450;
        Actor_Spawn(&play->actorCtx, play, ACTOR_OBJ_MAZE_WALL, x, y, z, 0, DEG_TO_BINANG(90), 0, 1);
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

    this->frameCount += 1;
    if (this->frameCount % 10 == 0)
    {
        this->frameCount = 0;
        row = this->originShiftPoint / 10;
        column = this->originShiftPoint % 10;
        direction = move(this, row, column);
        this->maze[row][column].type += direction + LEFT - (this->maze[row][column].type % 10);
        osSyncPrintf("Direction: %d\n", direction);
        switch (this->maze[row][column].type % 10) {
            case MAZE_UP:
                osSyncPrintf("Maze up");
                ObjMaze_SetCellToOrigin(this, row - 1, column, this->maze[row][column].topWallIdx);
                this->maze[row][column].type += NO_TOP_WALL;
                this->maze[row][column].topWallIdx = -1;
                this->originShiftPoint -= 10;
                break;
            case MAZE_DOWN:
                osSyncPrintf("Maze down");
                ObjMaze_SetCellToOrigin(this, row + 1, column, this->maze[row + 1][column].topWallIdx);
                this->maze[row + 1][column].type += NO_TOP_WALL;
                this->maze[row + 1][column].topWallIdx = -1;
                this->originShiftPoint += 10;
                break;
            case MAZE_RIGHT:
                osSyncPrintf("Maze right");
                ObjMaze_SetCellToOrigin(this, row, column + 1, this->maze[row][column].rightWallIdx);
                this->maze[row][column].type += NO_RIGHT_WALL;
                this->maze[row][column].rightWallIdx = -1;
                this->originShiftPoint += 1;
                break;
            case MAZE_LEFT:
                osSyncPrintf("Maze left");
                ObjMaze_SetCellToOrigin(this, row, column - 1, this->maze[row][column - 1].rightWallIdx);
                this->maze[row][column - 1].type += NO_RIGHT_WALL;
                this->maze[row][column - 1].rightWallIdx = -1;
                this->originShiftPoint -= 1;
                break;
        }
    }
}

void ObjMaze_Draw(Actor* thisx, PlayState* play) {
    ObjMaze* this = (ObjMaze*)thisx;
}

// Add wall back in and remove direction from cell
void ObjMaze_SetCellToOrigin(ObjMaze* this, u8 row, u8 column, s8 removedWallIdx) {

    int x = this->actor.world.pos.x + (column * 100) - 450;
    int y = this->actor.world.pos.y + 2.5;
    int z = this->actor.world.pos.z + (row * 100) - 450;
    u8 rot = 0;
    switch (this->maze[row][column].type % 10) {
        case MAZE_UP:
            this->maze[row][column].type -= NO_TOP_WALL;
            this->maze[row][column].type += ORIGIN - MAZE_UP;
            this->maze[row][column].topWallIdx = removedWallIdx;
            z -= 50;
            break;
        case MAZE_DOWN:
            this->maze[row + 1][column].type -= NO_TOP_WALL;
            this->maze[row][column].type += ORIGIN - MAZE_DOWN;
            this->maze[row + 1][column].topWallIdx = removedWallIdx;
            z += 50;
            break;
        case MAZE_RIGHT:
            this->maze[row][column].type -= NO_RIGHT_WALL;
            this->maze[row][column].type += ORIGIN - MAZE_RIGHT;
            this->maze[row][column].rightWallIdx = removedWallIdx;
            rot = 90;
            x += 50;
            break;
        case MAZE_LEFT:
            this->maze[row][column - 1].type -= NO_RIGHT_WALL;
            this->maze[row][column].type += ORIGIN - MAZE_LEFT;
            this->maze[row][column - 1].rightWallIdx = removedWallIdx;
            rot = 90;
            x -= 50;
            break;
    }
    
    if (removedWallIdx > -1)
    {
        this->wallActors[removedWallIdx]->world.pos.x = x;
        this->wallActors[removedWallIdx]->world.pos.y = y;
        this->wallActors[removedWallIdx]->world.pos.z = z;
        this->wallActors[removedWallIdx]->world.rot.y = DEG_TO_BINANG(rot);
        this->wallActors[removedWallIdx]->shape.rot.y = this->wallActors[removedWallIdx]->world.rot.y;
    }
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
            if (this->maze[i][j].type < MAZE_UP) {
                return (i * 10) + j;
            }
        }
    }

    return 0;
}
