#include "ultra64.h"
#include "z64.h"
#include "macros.h"

SurfaceType gMazeWallDL_polygonTypes[] = {
	{ 0x00000000, 0x00000000 },
};

CollisionPoly gMazeWallDL_polygons[] = {
	{ 0x0000, 0x0000, 0x0001, 0x0002, COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0), 0xffce },
	{ 0x0000, 0x0000, 0x0002, 0x0003, COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0), 0xffce },
	{ 0x0000, 0x0003, 0x0002, 0x0004, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-4.3213365330529996e-08), COLPOLY_SNORMAL(-1.0), 0xfffe },
	{ 0x0000, 0x0003, 0x0004, 0x0005, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-4.3213365330529996e-08), COLPOLY_SNORMAL(-1.0), 0xfffe },
	{ 0x0000, 0x0005, 0x0004, 0x0006, COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0), 0xffce },
	{ 0x0000, 0x0005, 0x0006, 0x0007, COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0), 0xffce },
	{ 0x0000, 0x0007, 0x0006, 0x0001, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(4.3213365330529996e-08), COLPOLY_SNORMAL(1.0), 0xfffe },
	{ 0x0000, 0x0007, 0x0001, 0x0000, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(4.3213365330529996e-08), COLPOLY_SNORMAL(1.0), 0xfffe },
	{ 0x0000, 0x0003, 0x0005, 0x0007, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(4.371138828673793e-08), 0x0000 },
	{ 0x0000, 0x0003, 0x0007, 0x0000, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(4.371138828673793e-08), 0x0000 },
	{ 0x0000, 0x0004, 0x0002, 0x0001, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(0.0), 0xff9c },
	{ 0x0000, 0x0004, 0x0001, 0x0006, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(0.0), 0xff9c },
};

Vec3s gMazeWallDL_vertices[8] = {
	{ -5000, 0, 200 },
    { -5000, 10000, 200 },
    { -5000, 10000, -200 },
    { -5000, 0, -200 },
    { 5000, 10000, -200 },
    { 5000, 0, -200 },
    { 5000, 10000, 200 },
    { 5000, 0, 200 },
};

CollisionHeader gMazeWallDL_collisionHeader = {
	-5000, 0, -200,
	5000, 10000, 200,
	8,
	gMazeWallDL_vertices,
	12,
	gMazeWallDL_polygons,
	gMazeWallDL_polygonTypes,
	0,
	0,
	0
};

Vtx gMazeWallDL_gMazeWallDL_mesh_layer_Opaque_vtx_0[24] = {
	{{{-5000, 0, 200},0, {368, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-5000, 10000, 200},0, {624, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-5000, 10000, -200},0, {624, 752},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-5000, 0, -200},0, {368, 752},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-5000, 0, -200},0, {368, 752},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-5000, 10000, -200},0, {624, 752},{0x0, 0x0, 0x81, 0xFF}}},
	{{{5000, 10000, -200},0, {624, 496},{0x0, 0x0, 0x81, 0xFF}}},
	{{{5000, 0, -200},0, {368, 496},{0x0, 0x0, 0x81, 0xFF}}},
	{{{5000, 0, -200},0, {368, 496},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{5000, 10000, -200},0, {624, 496},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{5000, 10000, 200},0, {624, 240},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{5000, 0, 200},0, {368, 240},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{5000, 0, 200},0, {368, 240},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{5000, 10000, 200},0, {624, 240},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-5000, 10000, 200},0, {624, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-5000, 0, 200},0, {368, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-5000, 0, -200},0, {112, 496},{0x0, 0x81, 0x0, 0xFF}}},
	{{{5000, 0, -200},0, {368, 496},{0x0, 0x81, 0x0, 0xFF}}},
	{{{5000, 0, 200},0, {368, 240},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-5000, 0, 200},0, {112, 240},{0x0, 0x81, 0x0, 0xFF}}},
	{{{5000, 10000, -200},0, {624, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-5000, 10000, -200},0, {880, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-5000, 10000, 200},0, {880, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{5000, 10000, 200},0, {624, 240},{0x0, 0x7F, 0x0, 0xFF}}},
};

Gfx gMazeWallDL_gMazeWallDL_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(gMazeWallDL_gMazeWallDL_mesh_layer_Opaque_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(gMazeWallDL_gMazeWallDL_mesh_layer_Opaque_vtx_0 + 16, 8, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSPEndDisplayList(),
};

Gfx mat_gMazeWallDL_f3d_material_002_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
	gsSPClearGeometryMode(G_CULL_FRONT | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	//gsDPSetPrimColor(0, 0, 0, 0, 0, 255),
	gsSPEndDisplayList(),
};

Gfx gMazeWallDL[] = {
	gsSPDisplayList(mat_gMazeWallDL_f3d_material_002_layerOpaque),
	gsSPDisplayList(gMazeWallDL_gMazeWallDL_mesh_layer_Opaque_tri_0),
	gsSPEndDisplayList(),
};

