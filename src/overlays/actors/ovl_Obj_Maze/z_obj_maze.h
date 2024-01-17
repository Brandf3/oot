#ifndef Z_OBJ_MAZE_H
#define Z_OBJ_MAZE_H

#include "ultra64.h"
#include "global.h"

struct ObjMaze;

typedef void (*ObjMazeActionFunc)(struct ObjMaze*, PlayState*);

typedef struct Cell {
    u8 direction;
    bool top_wall;
    bool right_wall;
} Cell;

typedef struct ObjMaze {
    Cell maze[10][10];
    unsigned long int next;
} ObjMaze;

#endif
