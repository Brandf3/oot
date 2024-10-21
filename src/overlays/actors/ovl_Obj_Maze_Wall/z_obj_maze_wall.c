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

ActorProfile Obj_Maze_Wall_Profile = {
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
    this->arm = NULL;
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

    if (this->arm != NULL)
    {
        this->arm->world.pos.x = this->dyna.actor.world.pos.x;
        this->arm->world.pos.z = this->dyna.actor.world.pos.z;
    }
}

void ObjMazeWall_Draw(Actor* thisx, PlayState* play) {
    ObjMazeWall* this = (ObjMazeWall*)thisx;
    OPEN_DISPS(play->state.gfxCtx, "../z_obj_maze_wall.c", 43);
    if (this->arm != NULL) {
        // Set the color for deadhand walls if you want visual que
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, 255);
    } else {
        // Set a default color for regular walls
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, 255);
    }
    Gfx_DrawDListOpa(play, gMazeWallDL);
    CLOSE_DISPS(play->state.gfxCtx, "../z_obj_maze_wall.c", 47);
}
