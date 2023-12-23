#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "my_scene_scene.h"
#include "segment_symbols.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"
#include "variables.h"

/**
 * Header Child Day (Default)
*/
#define LENGTH_MY_SCENE_ROOM_0_HEADER00_OBJECTLIST 2
#define LENGTH_MY_SCENE_ROOM_0_HEADER00_ACTORLIST 1
SceneCmd my_scene_room_0_header00[] = {
    SCENE_CMD_ECHO_SETTINGS(0x00),
    SCENE_CMD_ROOM_BEHAVIOR(0x00, 0x00, false, false),
    SCENE_CMD_SKYBOX_DISABLES(false, false),
    SCENE_CMD_TIME_SETTINGS(0xFF, 0xFF, 10),
    SCENE_CMD_ROOM_SHAPE(&my_scene_room_0_shapeHeader),
    SCENE_CMD_OBJECT_LIST(LENGTH_MY_SCENE_ROOM_0_HEADER00_OBJECTLIST, my_scene_room_0_header00_objectList),
    SCENE_CMD_ACTOR_LIST(LENGTH_MY_SCENE_ROOM_0_HEADER00_ACTORLIST, my_scene_room_0_header00_actorList),
    SCENE_CMD_END(),
};

s16 my_scene_room_0_header00_objectList[LENGTH_MY_SCENE_ROOM_0_HEADER00_OBJECTLIST] = {
    OBJECT_CHESS,
    OBJECT_B_HEART,
};

ActorEntry my_scene_room_0_header00_actorList[LENGTH_MY_SCENE_ROOM_0_HEADER00_ACTORLIST] = {
    // Custom Actor
    {
        /* Actor ID   */ ACTOR_OBJ_CHESS,
        /* Position   */ { 300, 200, 300 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(90.000) },
        /* Parameters */ 0x0000
    },
};

RoomShapeNormal my_scene_room_0_shapeHeader = {
    ROOM_SHAPE_TYPE_NORMAL,
    ARRAY_COUNT(my_scene_room_0_shapeDListEntry),
    my_scene_room_0_shapeDListEntry,
    my_scene_room_0_shapeDListEntry + ARRAY_COUNT(my_scene_room_0_shapeDListEntry)
};

RoomShapeDListsEntry my_scene_room_0_shapeDListEntry[1] = {
    { my_scene_room_0_entry_0_opaque, NULL },
};

Gfx my_scene_room_0_entry_0_opaque[] = {
	gsSPDisplayList(my_scene_dl_Ground_mesh_layer_Opaque),
	gsSPEndDisplayList(),
};

Vtx my_scene_dl_Ground_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {-700, 0, 700}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-700, 0, 700}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-700, 0, -700}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-700, 0, -700}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {700, 0, 700}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {700, 0, 700}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {700, 0, -700}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {700, 0, -700}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx my_scene_dl_Ground_mesh_layer_Opaque_vtx_0[4] = {
	{{ {-700, 0, 700}, 0, {-16, 1008}, {0, 127, 0, 255} }},
	{{ {700, 0, 700}, 0, {1008, 1008}, {0, 127, 0, 255} }},
	{{ {700, 0, -700}, 0, {1008, -16}, {0, 127, 0, 255} }},
	{{ {-700, 0, -700}, 0, {-16, -16}, {0, 127, 0, 255} }},
};

Gfx my_scene_dl_Ground_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(my_scene_dl_Ground_mesh_layer_Opaque_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_my_scene_dl_grass_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 162, 255, 141, 255),
	gsSPEndDisplayList(),
};

Gfx my_scene_dl_Ground_mesh_layer_Opaque[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(my_scene_dl_Ground_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_my_scene_dl_grass_layerOpaque),
	gsSPDisplayList(my_scene_dl_Ground_mesh_layer_Opaque_tri_0),
	gsSPEndDisplayList(),
};

