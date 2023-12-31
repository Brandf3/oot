#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "reverse_test_scene.h"
#include "segment_symbols.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"
#include "variables.h"

/**
 * Header Child Day (Default)
*/
SceneCmd reverse_test_scene_header00[] = {
    SCENE_CMD_SOUND_SETTINGS(0x00, 0x13, 0x02),
    SCENE_CMD_ROOM_LIST(1, reverse_test_scene_roomList),
    SCENE_CMD_MISC_SETTINGS(0x00, 0x00),
    SCENE_CMD_COL_HEADER(&reverse_test_collisionHeader),
    SCENE_CMD_SPECIAL_FILES(0x00, OBJECT_GAMEPLAY_DANGEON_KEEP),
    SCENE_CMD_SKYBOX_SETTINGS(0x00, 0x00, LIGHT_MODE_TIME),
    SCENE_CMD_ENTRANCE_LIST(reverse_test_scene_header00_entranceList),
    SCENE_CMD_SPAWN_LIST(1, reverse_test_scene_header00_playerEntryList),
    SCENE_CMD_ENV_LIGHT_SETTINGS(4, reverse_test_scene_header00_lightSettings),
    SCENE_CMD_END(),
};

RomFile reverse_test_scene_roomList[] = {
    { (u32)_reverse_test_room_0SegmentRomStart, (u32)_reverse_test_room_0SegmentRomEnd },
};

ActorEntry reverse_test_scene_header00_playerEntryList[] = {
    {
        /* Actor ID   */ ACTOR_PLAYER,
        /* Position   */ { 0, 0, 0 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x0FFF
    },
};

Spawn reverse_test_scene_header00_entranceList[] = {
    // { Spawn Actor List Index, Room Index }
    { 0, 0 },
};

EnvLightSettings reverse_test_scene_header00_lightSettings[4] = {
    // Dawn Lighting
    {
        {    70,    45,    57 },   // Ambient Color
        {    73,    73,    73 },   // Diffuse0 Direction
        {   180,   154,   138 },   // Diffuse0 Color
        {   -73,   -73,   -73 },   // Diffuse1 Direction
        {    20,    20,    60 },   // Diffuse1 Color
        {   140,   120,   100 },   // Fog Color
        ((1 << 10) | 993),         // Blend Rate & Fog Near
        12800,                     // Fog Far
    },
    // Day Lighting
    {
        {   105,    90,    90 },   // Ambient Color
        {    73,    73,    73 },   // Diffuse0 Direction
        {   255,   255,   240 },   // Diffuse0 Color
        {   -73,   -73,   -73 },   // Diffuse1 Direction
        {    50,    50,    90 },   // Diffuse1 Color
        {   100,   100,   120 },   // Fog Color
        ((1 << 10) | 996),         // Blend Rate & Fog Near
        12800,                     // Fog Far
    },
    // Dusk Lighting
    {
        {   120,    90,     0 },   // Ambient Color
        {    73,    73,    73 },   // Diffuse0 Direction
        {   250,   135,    50 },   // Diffuse0 Color
        {   -73,   -73,   -73 },   // Diffuse1 Direction
        {    30,    30,    60 },   // Diffuse1 Color
        {   120,    70,    50 },   // Fog Color
        ((1 << 10) | 995),         // Blend Rate & Fog Near
        12800,                     // Fog Far
    },
    // Night Lighting
    {
        {    40,    70,   100 },   // Ambient Color
        {    73,    73,    73 },   // Diffuse0 Direction
        {    20,    20,    35 },   // Diffuse0 Color
        {   -73,   -73,   -73 },   // Diffuse1 Direction
        {    50,    50,   100 },   // Diffuse1 Color
        {     0,     0,    30 },   // Fog Color
        ((1 << 10) | 992),         // Blend Rate & Fog Near
        12800,                     // Fog Far
    },
};

Vec3s reverse_test_camPosData[3] = {
	{ 0, 0, 0 },
	{ 8291, 44886, 65245 },
	{ 3960, -1, -1 },
};

BgCamInfo reverse_test_camData[1] = {
	{ CAM_SET_NORMAL0, 3, &reverse_test_camPosData[0] },
};

SurfaceType reverse_test_polygonTypes[] = {
	{ 0x00000000, 0x00000000 },
};

CollisionPoly reverse_test_polygons[] = {
	{ 0x0000, 0x0000, 0x0001, 0x0002, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(7.549790126404332e-08), 0x0000 },
	{ 0x0000, 0x0000, 0x0002, 0x0003, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(7.549790126404332e-08), 0x0000 },
	{ 0x0000, 0x0000, 0x0004, 0x0005, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(7.549790126404332e-08), COLPOLY_SNORMAL(-1.0), 0x036b },
	{ 0x0000, 0x0000, 0x0005, 0x0001, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(7.549790126404332e-08), COLPOLY_SNORMAL(-1.0), 0x036b },
	{ 0x0000, 0x0001, 0x0005, 0x0006, COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0), 0x02bc },
	{ 0x0000, 0x0001, 0x0006, 0x0002, COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0), 0x02bc },
	{ 0x0000, 0x0003, 0x0007, 0x0004, COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0), 0x02bc },
	{ 0x0000, 0x0003, 0x0004, 0x0000, COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0), 0x02bc },
	{ 0x0000, 0x0002, 0x0006, 0x0007, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-7.549790126404332e-08), COLPOLY_SNORMAL(1.0), 0x036b },
	{ 0x0000, 0x0002, 0x0007, 0x0003, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-7.549790126404332e-08), COLPOLY_SNORMAL(1.0), 0x036b },
	{ 0x0000, 0x0007, 0x0006, 0x0005, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(-7.549790126404332e-08), 0x0455 },
	{ 0x0000, 0x0007, 0x0005, 0x0004, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(-7.549790126404332e-08), 0x0455 },
	{ 0x0000, 0x0001, 0x0000, 0x0003, COLPOLY_SNORMAL(8.74227694680485e-08), COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(-7.549790126404332e-08), 0x0000 },
	{ 0x0000, 0x0001, 0x0003, 0x0002, COLPOLY_SNORMAL(8.74227694680485e-08), COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(-7.549790126404332e-08), 0x0000 },
	{ 0x0000, 0x0008, 0x0009, 0x0001, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(7.549790126404332e-08), COLPOLY_SNORMAL(-1.0), 0x036b },
	{ 0x0000, 0x0009, 0x0000, 0x0001, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(7.549790126404332e-08), COLPOLY_SNORMAL(-1.0), 0x036b },
	{ 0x0000, 0x0009, 0x000a, 0x0000, COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(6.881553815674124e-08), COLPOLY_SNORMAL(5.195428624398283e-15), 0x02bc },
	{ 0x0000, 0x000a, 0x0003, 0x0000, COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(6.881553815674124e-08), COLPOLY_SNORMAL(5.195428624398283e-15), 0x02bc },
	{ 0x0000, 0x000b, 0x0008, 0x0002, COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(-6.881553815674124e-08), COLPOLY_SNORMAL(-5.195428624398283e-15), 0x02bc },
	{ 0x0000, 0x0008, 0x0001, 0x0002, COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(-6.881553815674124e-08), COLPOLY_SNORMAL(-5.195428624398283e-15), 0x02bc },
	{ 0x0000, 0x000a, 0x000b, 0x0003, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-7.549790126404332e-08), COLPOLY_SNORMAL(1.0), 0x036b },
	{ 0x0000, 0x000b, 0x0002, 0x0003, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-7.549790126404332e-08), COLPOLY_SNORMAL(1.0), 0x036b },
	{ 0x0000, 0x000b, 0x000a, 0x0009, COLPOLY_SNORMAL(-1.089913510554652e-07), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(7.549790126404332e-08), 0x0455 },
	{ 0x0000, 0x000b, 0x0009, 0x0008, COLPOLY_SNORMAL(-1.089913510554652e-07), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(7.549790126404332e-08), 0x0455 },
};

Vec3s reverse_test_vertices[12] = {
	{ -700, 0, 875 },
	{ 700, 0, 875 },
	{ 700, 0, -875 },
	{ -700, 0, -875 },
	{ -700, 1109, 875 },
	{ 700, 1109, 875 },
	{ 700, 1109, -875 },
	{ -700, 1109, -875 },
	{ 700, -1109, 875 },
	{ -700, -1109, 875 },
	{ -700, -1109, -875 },
	{ 700, -1109, -875 },
};

CollisionHeader reverse_test_collisionHeader = {
	-700,
	-1109,
	-875,
	700,
	1109,
	875,
	12,
	reverse_test_vertices,
	24,
	reverse_test_polygons,
	reverse_test_polygonTypes,
	reverse_test_camData,
	0,
	0
};

