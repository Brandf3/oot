#ifndef Z_OBJ_MAZE_H
#define Z_OBJ_MAZE_H

#include "ultra64.h"
#include "global.h"

struct ObjMaze;

typedef void (*ObjMazeActionFunc)(struct ObjMaze*, PlayState*);

typedef struct ObjMaze {
    Actor actor;
    u8 maze[10][10];
    unsigned long int next;
    u8 start;
    u8 originShiftPoint;
    u8 frameCount;
} ObjMaze;

#endif
