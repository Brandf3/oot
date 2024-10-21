#ifndef Z_OBJ_MAZE_WALL_H
#define Z_OBJ_MAZE_WALL_H

#include "ultra64.h"
#include "global.h"

struct ObjMazeWall;

typedef void (*ObjMazeWallActionFunc)(struct ObjMazeWall*, PlayState*);

typedef struct ObjMazeWall {
    DynaPolyActor dyna;
    Actor* arm;
} ObjMazeWall;

#endif
