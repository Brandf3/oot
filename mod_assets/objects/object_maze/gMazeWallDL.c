#include "ultra64.h"
#include "global.h"

Vtx gMazeWallDL_gMazeWallDL_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {-5000, 0, -1000}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-5000, 0, 1000}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-5000, 10000, 1000}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-5000, 10000, -1000}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {5000, 0, -1000}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {5000, 0, 1000}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {5000, 10000, 1000}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {5000, 10000, -1000}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx gMazeWallDL_gMazeWallDL_mesh_layer_Opaque_vtx_0[16] = {
	{{ {-5000, 0, 1000}, 0, {368, 1008}, {129, 0, 0, 255} }},
	{{ {-5000, 10000, 1000}, 0, {624, 1008}, {129, 0, 0, 255} }},
	{{ {-5000, 10000, -1000}, 0, {624, 752}, {129, 0, 0, 255} }},
	{{ {-5000, 0, -1000}, 0, {368, 752}, {129, 0, 0, 255} }},
	{{ {-5000, 0, -1000}, 0, {368, 752}, {0, 0, 129, 255} }},
	{{ {-5000, 10000, -1000}, 0, {624, 752}, {0, 0, 129, 255} }},
	{{ {5000, 10000, -1000}, 0, {624, 496}, {0, 0, 129, 255} }},
	{{ {5000, 0, -1000}, 0, {368, 496}, {0, 0, 129, 255} }},
	{{ {5000, 0, -1000}, 0, {368, 496}, {127, 0, 0, 255} }},
	{{ {5000, 10000, -1000}, 0, {624, 496}, {127, 0, 0, 255} }},
	{{ {5000, 10000, 1000}, 0, {624, 240}, {127, 0, 0, 255} }},
	{{ {5000, 0, 1000}, 0, {368, 240}, {127, 0, 0, 255} }},
	{{ {5000, 0, 1000}, 0, {368, 240}, {0, 0, 127, 255} }},
	{{ {5000, 10000, 1000}, 0, {624, 240}, {0, 0, 127, 255} }},
	{{ {-5000, 10000, 1000}, 0, {624, -16}, {0, 0, 127, 255} }},
	{{ {-5000, 0, 1000}, 0, {368, -16}, {0, 0, 127, 255} }},
};

Gfx gMazeWallDL_gMazeWallDL_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(gMazeWallDL_gMazeWallDL_mesh_layer_Opaque_vtx_0 + 0, 16, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSPEndDisplayList(),
};

Gfx mat_gMazeWallDL_f3dlite_material_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsSPEndDisplayList(),
};

Gfx gMazeWallDL[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(gMazeWallDL_gMazeWallDL_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_gMazeWallDL_f3dlite_material_layerOpaque),
	gsSPDisplayList(gMazeWallDL_gMazeWallDL_mesh_layer_Opaque_tri_0),
	gsSPEndDisplayList(),
};

