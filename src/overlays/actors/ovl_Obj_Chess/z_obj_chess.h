#ifndef Z_CHESS_H
#define Z_OBJ_CHESS_H

#include "ultra64.h"
#include "global.h"

struct ObjChess;

typedef void (*ObjChessActionFunc)(struct ObjChess*, PlayState*);

typedef struct ObjChess {
    DynaPolyActor dyna;
    s8 puzzleStep;
    s8 pieceToMove;
    s8 destination;
    s8 chessBoard[8][8];
    char fen[72];
    Vec3f vertexA;
    Vec3f vertexB;
    Vec3f vertexC;
    Vec3f vertexD;
    ColliderQuad collider;
} ObjChess; 

#endif
