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
} Direction;

void ObjMaze_Init(Actor* thisx, PlayState* play) {
    ObjMaze* this = (ObjMaze*)thisx;
    this->next = gSaveContext.save.dayTime + play->gameplayFrames;

    u8 i;
    u8 j;
    u8 current;
    u8 direction;
    u8 mazeCount = 0;
    u8 start = rand(this, 90, 10);
    u8 end = rand(this, 0, 10);
    
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            this->maze[i][j].direction = EMPTY;
            this->maze[i][j].top_wall = true;
            this->maze[i][j].right_wall = true;
        }
    }

    this->maze[0][end].direction = MAZE_UP;
    this->maze[0][end].top_wall = false;
    mazeCount++;
    while (mazeCount < 100) {
        current = start;
        while (this->maze[current / 10][current % 10].direction < MAZE_UP) {
            direction = move(this, current / 10, current % 10);
            this->maze[current / 10][current % 10].direction = direction;

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
        while (this->maze[current / 10][current % 10].direction < MAZE_UP) {
            this->maze[current / 10][current % 10].direction += 4;
            mazeCount++;
            switch (this->maze[current / 10][current % 10].direction) {
                case MAZE_UP:
                    this->maze[current / 10][current % 10].top_wall = false;
                    current -= 10;
                    break;
                case MAZE_DOWN:
                    current += 10;
                    this->maze[current / 10][current % 10].top_wall = false;
                    break;
                case MAZE_RIGHT:
                    this->maze[current / 10][current % 10].right_wall = false;
                    current += 1;
                    break;
                case MAZE_LEFT:
                    current -= 1;
                    this->maze[current / 10][current % 10].right_wall = false;
                    break;
            }
        }

        start = findEmptyCell(this);
    }

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            osSyncPrintf("(%d, %d, %d)", this->maze[i][j].direction, this->maze[i][j].top_wall, this->maze[i][j].right_wall);
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
            if (this->maze[i][j].direction < MAZE_UP) {
                return (i * 10) + j;
            }
        }
    }

    return 0;
}
