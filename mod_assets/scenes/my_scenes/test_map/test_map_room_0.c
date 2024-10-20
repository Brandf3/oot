#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "test_map_scene.h"
#include "segment_symbols.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"
#include "variables.h"

/**
 * Header Child Day (Default)
*/
#define LENGTH_TEST_MAP_ROOM_0_HEADER00_OBJECTLIST 1
#define LENGTH_TEST_MAP_ROOM_0_HEADER00_ACTORLIST 1
SceneCmd test_map_room_0_header00[] = {
    SCENE_CMD_ECHO_SETTINGS(0x00),
    SCENE_CMD_ROOM_BEHAVIOR(0x00, 0x00, false, false),
    SCENE_CMD_SKYBOX_DISABLES(false, false),
    SCENE_CMD_TIME_SETTINGS(0xFF, 0xFF, 10),
    SCENE_CMD_ROOM_SHAPE(&test_map_room_0_shapeHeader),
    SCENE_CMD_OBJECT_LIST(LENGTH_TEST_MAP_ROOM_0_HEADER00_OBJECTLIST, test_map_room_0_header00_objectList),
    SCENE_CMD_ACTOR_LIST(LENGTH_TEST_MAP_ROOM_0_HEADER00_ACTORLIST, test_map_room_0_header00_actorList),
    SCENE_CMD_END(),
};

s16 test_map_room_0_header00_objectList[LENGTH_TEST_MAP_ROOM_0_HEADER00_OBJECTLIST] = {
    OBJECT_MAZE,
	//OBJECT_RD,
	//OBJECT_DH,
};

ActorEntry test_map_room_0_header00_actorList[LENGTH_TEST_MAP_ROOM_0_HEADER00_ACTORLIST] = {
    // Custom Actor
    {
        /* Actor ID   */ ACTOR_OBJ_MAZE,
        /* Position   */ { 0, 0, 0 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x0000
    },
	// {
    //     /* Actor ID   */ ACTOR_EN_RD,
    //     /* Position   */ { 50, 0, 0 },
    //     /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000) },
    //     /* Parameters */ 0x0001
    // },
	// {
    //     /* Actor ID   */ ACTOR_EN_DHA,
    //     /* Position   */ { 50, 0, 0 },
    //     /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000) },
    //     /* Parameters */ 0x0002
    // },
};

RoomShapeNormal test_map_room_0_shapeHeader = {
    ROOM_SHAPE_TYPE_NORMAL,
    ARRAY_COUNT(test_map_room_0_shapeDListEntry),
    test_map_room_0_shapeDListEntry,
    test_map_room_0_shapeDListEntry + ARRAY_COUNT(test_map_room_0_shapeDListEntry)
};

RoomShapeDListsEntry test_map_room_0_shapeDListEntry[1] = {
    { test_map_room_0_entry_0_opaque, NULL },
};

Gfx test_map_room_0_entry_0_opaque[] = {
	gsSPDisplayList(test_map_dl_Ground_mesh_layer_Opaque),
	gsSPEndDisplayList(),
};

Vtx test_map_dl_Ground_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {-1000, 0, 1000}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-1000, 0, 1000}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-1000, 0, -1000}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-1000, 0, -1000}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {1000, 0, 1000}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {1000, 0, 1000}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {1000, 0, -1000}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {1000, 0, -1000}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx test_map_dl_Ground_mesh_layer_Opaque_vtx_0[4] = {
	{{ {-1000, 0, 1000}, 0, {-16, 1008}, {0, 127, 0, 255} }},
	{{ {1000, 0, 1000}, 0, {1008, 1008}, {0, 127, 0, 255} }},
	{{ {1000, 0, -1000}, 0, {1008, -16}, {0, 127, 0, 255} }},
	{{ {-1000, 0, -1000}, 0, {-16, -16}, {0, 127, 0, 255} }},
};

Gfx test_map_dl_Ground_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(test_map_dl_Ground_mesh_layer_Opaque_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_test_map_dl_grass_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 162, 255, 141, 255),
	gsSPEndDisplayList(),
};

Gfx test_map_dl_Ground_mesh_layer_Opaque[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(test_map_dl_Ground_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_test_map_dl_grass_layerOpaque),
	gsSPDisplayList(test_map_dl_Ground_mesh_layer_Opaque_tri_0),
	gsSPEndDisplayList(),
};

