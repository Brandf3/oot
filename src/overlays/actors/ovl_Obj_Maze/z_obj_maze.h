#ifndef Z_OBJ_MAZE_H
#define Z_OBJ_MAZE_H

#include "ultra64.h"
#include "global.h"

#define ROWS 10
#define COLUMNS 20
#define ORIGIN_SHIFT_DELAY 10
#define TELEPORTER_SHIFT_DELAY 200
#define TELEPORTER_COOLDOWN 100
#define CELL_SIZE 100

typedef struct {
    u8 type;           // Cell type (e.g., MAZE_UP, MAZE_DOWN, etc.)
    s8 rightWallIdx;   // Index in the wallActors array for the right wall (-1 if no right wall)
    s8 topWallIdx;     // Index in the wallActors array for the top wall (-1 if no top wall)
} Cell;

struct ObjMaze;

typedef void (*ObjMazeActionFunc)(struct ObjMaze*, PlayState*);

typedef struct ObjMaze {
    Actor actor;
    Cell maze[ROWS][COLUMNS];
    Actor* wallActors[((ROWS - 1) * (COLUMNS - 1))];
    unsigned long int next;
    u8 originShiftPoint;
    u8 frameCount;
    u8 frameCount2;
    u8 portalOneIdx;
    u8 portalTwoIdx;
    u8 teleportCooldown;
} ObjMaze;

#endif
