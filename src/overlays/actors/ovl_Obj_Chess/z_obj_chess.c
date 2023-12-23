/*
 * File: z_obj_chess.c
 * Overlay: ObjChess
 * Description: Chess Puzzle
 */

#include "z_obj_chess.h"
#include "assets/objects/object_chess/gChessboardDL.h"
#include "assets/objects/object_chess/gChessboardDL_collision.h"
#include "assets/objects/object_chess/gKingDL.h"
#include "assets/objects/object_chess/gQueenDL.h"
#include "assets/objects/object_chess/gRookDL.h"
#include "assets/objects/object_chess/gBishopDL.h"
#include "assets/objects/object_chess/gKnightDL.h"
#include "assets/objects/object_chess/gPawnDL.h"

#define FLAGS (ACTOR_FLAG_4 | ACTOR_FLAG_5)

void ObjChess_Init(Actor* thisx, PlayState* play);
void ObjChess_Destroy(Actor* thisx, PlayState* play);
void ObjChess_Update(Actor* thisx, PlayState* play);
void ObjChess_Draw(Actor* thisx, PlayState* play);

void ObjChess_DrawPieces(ObjChess* this, PlayState* play);
void ObjChess_Collision(ObjChess* this, PlayState* play);
void ObjChess_Win(ObjChess* this, PlayState* play);
void ObjChess_Reset(ObjChess* this, PlayState* play);
void ObjChess_Move(ObjChess* this, PlayState* play);
bool ObjChess_CheckMove(ObjChess* this, PlayState* play);
void ObjChess_ConvertToFEN(ObjChess* this, PlayState* play);
void ObjChess_PopulateBoard(ObjChess* this, PlayState* play, char fen[]);
void ObjChess_RotateVector(ObjChess* this, PlayState* play, Vec3f* vec);
void ObjChess_UnrotateVector(ObjChess* this, PlayState* play, Vec3f* vec);

static ColliderQuadInit sQuadInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_2,
        COLSHAPE_QUAD,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { DMG_SLINGSHOT, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

ActorInit Obj_Chess_InitVars = {
    ACTOR_OBJ_CHESS,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_CHESS,
    sizeof(ObjChess),
    (ActorFunc)ObjChess_Init,
    (ActorFunc)ObjChess_Destroy,
    (ActorFunc)ObjChess_Update,
    (ActorFunc)ObjChess_Draw,
};

typedef enum {
    EMPTY,
    BLACK_PAWN,
    BLACK_KNIGHT,
    BLACK_BISHOP,
    BLACK_ROOK,
    BLACK_QUEEN,
    BLACK_KING,
    WHITE_PAWN,
    WHITE_KNIGHT,
    WHITE_BISHOP,
    WHITE_ROOK,
    WHITE_QUEEN,
    WHITE_KING,
} Pieces;

// One move checkmate example
// char puzzle[2][72] = {
//     {"4r3/pb1rPkp1/1p6/3p4/P2B3K/2P3R1/2P5/4R3"}, // Starting position
//     {"4r3/pb1rPkR1/1p6/3p4/P2B3K/2P5/2P5/4R3"} // Final position with mate
// };

// Two move checkmate example
// char puzzle[4][72] = {
//     {"1q3rk1/3b1pp1/2pbn3/4p3/1P1pN3/2PP2QP/3r1PP1/1R3RK1"}, // Starting position
//     {"1q3rk1/3b1pp1/2pbnN2/4p3/1P1p4/2PP2QP/3r1PP1/1R3RK1"}, // First white movement
//     {"1q3r1k/3b1pp1/2pbnN2/4p3/1P1p4/2PP2QP/3r1PP1/1R3RK1"}, // First black movement
//     {"1q3r1k/3b1pp1/2pbnN2/4p3/1P1p3Q/2PP3P/3r1PP1/1R3RK1"}, // Final position with mate
// };

// Long puzzle with promotion example, can use the same concept for castling
char puzzle[21][72] = {
    {"7K/P1p1p1p1/2P1P1Pk/6pP/3p2P1/1P6/3P4/8"}, // Starting position
    {"P6K/2p1p1p1/2P1P1Pk/6pP/3p2P1/1P6/3P4/8"}, // First white movement
    {"N6K/2p1p1p1/2P1P1Pk/6pP/6P1/1P1p4/3P4/8"}, // Promotion + black movement
    {"7K/2p1p1p1/1NP1P1Pk/6pP/6P1/1P1p4/3P4/8"},
    {"7K/4p1p1/1pP1P1Pk/6pP/6P1/1P1p4/3P4/8"},
    {"7K/2P1p1p1/1p2P1Pk/6pP/6P1/1P1p4/3P4/8"},
    {"7K/2P1p1p1/4P1Pk/1p4pP/6P1/1P1p4/3P4/8"},
    {"2P4K/4p1p1/4P1Pk/1p4pP/6P1/1P1p4/3P4/8"},
    {"2N4K/4p1p1/4P1Pk/6pP/1p4P1/1P1p4/3P4/8"}, // Promotion + black movement
    {"7K/4p1p1/3NP1Pk/6pP/1p4P1/1P1p4/3P4/8"},
    {"7K/6p1/3pP1Pk/6pP/1p4P1/1P1p4/3P4/8"},
    {"7K/4P1p1/3p2Pk/6pP/1p4P1/1P1p4/3P4/8"},
    {"7K/4P1p1/6Pk/3p2pP/1p4P1/1P1p4/3P4/8"},
    {"4P2K/6p1/6Pk/3p2pP/1p4P1/1P1p4/3P4/8"},
    {"4N2K/6p1/6Pk/6pP/1p1p2P1/1P1p4/3P4/8"}, // Promotion + black movement
    {"7K/6p1/5NPk/6pP/1p1p2P1/1P1p4/3P4/8"},
    {"7K/8/5pPk/6pP/1p1p2P1/1P1p4/3P4/8"},
    {"7K/6P1/5p1k/6pP/1p1p2P1/1P1p4/3P4/8"},
    {"7K/6P1/7k/5ppP/1p1p2P1/1P1p4/3P4/8"},
    {"6PK/8/7k/5ppP/1p1p2P1/1P1p4/3P4/8"},
    {"6NK/8/7k/5ppP/1p1p2P1/1P1p4/3P4/8"}, // Promotion + checkmate
};

void ObjChess_Init(Actor* thisx, PlayState* play) {
    ObjChess* this = (ObjChess*)thisx;

    CollisionHeader* colHeader = NULL;
    CollisionHeader_GetVirtual(&gChessboardDL_collisionHeader, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);
    
    ObjChess_Reset(this, play);   
    this->pieceToMove = -1;
    this->destination = -1;

    this->vertexA.x = 200.0f;
    this->vertexA.y = 0.0f;
    this->vertexA.z = 200.0f;

    this->vertexB.x = 200.0f;
    this->vertexB.y = 0.0f;
    this->vertexB.z = -200.0f;

    this->vertexC.x = -200.0f;
    this->vertexC.y = 0.0f;
    this->vertexC.z = 200.0f;

    this->vertexD.x = -200.0f;
    this->vertexD.y = 0.0f;
    this->vertexD.z = -200.0f;

    ObjChess_RotateVector(this, play, &this->vertexA);
    ObjChess_RotateVector(this, play, &this->vertexB);
    ObjChess_RotateVector(this, play, &this->vertexC);
    ObjChess_RotateVector(this, play, &this->vertexD);

    this->vertexA.x += this->dyna.actor.world.pos.x;
    this->vertexA.y += this->dyna.actor.world.pos.y;
    this->vertexA.z += this->dyna.actor.world.pos.z;

    this->vertexB.x += this->dyna.actor.world.pos.x;
    this->vertexB.y += this->dyna.actor.world.pos.y;
    this->vertexB.z += this->dyna.actor.world.pos.z;

    this->vertexC.x += this->dyna.actor.world.pos.x;
    this->vertexC.y += this->dyna.actor.world.pos.y;
    this->vertexC.z += this->dyna.actor.world.pos.z;

    this->vertexD.x += this->dyna.actor.world.pos.x;
    this->vertexD.y += this->dyna.actor.world.pos.y;
    this->vertexD.z += this->dyna.actor.world.pos.z;

    Collider_InitQuad(play, &this->collider);
    Collider_SetQuad(play, &this->collider, &this->dyna.actor, &sQuadInit);
}

void ObjChess_Destroy(Actor* thisx, PlayState* play) {
    ObjChess* this = (ObjChess*)thisx;
    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyQuad(play, &this->collider);
}

void ObjChess_Update(Actor* thisx, PlayState* play) {
    ObjChess* this = (ObjChess*)thisx;
    ObjChess_Collision(this, play);
    Collider_SetQuadVertices(&this->collider, &this->vertexA, &this->vertexB, &this->vertexC, &this->vertexD);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
}

void ObjChess_Draw(Actor* thisx, PlayState* play) {
    ObjChess* this = (ObjChess*)thisx;
    Gfx_DrawDListOpa(play, gChessboardDL);
    ObjChess_DrawPieces(this, play);
}

void ObjChess_DrawPieces(ObjChess* this, PlayState* play) {
    int i;
    int j;

    OPEN_DISPS(play->state.gfxCtx, "../z_obj_chess.c", 174);
    
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            int piece = this->chessBoard[i][j];
            if (piece != EMPTY) {
                Vec3f piecePosition;
                piecePosition.x = (j * 50) - 175;
                piecePosition.y = 5;
                piecePosition.z = (i * 50) - 175;

                ObjChess_RotateVector(this, play, &piecePosition);
                piecePosition.x += this->dyna.actor.world.pos.x;
                piecePosition.y += this->dyna.actor.world.pos.y;
                piecePosition.z += this->dyna.actor.world.pos.z;

                Matrix_Translate(piecePosition.x, piecePosition.y, piecePosition.z, MTXMODE_NEW);
                Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);

                // Makes pieces face outward no matter the rotation
                //Matrix_RotateZYX(this->dyna.actor.shape.rot.x, this->dyna.actor.shape.rot.y, this->dyna.actor.shape.rot.z, MTXMODE_APPLY);

                if (piece >= WHITE_PAWN) {
                    Matrix_RotateY(DEG_TO_RAD(90), MTXMODE_APPLY);
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 200, 200, 200, 255);
                } else {
                    Matrix_RotateY(DEG_TO_RAD(270), MTXMODE_APPLY);
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 64, 64, 64, 255);
                }
                
                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx, "../z_obj_chess.c", 175),
                G_MTX_MODELVIEW | G_MTX_LOAD);

                switch(piece) {
                    case BLACK_PAWN:
                    case WHITE_PAWN:
                        gSPDisplayList(POLY_OPA_DISP++, gPawnDL);
                        break;
                    case BLACK_KNIGHT:
                    case WHITE_KNIGHT:
                        gSPDisplayList(POLY_OPA_DISP++, gKnightDL);
                        break;
                    case BLACK_BISHOP:
                    case WHITE_BISHOP:
                        gSPDisplayList(POLY_OPA_DISP++, gBishopDL);
                        break;
                    case BLACK_ROOK:
                    case WHITE_ROOK:
                        gSPDisplayList(POLY_OPA_DISP++, gRookDL);
                        break;
                    case BLACK_QUEEN:
                    case WHITE_QUEEN:
                        gSPDisplayList(POLY_OPA_DISP++, gQueenDL);
                        break;
                    case BLACK_KING:
                    case WHITE_KING:
                        gSPDisplayList(POLY_OPA_DISP++, gKingDL);
                        break;
                }
            }
        }
    }
    
    CLOSE_DISPS(play->state.gfxCtx, "../z_obj_chess.c", 228);
}

void ObjChess_Collision(ObjChess* this, PlayState* play) {
    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;

        Vec3f hitMark;
        hitMark.x = (this->collider.info.bumper.hitPos.x - this->dyna.actor.world.pos.x);
        hitMark.y = (this->collider.info.bumper.hitPos.y - this->dyna.actor.world.pos.y);
        hitMark.z = (this->collider.info.bumper.hitPos.z - this->dyna.actor.world.pos.z);

        ObjChess_UnrotateVector(this, play, &hitMark);
        hitMark.x = (hitMark.x + 200) / 50;
        hitMark.y = (hitMark.y + 200) / 50;
        hitMark.z = (hitMark.z + 200) / 50;

        int column = hitMark.x;
        int row = hitMark.z;
        int squareHit = column + (row * 8);

        if (this->pieceToMove == -1) {
            this->pieceToMove = squareHit;
        } else {
            if (squareHit == this->pieceToMove) { // If they hit the same square twice deselect it
                this->pieceToMove = -1;
            } else {
                this->destination = squareHit;
                ObjChess_Move(this, play);
            }
        }
    }
}

void ObjChess_Win(ObjChess* this, PlayState* play) {
    SEQCMD_PLAY_SEQUENCE(SEQ_PLAYER_BGM_MAIN, 0, 0, NA_BGM_HEART_GET);
    Actor_Spawn(&play->actorCtx, play, ACTOR_ITEM_B_HEART, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                            this->dyna.actor.world.pos.z, 0, 0, 0, 0);
    osSyncPrintf("Congrats, you won!!");
}

void ObjChess_Reset(ObjChess* this, PlayState* play) {
    ObjChess_PopulateBoard(this, play, puzzle[0]);
    this->puzzleStep = 1;
}

void ObjChess_Move(ObjChess* this, PlayState* play) {
    this->chessBoard[this->destination / 8][this->destination % 8] = this->chessBoard[this->pieceToMove / 8][this->pieceToMove % 8];
    this->chessBoard[this->pieceToMove / 8][this->pieceToMove % 8] = EMPTY;
    this->pieceToMove = -1;
    this->destination = -1;
    ObjChess_ConvertToFEN(this, play);

    if (ObjChess_CheckMove(this, play)) {
        this->puzzleStep++;
        if (this->puzzleStep != sizeof(puzzle) / sizeof(puzzle[0])) { // Black makes its move
            ObjChess_PopulateBoard(this, play, puzzle[this->puzzleStep]);
            this->puzzleStep++;
        }
        
        if (this->puzzleStep == sizeof(puzzle) / sizeof(puzzle[0])) {
            ObjChess_Win(this, play);
        } else {
            Sfx_PlaySfxCentered(NA_SE_SY_CORRECT_CHIME);
        }
    } else { 
        Sfx_PlaySfxCentered(NA_SE_SY_ERROR);
        ObjChess_PopulateBoard(this, play, puzzle[this->puzzleStep - 1]);
        //ObjChess_Reset(this, play); // If you want to reset puzzle on failure
    }
}

// Checks if the player's move matches the next step in the puzzle
bool ObjChess_CheckMove(ObjChess* this, PlayState* play) {
    int i = 0;
    while (this->fen[i] != '\0') {
        if (this->fen[i] != puzzle[this->puzzleStep][i]) {
            return false;
        }
        i++;
    }
    return true;
}

void ObjChess_ConvertToFEN(ObjChess* this, PlayState* play) {
    int i;
    int j;
    int fenIndex = 0;

    for (i = 0; i < 8; i++) {
        s8 emptyCount = 0;
        for (j = 0; j < 8; j++) {
            if (this->chessBoard[i][j] == EMPTY) {
                emptyCount++;
            } else {
                if (emptyCount > 0) {
                    this->fen[fenIndex++] = emptyCount + '0';
                    emptyCount = 0;
                }

                switch(this->chessBoard[i][j]) {
                    case BLACK_PAWN:
                        this->fen[fenIndex] = 'p';
                        break;
                    case BLACK_KNIGHT:
                        this->fen[fenIndex] = 'n';
                        break;
                    case BLACK_BISHOP:
                        this->fen[fenIndex] = 'b';
                        break;
                    case BLACK_ROOK:
                        this->fen[fenIndex] = 'r';
                        break;
                    case BLACK_QUEEN:
                        this->fen[fenIndex] = 'q';
                        break;
                    case BLACK_KING:
                        this->fen[fenIndex] = 'k';
                        break;
                    case WHITE_PAWN:
                        this->fen[fenIndex] = 'P';
                        break;
                    case WHITE_KNIGHT:
                        this->fen[fenIndex] = 'N';
                        break;
                    case WHITE_BISHOP:
                        this->fen[fenIndex] = 'B';
                        break;
                    case WHITE_ROOK:
                        this->fen[fenIndex] = 'R';
                        break;
                    case WHITE_QUEEN:
                        this->fen[fenIndex] = 'Q';
                        break;
                    case WHITE_KING:
                        this->fen[fenIndex] = 'K';
                        break;
                }
                fenIndex++;
            }
        }
        
        if (emptyCount > 0)
        {
            this->fen[fenIndex++] = emptyCount + '0';
        }

        if (i < 7) {
            this->fen[fenIndex++] = '/';
        }
    }

    this->fen[fenIndex] = '\0';
}

void ObjChess_PopulateBoard(ObjChess* this, PlayState* play, char fen[]) {
    int i = 0;
    int j;
    int boardRank = 0;
    int boardColumn = 0;

    while (fen[i] != '\0') {
        if (fen[i] >= '0' && fen[i] <= '8') {
            for (j = 0; j < fen[i] - '0'; j++) {
                this->chessBoard[boardRank][boardColumn] = EMPTY;
                boardColumn++;
            }
        } else {
            switch(fen[i]) {
                case 'p':
                    this->chessBoard[boardRank][boardColumn] = BLACK_PAWN;
                    break;
                case 'n':
                    this->chessBoard[boardRank][boardColumn] = BLACK_KNIGHT;
                    break;
                case 'b':
                    this->chessBoard[boardRank][boardColumn] = BLACK_BISHOP;
                    break;
                case 'r':
                    this->chessBoard[boardRank][boardColumn] = BLACK_ROOK;
                    break;
                case 'q':
                    this->chessBoard[boardRank][boardColumn] = BLACK_QUEEN;
                    break;
                case 'k':
                    this->chessBoard[boardRank][boardColumn] = BLACK_KING;
                    break;
                case 'P':
                    this->chessBoard[boardRank][boardColumn] = WHITE_PAWN;
                    break;
                case 'N':
                    this->chessBoard[boardRank][boardColumn] = WHITE_KNIGHT;
                    break;
                case 'B':
                    this->chessBoard[boardRank][boardColumn] = WHITE_BISHOP;
                    break;
                case 'R':
                    this->chessBoard[boardRank][boardColumn] = WHITE_ROOK;
                    break;
                case 'Q':
                    this->chessBoard[boardRank][boardColumn] = WHITE_QUEEN;
                    break;
                case 'K':
                    this->chessBoard[boardRank][boardColumn] = WHITE_KING;
                    break;
                case '/':
                    boardRank++;
                    boardColumn = -1;
                    break;
            }

            boardColumn++;
        }
        i++;
    }
}

void ObjChess_RotateVector(ObjChess* this, PlayState* play, Vec3f* vec) {
    s16 z = this->dyna.actor.shape.rot.z;
    s16 y = this->dyna.actor.shape.rot.y;
    s16 x = this->dyna.actor.shape.rot.x;
    f32 temp1;
    f32 temp2;
    f32 sin;
    f32 cos;

    if (z != 0) {
        sin = Math_SinS(z);
        cos = Math_CosS(z);
        
        temp1 = vec->x;
        temp2 = vec->y;
        vec->x = temp1 * cos - temp2 * sin;
        vec->y = temp2 * cos + temp1 * sin;
    }

    if (y != 0) {
        sin = Math_SinS(y);
        cos = Math_CosS(y);

        temp1 = vec->x;
        temp2 = vec->z;
        vec->x = temp1 * cos + temp2 * sin;
        vec->z = temp1 * sin * -1 + temp2 * cos;
    }

    if (x != 0) {
        sin = Math_SinS(x);
        cos = Math_CosS(x);

        temp1 = vec->y;
        temp2 = vec->z;
        vec->y = temp1 * cos - temp2 * sin;
        vec->z = temp2 * cos + temp1 * sin;
    }
}

void ObjChess_UnrotateVector(ObjChess* this, PlayState* play, Vec3f* vec) {
    s16 z = this->dyna.actor.shape.rot.z;
    s16 y = this->dyna.actor.shape.rot.y;
    s16 x = this->dyna.actor.shape.rot.x;
    f32 temp1;
    f32 temp2;
    f32 sin;
    f32 cos;

    if (z != 0) {
        sin = Math_SinS(z);
        cos = Math_CosS(z);

        temp1 = vec->x;
        temp2 = vec->y;
        vec->x = temp1 * cos + temp2 * sin;
        vec->y = temp2 * cos - temp1 * sin;
    }

    if (y != 0) {
        sin = Math_SinS(y);
        cos = Math_CosS(y);

        temp1 = vec->x;
        temp2 = vec->z;
        vec->x = temp1 * cos - temp2 * sin;
        vec->z = temp1 * sin + temp2 * cos;
    }

    if (x != 0) {
        sin = Math_SinS(x);
        cos = Math_CosS(x);

        temp1 = vec->y;
        temp2 = vec->z;
        vec->y = temp1 * cos + temp2 * sin;
        vec->z = temp2 * cos - temp1 * sin;
    }
}

