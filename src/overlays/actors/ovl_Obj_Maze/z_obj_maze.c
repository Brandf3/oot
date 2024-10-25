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

void ObjMaze_SetCellToOrigin(ObjMaze* this, u8 row, u8 column);
u8 move(ObjMaze* this, int row, int column);
u8 findEmptyCell(ObjMaze* this);
void printMaze(ObjMaze* this);

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
    u8 index;
    u8 current;
    u8 direction;
    u8 mazeCount = 0;
    this->frameCount = 0;
    this->frameCount2 = 0;

    u8 end = Rand_S16Offset(0, COLUMNS / 3);
    u8 start = Rand_S16Offset(end + 1, ROWS * COLUMNS - (end + 1));
    this->originShiftPoint = end;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            this->maze[i][j] = 0;
        }
    }

    this->maze[0][end] = ORIGIN + NO_TOP_WALL;
    mazeCount++;
    while (mazeCount < ROWS * COLUMNS) {
        current = start;
        while (this->maze[current / COLUMNS][current % COLUMNS] < MAZE_UP) {
            direction = move(this, current / COLUMNS, current % COLUMNS);
            this->maze[current / COLUMNS][current % COLUMNS] = direction;

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
        while (this->maze[current / COLUMNS][current % COLUMNS] % 10 < MAZE_UP) {
            this->maze[current / COLUMNS][current % COLUMNS] += 4;
            mazeCount++;
            switch (this->maze[current / COLUMNS][current % COLUMNS] % 10) {
                case MAZE_UP:
                    this->maze[current / COLUMNS][current % COLUMNS] += NO_TOP_WALL;
                    current -= COLUMNS;
                    break;
                case MAZE_DOWN:
                    current += COLUMNS;
                    this->maze[current / COLUMNS][current % COLUMNS] += NO_TOP_WALL;
                    break;
                case MAZE_RIGHT:
                    this->maze[current / COLUMNS][current % COLUMNS] += NO_RIGHT_WALL;
                    current += 1;
                    break;
                case MAZE_LEFT:
                    current -= 1;
                    this->maze[current / COLUMNS][current % COLUMNS] += NO_RIGHT_WALL;
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
            int cell = this->maze[i][j];
            int x = this->actor.world.pos.x + (j * CELL_SIZE) - ((COLUMNS * CELL_SIZE) / 2 - (CELL_SIZE / 2));  //450
            int y = this->actor.world.pos.y + 2.5;
            int z = this->actor.world.pos.z + (i * CELL_SIZE) - ((ROWS * CELL_SIZE) / 2 - (CELL_SIZE / 2)); //450

            rightWall = cell % NO_TOP_WALL < NO_RIGHT_WALL;
            topWall = cell < NO_TOP_WALL;
            if (rightWall) 
            {
                ObjMazeWall* wall = (ObjMazeWall*)Actor_Spawn(&play->actorCtx, play, ACTOR_OBJ_MAZE_WALL, x + 50, y, z, 0, DEG_TO_BINANG(90), 0, 0);
                if (j < COLUMNS - 1) {
                    this->wallActors[wallCount] = wall;
                    wallCount++;
                }
            }
            if (topWall)
            {
                ObjMazeWall* wall = (ObjMazeWall*)Actor_Spawn(&play->actorCtx, play, ACTOR_OBJ_MAZE_WALL, x, y, z - 50, 0, 0, 0, 0);
                if (i > 0)
                {
                    this->wallActors[wallCount] = wall;
                    wallCount++;
                }
            }
        }
    }

    u8 offset = (COLUMNS / 3) * 2;
    start = Rand_S16Offset(offset, COLUMNS - offset);
    for (i = 0; i < COLUMNS; i++) {
        if (i != start % COLUMNS) {
            int x = this->actor.world.pos.x + (i * CELL_SIZE) - ((COLUMNS * CELL_SIZE) / 2 - (CELL_SIZE / 2)); //450
            int y = this->actor.world.pos.y + 2.5;
            int z = this->actor.world.pos.z + ((ROWS * CELL_SIZE) / 2); //500
            Actor_Spawn(&play->actorCtx, play, ACTOR_OBJ_MAZE_WALL, x, y, z, 0, 0, 0, 1);
        }
    }

    for (i = 0; i < ROWS; i++) {
        int x = this->actor.world.pos.x - ((COLUMNS * CELL_SIZE) / 2); //500
        int y = this->actor.world.pos.y + 2.5;
        int z = this->actor.world.pos.z + (i * CELL_SIZE) - ((ROWS * CELL_SIZE) / 2 - (CELL_SIZE / 2)); //450
        Actor_Spawn(&play->actorCtx, play, ACTOR_OBJ_MAZE_WALL, x, y, z, 0, DEG_TO_BINANG(90), 0, 0);
    }

    index = Rand_S16Offset(0, ((ROWS - 1) * (COLUMNS - 1)));
    ObjMazeWall* wall = this->wallActors[index];
    for (i = 0; i < ARM_COUNT; i++)
    {
        while (wall->arm != NULL)
        {
            index = Rand_S16Offset(0, ((ROWS - 1) * (COLUMNS - 1)));
            wall = this->wallActors[index];
        }
        
        wall->arm = Actor_Spawn(&play->actorCtx, play, ACTOR_EN_DHA, 
            wall->dyna.actor.world.pos.x, 
            wall->dyna.actor.world.pos.y, 
            wall->dyna.actor.world.pos.z, 
            0, 0, 0, 7);
        this->armWallId[i] = index;
    }

    for (i = 0; i < KEESE_COUNT; i++)
    {
        index = Rand_S16Offset(0, ROWS * COLUMNS);
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_FIREFLY, 
                    this->actor.world.pos.x + ((index % COLUMNS) * CELL_SIZE) - ((COLUMNS * CELL_SIZE) / 2 - (CELL_SIZE / 2)),
                    this->actor.world.pos.y + 2.5,
                    this->actor.world.pos.z + ((index / COLUMNS) * CELL_SIZE) - ((ROWS * CELL_SIZE) / 2 - (CELL_SIZE / 2)),
                    0, 0, 0, 2); 
    }
    
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
    u8 i;
    u8 j;
    u8 index;
    ObjMazeWall* newHome;

    this->frameCount++;
    this->frameCount2++;

    if (this->frameCount % ORIGIN_SHIFT_DELAY == 0)
    {
        this->frameCount = 0;
        row = this->originShiftPoint / COLUMNS;
        column = this->originShiftPoint % COLUMNS;
        direction = move(this, row, column);
        this->maze[row][column] += direction + LEFT - ORIGIN; // Change the ones place to the new direction
        switch (this->maze[row][column] % 10) {
            case MAZE_UP: // If this cell now points up, remove its top wall and set the above cell to origin
                ObjMaze_SetCellToOrigin(this, row - 1, column);
                this->maze[row][column] += NO_TOP_WALL;
                this->originShiftPoint -= COLUMNS;
                break;
            case MAZE_DOWN: // If this cell now points down, remove the top wall of the cell below and set it to origin
                ObjMaze_SetCellToOrigin(this, row + 1, column);
                this->maze[row + 1][column] += NO_TOP_WALL;
                this->originShiftPoint += COLUMNS;
                break;
            case MAZE_RIGHT: // If this cell now points right, remove its right wall and set the right cell to origin
                ObjMaze_SetCellToOrigin(this, row, column + 1);
                this->maze[row][column] += NO_RIGHT_WALL;
                this->originShiftPoint += 1;
                break;
            case MAZE_LEFT: // If this cell now points left, remove the right wall of the cell to the left and set it to origin
                ObjMaze_SetCellToOrigin(this, row, column - 1);
                this->maze[row][column - 1] += NO_RIGHT_WALL;
                this->originShiftPoint -= 1;
                break;
        }

        u8 wallCount = 0;
        bool rightWall;
        bool topWall;
        for (i = 0; i < ROWS; i++) {
            for (j = 0; j < COLUMNS; j++) {
                int cell = this->maze[i][j];
                int x = this->actor.world.pos.x + (j * CELL_SIZE) - ((COLUMNS * CELL_SIZE) / 2 - (CELL_SIZE / 2));  //450    1000 - (500 - 50) -> 1000 - 450 = 550
                int y = this->actor.world.pos.y + 2.5;
                int z = this->actor.world.pos.z + (i * CELL_SIZE) - ((ROWS * CELL_SIZE) / 2 - (CELL_SIZE / 2)); //450

                rightWall = cell % NO_TOP_WALL < NO_RIGHT_WALL;
                topWall = cell < NO_TOP_WALL;
                if (rightWall) 
                {
                    if (j < COLUMNS - 1) {
                        ObjMazeWall* wall = this->wallActors[wallCount];
                        wall->dyna.actor.world.pos.x = x + 50;
                        wall->dyna.actor.world.pos.y = y;
                        wall->dyna.actor.world.pos.z = z;
                        wall->dyna.actor.world.rot.y = DEG_TO_BINANG(90);
                        wall->dyna.actor.shape.rot.y = wall->dyna.actor.world.rot.y;
                        wallCount += 1;
                    }
                }
                if (topWall)
                {
                    if (i > 0)
                    {
                        ObjMazeWall* wall = this->wallActors[wallCount];
                        wall->dyna.actor.world.pos.x = x;
                        wall->dyna.actor.world.pos.y = y;
                        wall->dyna.actor.world.pos.z = z - 50;
                        wall->dyna.actor.world.rot.y = DEG_TO_BINANG(0);
                        wall->dyna.actor.shape.rot.y = wall->dyna.actor.world.rot.y;
                        wallCount += 1;
                    }
                }
            }
        }
    }

    if (this->frameCount2 % ARM_SHIFT_DELAY == 0) 
    {
        index = Rand_S16Offset(0, ((ROWS - 1) * (COLUMNS - 1)));
        newHome = this->wallActors[index];
        this->frameCount2 = 0;
        for (i = 0; i < ARM_COUNT; i++)
        {
            while (newHome->arm != NULL)
            {
                index = Rand_S16Offset(0, ((ROWS - 1) * (COLUMNS - 1)));
                newHome = this->wallActors[index];
            }

            ObjMazeWall* oldHome = this->wallActors[this->armWallId[i]];
            if (oldHome->arm != NULL && oldHome->arm->xzDistToPlayer > 100.0f)
            {
                newHome->arm = oldHome->arm;
                oldHome->arm = NULL;
                this->armWallId[i] = index;
                newHome->arm->world.pos.x = newHome->dyna.actor.world.pos.x;
                newHome->arm->world.pos.z = newHome->dyna.actor.world.pos.z;
            }
        }
    }
}

void ObjMaze_Draw(Actor* thisx, PlayState* play) {
    ObjMaze* this = (ObjMaze*)thisx;
}

// Add wall back in and remove direction from cell
void ObjMaze_SetCellToOrigin(ObjMaze* this, u8 row, u8 column) {
    switch (this->maze[row][column] % 10) {
        case MAZE_UP:
            this->maze[row][column] -= NO_TOP_WALL;
            this->maze[row][column] += ORIGIN - MAZE_UP;
            break;
        case MAZE_DOWN:
            this->maze[row + 1][column] -= NO_TOP_WALL;
            this->maze[row][column] += ORIGIN - MAZE_DOWN;
            break;
        case MAZE_RIGHT:
            this->maze[row][column] -= NO_RIGHT_WALL;
            this->maze[row][column] += ORIGIN - MAZE_RIGHT;
            break;
        case MAZE_LEFT:
            this->maze[row][column - 1] -= NO_RIGHT_WALL;
            this->maze[row][column] += ORIGIN - MAZE_LEFT;
            break;
    }
}

u8 move(ObjMaze* this, int row, int column) {
    u8 choice = Rand_S16Offset(0, 4);
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
        choice += Rand_S16Offset(1, 3);
    }
}

u8 findEmptyCell(ObjMaze* this) {
    u8 i;
    u8 j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            if (this->maze[i][j] < MAZE_UP) {
                return (i * COLUMNS) + j;
            }
        }
    }

    return 0;
}

void printMaze(ObjMaze* this)
{
    u8 i;
    u8 j;
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLUMNS; j++)
        {
            osSyncPrintf("%d\t", this->maze[i][j]);
        }
        osSyncPrintf("\n");
    }
    osSyncPrintf("\n");
}