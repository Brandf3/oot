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

ActorProfile Obj_Maze_Profile = {
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
    this->frameCount2 = 0;
    u8 start = rand(this, (ROWS - 1) * COLUMNS + (COLUMNS / 2), COLUMNS / 2);
    u8 end = rand(this, 0, COLUMNS / 2);
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            this->maze[i][j].type = 0;
            this->maze[i][j].topWallIdx = -1;
            this->maze[i][j].rightWallIdx = -1;
        }
    }

    this->originShiftPoint = end;
    this->maze[0][end].type = ORIGIN + NO_TOP_WALL;
    mazeCount++;
    while (mazeCount < ROWS * COLUMNS) {
        current = start;
        while (this->maze[current / COLUMNS][current % COLUMNS].type < MAZE_UP) {
            direction = move(this, current / COLUMNS, current % COLUMNS);
            this->maze[current / COLUMNS][current % COLUMNS].type = direction;

            switch (direction) {
                case UP:
                    current -= COLUMNS;
                    break;
                case DOWN:
                    current += COLUMNS;
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
        while (this->maze[current / COLUMNS][current % COLUMNS].type % 10 < MAZE_UP) {
            this->maze[current / COLUMNS][current % COLUMNS].type += 4;
            mazeCount++;
            switch (this->maze[current / COLUMNS][current % COLUMNS].type % 10) {
                case MAZE_UP:
                    this->maze[current / COLUMNS][current % COLUMNS].type += NO_TOP_WALL;
                    current -= COLUMNS;
                    break;
                case MAZE_DOWN:
                    current += COLUMNS;
                    this->maze[current / COLUMNS][current % COLUMNS].type += NO_TOP_WALL;
                    break;
                case MAZE_RIGHT:
                    this->maze[current / COLUMNS][current % COLUMNS].type += NO_RIGHT_WALL;
                    current += 1;
                    break;
                case MAZE_LEFT:
                    current -= 1;
                    this->maze[current / COLUMNS][current % COLUMNS].type += NO_RIGHT_WALL;
                    break;
            }
        }

        start = findEmptyCell(this);
    }

    u8 wallCount = 0;
    bool rightWall;
    bool topWall;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            int cell = this->maze[i][j].type;
            int x = this->actor.world.pos.x + (j * CELL_SIZE) - (COLUMNS * 100 / 2 - (CELL_SIZE / 2));  //450
            int y = this->actor.world.pos.y + 2.5;
            int z = this->actor.world.pos.z + (i * CELL_SIZE) - (ROWS * 100 / 2 - (CELL_SIZE / 2)); //450

            rightWall = cell % 100 < 10;
            topWall = cell < 100;
            if (rightWall) 
            {
                Actor* wall = Actor_Spawn(&play->actorCtx, play, ACTOR_OBJ_MAZE_WALL, x + 50, y, z, 0, DEG_TO_BINANG(90), 0, 0);
                if (j < COLUMNS - 1) {
                    this->wallActors[wallCount] = wall;
                    this->maze[i][j].rightWallIdx = wallCount;
                    wallCount += 1;
                }
            }
            if (topWall)
            {
                Actor* wall = Actor_Spawn(&play->actorCtx, play, ACTOR_OBJ_MAZE_WALL, x, y, z - 50, 0, 0, 0, 0);
                if (i > 0)
                {
                    this->wallActors[wallCount] = wall;
                    this->maze[i][j].topWallIdx = wallCount;
                    wallCount += 1;
                }
            }
        }
    }

    for (i = 0; i < COLUMNS; i++) {
        if (i != start % COLUMNS) {
            int x = this->actor.world.pos.x + (i * CELL_SIZE) - (COLUMNS * CELL_SIZE / 2 - (CELL_SIZE / 2)); //450
            int y = this->actor.world.pos.y + 2.5;
            int z = this->actor.world.pos.z + (ROWS * CELL_SIZE / 2); //500
            Actor_Spawn(&play->actorCtx, play, ACTOR_OBJ_MAZE_WALL, x, y, z, 0, 0, 0, 0);
        }
    }

    for (i = 0; i < ROWS; i++) {
        int x = this->actor.world.pos.x - (COLUMNS * CELL_SIZE / 2); //500
        int y = this->actor.world.pos.y + 2.5;
        int z = this->actor.world.pos.z + (i * CELL_SIZE) - (ROWS * CELL_SIZE / 2 - (CELL_SIZE / 2)); //450
        Actor_Spawn(&play->actorCtx, play, ACTOR_OBJ_MAZE_WALL, x, y, z, 0, DEG_TO_BINANG(90), 0, 0);
    }

    this->portalOneIdx = rand(this, 0, ((ROWS - 1) * (COLUMNS - 1)));
    this->portalTwoIdx = rand(this, 0, ((ROWS - 1) * (COLUMNS - 1)));
    this->wallActors[this->portalOneIdx]->params = 1;
    this->wallActors[this->portalTwoIdx]->params = 1;
}

void ObjMaze_Destroy(Actor* thisx, PlayState* play) {
    ObjMaze* this = (ObjMaze*)thisx;
}

void ObjMaze_Update(Actor* thisx, PlayState* play) {
    ObjMaze* this = (ObjMaze*)thisx;

    //Origin Shift Algorithm
    u8 direction;
    u8 row;
    u8 column;

    this->frameCount++;
    this->frameCount2++;
    if (this->teleportCooldown > 0)
    {
        this->teleportCooldown--;
    }

    if (this->frameCount % ORIGIN_SHIFT_DELAY == 0)
    {
        this->frameCount = 0;
        row = this->originShiftPoint / COLUMNS;
        column = this->originShiftPoint % COLUMNS;
        direction = move(this, row, column);
        this->maze[row][column].type += direction + LEFT - (this->maze[row][column].type % 10);
        switch (this->maze[row][column].type % 10) {
            case MAZE_UP:
                ObjMaze_SetCellToOrigin(this, row - 1, column, this->maze[row][column].topWallIdx);
                this->maze[row][column].type += NO_TOP_WALL;
                this->maze[row][column].topWallIdx = -1;
                this->originShiftPoint -= COLUMNS;
                break;
            case MAZE_DOWN:
                ObjMaze_SetCellToOrigin(this, row + 1, column, this->maze[row + 1][column].topWallIdx);
                this->maze[row + 1][column].type += NO_TOP_WALL;
                this->maze[row + 1][column].topWallIdx = -1;
                this->originShiftPoint += COLUMNS;
                break;
            case MAZE_RIGHT:
                ObjMaze_SetCellToOrigin(this, row, column + 1, this->maze[row][column].rightWallIdx);
                this->maze[row][column].type += NO_RIGHT_WALL;
                this->maze[row][column].rightWallIdx = -1;
                this->originShiftPoint += 1;
                break;
            case MAZE_LEFT:
                ObjMaze_SetCellToOrigin(this, row, column - 1, this->maze[row][column - 1].rightWallIdx);
                this->maze[row][column - 1].type += NO_RIGHT_WALL;
                this->maze[row][column - 1].rightWallIdx = -1;
                this->originShiftPoint -= 1;
                break;
        }
    }

    if (this->frameCount2 % TELEPORTER_SHIFT_DELAY == 0) 
    {
        this->frameCount2 = 0;
        this->wallActors[this->portalOneIdx]->params = 0;
        this->wallActors[this->portalTwoIdx]->params = 0;
        this->portalOneIdx = rand(this, 0, ((ROWS - 1) * (COLUMNS - 1)));
        this->portalTwoIdx = rand(this, 0, ((ROWS - 1) * (COLUMNS - 1)));
        this->wallActors[this->portalOneIdx]->params = 1;
        this->wallActors[this->portalTwoIdx]->params = 1;
    }

    if (this->teleportCooldown == 0) 
    {
        if (this->wallActors[this->portalOneIdx]->xzDistToPlayer < 30.0f)
        {
            Player* player = GET_PLAYER(play);
            Math_Vec3f_Copy(&player->actor.world.pos, &this->wallActors[this->portalTwoIdx]->world.pos);
            Camera* camera = Play_GetCamera(play, play->activeCamId);
            //Math_Vec3f_Copy(&camera->at, &this->wallActors[this->portalOneIdx]->world.pos);
            this->teleportCooldown = 100;
        }
        else if (this->wallActors[this->portalTwoIdx]->xzDistToPlayer < 30.0f)
        {
            Player* player = GET_PLAYER(play);
            Math_Vec3f_Copy(&player->actor.world.pos, &this->wallActors[this->portalOneIdx]->world.pos);
            Camera* camera = Play_GetCamera(play, play->activeCamId);
            //Math_Vec3f_Copy(&camera->at, &this->wallActors[this->portalOneIdx]->world.pos);
            this->teleportCooldown = 100;
        }
    }
}

void ObjMaze_Draw(Actor* thisx, PlayState* play) {
    ObjMaze* this = (ObjMaze*)thisx;
}

// Add wall back in and remove direction from cell
void ObjMaze_SetCellToOrigin(ObjMaze* this, u8 row, u8 column, s8 removedWallIdx) {

    int x = this->actor.world.pos.x + (column * CELL_SIZE) - (COLUMNS * CELL_SIZE / 2 - (CELL_SIZE / 2)); // 450
    int y = this->actor.world.pos.y + 2.5;
    int z = this->actor.world.pos.z + (row * CELL_SIZE) - (ROWS * CELL_SIZE / 2 - (CELL_SIZE / 2)); // 450
    u8 rot = 0;
    switch (this->maze[row][column].type % 10) {
        case MAZE_UP:
            this->maze[row][column].type -= NO_TOP_WALL;
            this->maze[row][column].type += ORIGIN - MAZE_UP;
            this->maze[row][column].topWallIdx = removedWallIdx;
            z -= (CELL_SIZE / 2);
            break;
        case MAZE_DOWN:
            this->maze[row + 1][column].type -= NO_TOP_WALL;
            this->maze[row][column].type += ORIGIN - MAZE_DOWN;
            this->maze[row + 1][column].topWallIdx = removedWallIdx;
            z += (CELL_SIZE / 2);
            break;
        case MAZE_RIGHT:
            this->maze[row][column].type -= NO_RIGHT_WALL;
            this->maze[row][column].type += ORIGIN - MAZE_RIGHT;
            this->maze[row][column].rightWallIdx = removedWallIdx;
            rot = 90;
            x += (CELL_SIZE / 2);
            break;
        case MAZE_LEFT:
            this->maze[row][column - 1].type -= NO_RIGHT_WALL;
            this->maze[row][column].type += ORIGIN - MAZE_LEFT;
            this->maze[row][column - 1].rightWallIdx = removedWallIdx;
            rot = 90;
            x -= (CELL_SIZE / 2);
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
        } else if (choice == 1 && row < ROWS - 1) {
            return DOWN;
        } else if (choice == 2 && column < COLUMNS - 1) {
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
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            if (this->maze[i][j].type < MAZE_UP) {
                return (i * COLUMNS) + j;
            }
        }
    }

    return 0;
}
