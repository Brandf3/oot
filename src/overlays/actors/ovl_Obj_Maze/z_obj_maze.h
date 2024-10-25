#ifndef Z_OBJ_MAZE_H
#define Z_OBJ_MAZE_H

#include "ultra64.h"
#include "global.h"
#include "src/overlays/actors/ovl_Obj_Maze_Wall/z_obj_maze_wall.h"

#define ROWS 10
#define COLUMNS 15
#define ORIGIN_SHIFT_DELAY 4
#define ARM_COUNT 6
#define ARM_SHIFT_DELAY 200
#define KEESE_COUNT 5
#define CELL_SIZE 100

struct ObjMaze;

typedef void (*ObjMazeActionFunc)(struct ObjMaze*, PlayState*);

typedef struct ObjMaze {
    Actor actor;
    u8 maze[ROWS][COLUMNS];
    ObjMazeWall* wallActors[((ROWS - 1) * (COLUMNS - 1))];
    unsigned long int next;
    u8 originShiftPoint;
    u8 frameCount;
    u8 frameCount2;
    u8 armWallId[ARM_COUNT];
} ObjMaze;

#endif
