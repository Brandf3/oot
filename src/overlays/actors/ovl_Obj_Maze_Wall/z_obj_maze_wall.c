/*
 * File: z_obj_maze_wall.c
 * Overlay: ovl_Obj_Maze_Wall
 * Description: Maze Wall
 */

#include "z_obj_maze_wall.h"
#include "assets/objects/object_maze/gMazeWallDL.h"

#define FLAGS 0

void ObjMazeWall_Init(Actor* thisx, PlayState* play);
void ObjMazeWall_Destroy(Actor* thisx, PlayState* play);
void ObjMazeWall_Update(Actor* thisx, PlayState* play);
void ObjMazeWall_Draw(Actor* thisx, PlayState* play);

ActorInit Obj_Maze_Wall_InitVars = {
    /**/ ACTOR_OBJ_MAZE_WALL,
    /**/ ACTORCAT_BG,
    /**/ FLAGS,
    /**/ OBJECT_MAZE,
    /**/ sizeof(ObjMazeWall),
    /**/ ObjMazeWall_Init,
    /**/ ObjMazeWall_Destroy,
    /**/ ObjMazeWall_Update,
    /**/ ObjMazeWall_Draw,
};

void ObjMazeWall_Init(Actor* thisx, PlayState* play) {
    ObjMazeWall* this = (ObjMazeWall*)thisx;

    DynaPolyActor_Init(&this->dyna, 0);
    CollisionHeader* colHeader = NULL;
    CollisionHeader_GetVirtual(&gMazeWallDL_collisionHeader, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);
}

void ObjMazeWall_Destroy(Actor* thisx, PlayState* play) {
    ObjMazeWall* this = (ObjMazeWall*)thisx;
    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void ObjMazeWall_Update(Actor* thisx, PlayState* play) {
    ObjMazeWall* this = (ObjMazeWall*)thisx;
}

void ObjMazeWall_Draw(Actor* thisx, PlayState* play) {
    ObjMazeWall* this = (ObjMazeWall*)thisx;
    OPEN_DISPS(play->state.gfxCtx, "../z_obj_maze_wall.c", 43);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx, "../z_obj_maze.c", 158), G_MTX_MODELVIEW | G_MTX_LOAD);
    if (this->dyna.actor.params == 1) {
        // Set the color for the teleporter wall
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 0, 0, 255);
    } else {
        // Set a default color for regular walls
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, 255);
    }
    gSPDisplayList(POLY_OPA_DISP++, gMazeWallDL);
    //Gfx_DrawDListOpa(play, gMazeWallDL);
    CLOSE_DISPS(play->state.gfxCtx, "../z_obj_maze_wall.c", 47);
}
