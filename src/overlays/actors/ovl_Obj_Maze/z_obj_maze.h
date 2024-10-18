#ifndef Z_OBJ_MAZE_H
#define Z_OBJ_MAZE_H

#include "ultra64.h"
#include "global.h"

typedef struct {
    u8 type;           // Cell type (e.g., MAZE_UP, MAZE_DOWN, etc.)
    s8 rightWallIdx;   // Index in the wallActors array for the right wall (-1 if no right wall)
    s8 topWallIdx;     // Index in the wallActors array for the top wall (-1 if no top wall)
} Cell;

struct ObjMaze;

typedef void (*ObjMazeActionFunc)(struct ObjMaze*, PlayState*);

typedef struct ObjMaze {
    Actor actor;
    Cell maze[10][10];
    Actor* wallActors[101];
    unsigned long int next;
    u8 start;
    u8 originShiftPoint;
    u8 frameCount;
} ObjMaze;

#endif
