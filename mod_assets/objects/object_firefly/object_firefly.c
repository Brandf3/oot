#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "object_firefly.h"
#include "assets/misc/link_animetion/link_animetion.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

s16 sKeeseFlyAnimFrameData[] = {
    0x0000, 0x4000, 0xD4A9, 0xEFB4, 0x2B57, 0x104C, 0x1BDA, 0xE426, 0x163C, 0xC000, 0x0000, 0xFFBD, 0xFF9C, 0xFFBB, 
    0x0000, 0x0045, 0x0064, 0x0043, 0x9C72, 0x9E5F, 0xA000, 0x9EAB, 0x9C72, 0x9A39, 0x98E4, 0x9A85, 0x9C72, 0x9E5F, 
    0xA000, 0x9EAB, 0x9C72, 0x9A39, 0x98E4, 0x9A85, 0x03AB, 0x139C, 0x238E, 0x171C, 0x0AAB, 0xFE39, 0xF1C7, 0xFAB9, 
    0x69CA, 0x6DC8, 0x71C7, 0x6F1C, 0x6C72, 0x69C7, 0x671C, 0x6873, 0x307C, 0x2BCC, 0x271C, 0x1AAB, 0x0E39, 0x01C7, 
    0xF555, 0x12E9, 0xC41B, 0xDE7F, 0xF8E4, 0xF000, 0xE71C, 0xDE39, 0xD555, 0xCCB8, 0xFC55, 0xEC64, 0xDC72, 0xE8E4, 
    0xF555, 0x01C7, 0x0E39, 0x0547, 0x69CA, 0x6DC8, 0x71C7, 0x6F1C, 0x6C72, 0x69C7, 0x671C, 0x6873, 0xCF84, 0xD434, 
    0xD8E4, 0xE555, 0xF1C7, 0xFE39, 0x0AAB, 0xED17, 0x3BE5, 0x2181, 0x071C, 0x1000, 0x18E4, 0x21C7, 0x2AAB, 0x3348, 
    0xA2FE, 0xA131, 0x9FBB, 0xA128, 0xA377, 0xA5BE, 0xA711, 0xA52A, 
};

JointIndex sKeeseFlyAnimJointIndices[] = {
    { 0x0000, 0x000A, 0x0000 },
    { 0x0000, 0x0001, 0x0000 },
    { 0x0000, 0x0000, 0x0002 },
    { 0x0000, 0x0000, 0x0000 },
    { 0x0000, 0x0003, 0x0004 },
    { 0x0000, 0x0000, 0x0012 },
    { 0x0000, 0x0000, 0x0000 },
    { 0x0000, 0x0005, 0x0004 },
    { 0x0000, 0x0000, 0x001A },
    { 0x0000, 0x0000, 0x0000 },
    { 0x0000, 0x0000, 0x0000 },
    { 0x0006, 0x0001, 0x0007 },
    { 0x0000, 0x0022, 0x002A },
    { 0x0000, 0x0032, 0x0000 },
    { 0x0000, 0x003A, 0x0008 },
    { 0x0000, 0x0000, 0x0000 },
    { 0x0000, 0x0000, 0x0000 },
    { 0x0000, 0x0000, 0x0000 },
    { 0x0007, 0x0009, 0x0007 },
    { 0x0000, 0x0042, 0x004A },
    { 0x0000, 0x0052, 0x0000 },
    { 0x0000, 0x005A, 0x0008 },
    { 0x0000, 0x0000, 0x0000 },
    { 0x0000, 0x0000, 0x0000 },
    { 0x0000, 0x0000, 0x0000 },
    { 0x0000, 0x0000, 0x0004 },
    { 0x0000, 0x0000, 0x0062 },
    { 0x0000, 0x0000, 0x0000 },
};

AnimationHeader gKeeseFlyAnim = { 
    { 8 }, sKeeseFlyAnimFrameData,
    sKeeseFlyAnimJointIndices, 10
};

u8 object_firefly_possiblePadding_00018C[] = {
    0x00, 0x00, 0x00, 0x00, 
};

u64 gKeeseEyeTex[] = {
#include "assets/objects/object_firefly/eye.rgba16.inc.c"
};

u64 gFireKeeseBodyTex[] = {
#include "assets/objects/object_firefly/fire_body.rgba16.inc.c"
};

u64 gFireKeeseEyeTex[] = {
#include "assets/objects/object_firefly/fire_eye.rgba16.inc.c"
};

u64 gFireKeeseEarTex[] = {
#include "assets/objects/object_firefly/fire_ear.rgba16.inc.c"
};

u64 gFireKeeseTalonTex[] = {
#include "assets/objects/object_firefly/fire_talon.rgba16.inc.c"
};

u64 gFireKeeseWingTex[] = {
#include "assets/objects/object_firefly/fire_wing.rgba16.inc.c"
};

u64 gKeeseBodyTex[] = {
#include "assets/objects/object_firefly/body.rgba16.inc.c"
};

u64 gKeeseTalonTex[] = {
#include "assets/objects/object_firefly/talon.rgba16.inc.c"
};

u64 gKeeseWingTex[] = {
#include "assets/objects/object_firefly/wing.rgba16.inc.c"
};

u64 gKeeseEarTex[] = {
#include "assets/objects/object_firefly/ear.rgba16.inc.c"
};

Vtx object_fireflyVtx_000890[] = {
#include "assets/objects/object_firefly/object_fireflyVtx_000890.vtx.inc"
};

Gfx gKeeseSkeletonLimbsLimb_001840DL_000D30[] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(gFireKeeseBodyTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadMultiBlock(gKeeseBodyTex, 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_MIRROR | G_TX_WRAP,
                       G_TX_NOMIRROR | G_TX_WRAP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, ENV_ALPHA, TEXEL0, 0, 0, 0, 1, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPClearGeometryMode(G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_CULL_BACK | G_FOG | G_LIGHTING),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsSPVertex(object_fireflyVtx_000890, 14, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 1, 0),
    gsSP2Triangles(3, 5, 6, 0, 3, 6, 4, 0),
    gsSP2Triangles(7, 2, 8, 0, 2, 7, 0, 0),
    gsSP2Triangles(6, 9, 4, 0, 10, 11, 12, 0),
    gsSP2Triangles(6, 5, 13, 0, 4, 2, 1, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gFireKeeseEyeTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR
                         | G_TX_WRAP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadMultiBlock(gKeeseBodyTex, 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                       G_TX_NOMIRROR | G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_fireflyVtx_000890[14], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gFireKeeseEarTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadMultiBlock(gKeeseEarTex, 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                       G_TX_NOMIRROR | G_TX_CLAMP, 4, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, ENV_ALPHA, TEXEL0, TEXEL1, TEXEL0, ENVIRONMENT, TEXEL0, COMBINED, 0, SHADE, 0,
                       TEXEL1, 0, PRIM_LOD_FRAC, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPVertex(&object_fireflyVtx_000890[20], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSPEndDisplayList(),
};

Gfx gKeeseSkeletonLimbsLimb_001774DL_000F40[] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(gFireKeeseBodyTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadMultiBlock(gKeeseBodyTex, 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_MIRROR | G_TX_WRAP,
                       G_TX_NOMIRROR | G_TX_WRAP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, ENV_ALPHA, TEXEL0, 0, 0, 0, 1, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPClearGeometryMode(G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_CULL_BACK | G_FOG | G_LIGHTING),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsSPVertex(&object_fireflyVtx_000890[26], 17, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(5, 6, 7, 0, 8, 2, 9, 0),
    gsSP2Triangles(10, 3, 7, 0, 11, 2, 8, 0),
    gsSP2Triangles(6, 12, 7, 0, 8, 6, 5, 0),
    gsSP2Triangles(5, 4, 8, 0, 13, 6, 8, 0),
    gsSP2Triangles(14, 15, 16, 0, 0, 2, 11, 0),
    gsSP2Triangles(4, 3, 10, 0, 7, 3, 5, 0),
    gsSPEndDisplayList(),
};

Gfx gKeeseSkeletonLimbsLimb_001768DL_001038[] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(gFireKeeseTalonTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadMultiBlock(gKeeseTalonTex, 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                       G_TX_NOMIRROR | G_TX_CLAMP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, ENV_ALPHA, TEXEL0, TEXEL1, TEXEL0, ENVIRONMENT, TEXEL0, COMBINED, 0, SHADE, 0,
                       TEXEL1, 0, PRIM_LOD_FRAC, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPClearGeometryMode(G_CULL_BACK | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_FOG | G_LIGHTING),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsSPVertex(&object_fireflyVtx_000890[43], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx gKeeseSkeletonLimbsLimb_001744DL_001100[] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(gFireKeeseTalonTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadMultiBlock(gKeeseTalonTex, 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                       G_TX_NOMIRROR | G_TX_CLAMP, 3, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, ENV_ALPHA, TEXEL0, TEXEL1, TEXEL0, ENVIRONMENT, TEXEL0, COMBINED, 0, SHADE, 0,
                       TEXEL1, 0, PRIM_LOD_FRAC, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPClearGeometryMode(G_CULL_BACK | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_FOG | G_LIGHTING),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsSPVertex(&object_fireflyVtx_000890[46], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx gKeeseSkeletonLimbsLimb_00181CDL_0011C8[] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(gFireKeeseWingTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 2, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadMultiBlock(gKeeseWingTex, 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                       G_TX_NOMIRROR | G_TX_CLAMP, 2, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, ENV_ALPHA, TEXEL0, 0, 0, 0, 1, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPClearGeometryMode(G_CULL_BACK | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_FOG | G_LIGHTING),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsSPVertex(&object_fireflyVtx_000890[50], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx gKeeseSkeletonLimbsLimb_001810DL_001290[] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(gFireKeeseWingTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 2, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadMultiBlock(gKeeseWingTex, 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                       G_TX_NOMIRROR | G_TX_CLAMP, 2, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, ENV_ALPHA, TEXEL0, 0, 0, 0, 1, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPClearGeometryMode(G_CULL_BACK | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_FOG | G_LIGHTING),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsSPVertex(&object_fireflyVtx_000890[53], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx gKeeseSkeletonLimbsLimb_001804DL_001358[] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(gFireKeeseWingTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 2, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadMultiBlock(gKeeseWingTex, 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                       G_TX_NOMIRROR | G_TX_CLAMP, 2, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, ENV_ALPHA, TEXEL0, 0, 0, 0, 1, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPClearGeometryMode(G_CULL_BACK | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_FOG | G_LIGHTING),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsSPVertex(&object_fireflyVtx_000890[56], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx gKeeseSkeletonLimbsLimb_0017B0DL_001420[] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(gFireKeeseWingTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 2, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadMultiBlock(gKeeseWingTex, 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                       G_TX_NOMIRROR | G_TX_CLAMP, 2, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, ENV_ALPHA, TEXEL0, 0, 0, 0, 1, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPClearGeometryMode(G_CULL_BACK | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_FOG | G_LIGHTING),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsSPVertex(&object_fireflyVtx_000890[59], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx gKeeseSkeletonLimbsLimb_0017BCDL_0014E8[] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(gFireKeeseWingTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 2, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadMultiBlock(gKeeseWingTex, 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                       G_TX_NOMIRROR | G_TX_CLAMP, 2, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, ENV_ALPHA, TEXEL0, 0, 0, 0, 1, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPClearGeometryMode(G_CULL_BACK | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_FOG | G_LIGHTING),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsSPVertex(&object_fireflyVtx_000890[62], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx gKeeseSkeletonLimbsLimb_0017C8DL_0015B0[] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(gFireKeeseWingTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 2, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadMultiBlock(gKeeseWingTex, 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                       G_TX_NOMIRROR | G_TX_CLAMP, 2, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, ENV_ALPHA, TEXEL0, 0, 0, 0, 1, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPClearGeometryMode(G_CULL_BACK | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_FOG | G_LIGHTING),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsSPVertex(&object_fireflyVtx_000890[65], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx gKeeseEyesDL[] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(gKeeseEyeTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR |
                         G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA_PRIM, G_CC_PASS2),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_XLU_DECAL2),
    gsSPClearGeometryMode(G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsSPVertex(&object_fireflyVtx_000890[68], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSPEndDisplayList(),
};

StandardLimb gKeeseSkeletonLimbsLimb_001708 = { 
    { 0, 0, 0 }, 0x01, LIMB_DONE,
    NULL
};

StandardLimb gKeeseSkeletonLimbsLimb_001714 = { 
    { 0, 0, 0 }, 0x02, LIMB_DONE,
    NULL
};

StandardLimb gKeeseSkeletonLimbsLimb_001720 = { 
    { 1707, 0, 0 }, 0x03, 0x09,
    NULL
};

StandardLimb gKeeseSkeletonLimbsLimb_00172C = { 
    { 236, 77, -83 }, 0x04, 0x06,
    NULL
};

StandardLimb gKeeseSkeletonLimbsLimb_001738 = { 
    { 0, 0, 0 }, 0x05, LIMB_DONE,
    NULL
};

StandardLimb gKeeseSkeletonLimbsLimb_001744 = { 
    { 0, 0, 0 }, LIMB_DONE, LIMB_DONE,
    gKeeseSkeletonLimbsLimb_001744DL_001100
};

StandardLimb gKeeseSkeletonLimbsLimb_001750 = { 
    { 236, 77, 83 }, 0x07, LIMB_DONE,
    NULL
};

StandardLimb gKeeseSkeletonLimbsLimb_00175C = { 
    { 0, 0, 0 }, 0x08, LIMB_DONE,
    NULL
};

StandardLimb gKeeseSkeletonLimbsLimb_001768 = { 
    { 0, 0, 0 }, LIMB_DONE, LIMB_DONE,
    gKeeseSkeletonLimbsLimb_001768DL_001038
};

StandardLimb gKeeseSkeletonLimbsLimb_001774 = { 
    { 0, 0, 0 }, LIMB_DONE, 0x0A,
    gKeeseSkeletonLimbsLimb_001774DL_000F40
};

StandardLimb gKeeseSkeletonLimbsLimb_001780 = { 
    { 455, 280, 10 }, 0x0B, 0x11,
    NULL
};

StandardLimb gKeeseSkeletonLimbsLimb_00178C = { 
    { 0, 0, 0 }, 0x0C, LIMB_DONE,
    NULL
};

StandardLimb gKeeseSkeletonLimbsLimb_001798 = { 
    { 1140, 0, 0 }, 0x0D, 0x10,
    NULL
};

StandardLimb gKeeseSkeletonLimbsLimb_0017A4 = { 
    { 860, 0, 0 }, 0x0E, 0x0F,
    NULL
};

StandardLimb gKeeseSkeletonLimbsLimb_0017B0 = { 
    { 0, 0, 0 }, LIMB_DONE, LIMB_DONE,
    gKeeseSkeletonLimbsLimb_0017B0DL_001420
};

StandardLimb gKeeseSkeletonLimbsLimb_0017BC = { 
    { 0, 0, 0 }, LIMB_DONE, LIMB_DONE,
    gKeeseSkeletonLimbsLimb_0017BCDL_0014E8
};

StandardLimb gKeeseSkeletonLimbsLimb_0017C8 = { 
    { 0, 0, 0 }, LIMB_DONE, LIMB_DONE,
    gKeeseSkeletonLimbsLimb_0017C8DL_0015B0
};

StandardLimb gKeeseSkeletonLimbsLimb_0017D4 = { 
    { 455, 280, -10 }, 0x12, 0x18,
    NULL
};

StandardLimb gKeeseSkeletonLimbsLimb_0017E0 = { 
    { 0, 0, 0 }, 0x13, LIMB_DONE,
    NULL
};

StandardLimb gKeeseSkeletonLimbsLimb_0017EC = { 
    { 1140, 0, 0 }, 0x14, 0x17,
    NULL
};

StandardLimb gKeeseSkeletonLimbsLimb_0017F8 = { 
    { 860, 0, 0 }, 0x15, 0x16,
    NULL
};

StandardLimb gKeeseSkeletonLimbsLimb_001804 = { 
    { 0, 0, 0 }, LIMB_DONE, LIMB_DONE,
    gKeeseSkeletonLimbsLimb_001804DL_001358
};

StandardLimb gKeeseSkeletonLimbsLimb_001810 = { 
    { 0, 0, 0 }, LIMB_DONE, LIMB_DONE,
    gKeeseSkeletonLimbsLimb_001810DL_001290
};

StandardLimb gKeeseSkeletonLimbsLimb_00181C = { 
    { 0, 0, 0 }, LIMB_DONE, LIMB_DONE,
    gKeeseSkeletonLimbsLimb_00181CDL_0011C8
};

StandardLimb gKeeseSkeletonLimbsLimb_001828 = { 
    { 0, 0, 0 }, 0x19, LIMB_DONE,
    NULL
};

StandardLimb gKeeseSkeletonLimbsLimb_001834 = { 
    { 0, 0, 0 }, 0x1A, LIMB_DONE,
    NULL
};

u64 gIngoHeadTLUT4[] = {
#include "assets/objects/object_in/head_tlut.rgba16.inc.c"
};

u64 gIngoTLUT24[] = {
#include "assets/objects/object_in/tlut2.rgba16.inc.c"
};

u64 gIngoHeadGradient2Tex3[] = {
#include "assets/objects/object_in/head_gradient_2.ci8.inc.c"
};

u64 gIngoEarTex3[] = {
#include "assets/objects/object_in/ear.ci8.inc.c"
};

u64 gIngoBrownTex3[] = {
#include "assets/objects/object_in/brown.ci8.inc.c"
};

u64 gIngoEyeOpenTex3[] = {
#include "assets/objects/object_in/eye_open.ci8.inc.c"
};

u64 gIngoEyebrowEdgeTex3[] = {
#include "assets/objects/object_in/eyebrow_edge.rgba16.inc.c"
};

u64 gIngoHairTex3[] = {
#include "assets/objects/object_in/hair.ci8.inc.c"
};

u64 gIngoSideburnsTex3[] = {
#include "assets/objects/object_in/sideburns.ci8.inc.c"
};

u64 gIngoBeardTex3[] = {
#include "assets/objects/object_in/beard.ci8.inc.c"
};

u64 gIngoEyeClosed2Tex3[] = {
#include "assets/objects/object_in/eye_closed_2.ci8.inc.c"
};

u64 gIngoHeadGradientTex3[] = {
#include "assets/objects/object_in/head_gradient.ci8.inc.c"
};

u64 gIngoEyeHalfTex3[] = {
#include "assets/objects/object_in/eye_half.ci8.inc.c"
};

u64 gIngoEyeClosedTex3[] = {
#include "assets/objects/object_in/eye_closed.ci8.inc.c"
};

Vtx object_inVtx_004FD03[] = {
#include "assets/objects/object_in/object_inVtx_004FD0.vtx.inc"
};

Gfx gIngoChildEraHeadDL4[] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(gIngoBeardTex3, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR |
                         G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadTLUT_pal256(gIngoTLUT24),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPClearGeometryMode(G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_CULL_BACK | G_FOG | G_LIGHTING),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsSPVertex(object_inVtx_004FD03, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoHeadGradient2Tex3, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadTLUT_pal256(gIngoHeadTLUT4),
    gsSPVertex(&object_inVtx_004FD03[3], 9, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 0, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 7, 5, 4, 0),
    gsSP1Triangle(3, 8, 1, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoHairTex3, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR |
                         G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadTLUT_pal256(gIngoTLUT24),
    gsSPVertex(&object_inVtx_004FD03[12], 16, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 11, 15, 9, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoHeadGradientTex3, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_inVtx_004FD03[28], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoHeadGradient2Tex3, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadTLUT_pal256(gIngoHeadTLUT4),
    gsSPVertex(&object_inVtx_004FD03[32], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoHairTex3, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR |
                         G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadTLUT_pal256(gIngoTLUT24),
    gsSPVertex(&object_inVtx_004FD03[35], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoSideburnsTex3, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_inVtx_004FD03[39], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 1, 3, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoHairTex3, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR |
                         G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_inVtx_004FD03[43], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoEarTex3, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR |
                         G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPVertex(&object_inVtx_004FD03[46], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoHeadGradient2Tex3, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadTLUT_pal256(gIngoHeadTLUT4),
    gsSPVertex(&object_inVtx_004FD03[49], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoHairTex3, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR |
                         G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadTLUT_pal256(gIngoTLUT24),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPVertex(&object_inVtx_004FD03[52], 9, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoHeadGradient2Tex3, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadTLUT_pal256(gIngoHeadTLUT4),
    gsSPVertex(&object_inVtx_004FD03[61], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoHeadGradientTex3, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadTLUT_pal256(gIngoTLUT24),
    gsSPVertex(&object_inVtx_004FD03[64], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoBeardTex3, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR |
                         G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_inVtx_004FD03[67], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoHairTex3, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR |
                         G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_inVtx_004FD03[70], 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 9, 4, 3, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoHeadGradientTex3, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_inVtx_004FD03[80], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoHeadGradient2Tex3, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadTLUT_pal256(gIngoHeadTLUT4),
    gsSPVertex(&object_inVtx_004FD03[83], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsSP2Triangles(4, 2, 1, 0, 5, 6, 7, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoHairTex3, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR |
                         G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadTLUT_pal256(gIngoTLUT24),
    gsSPVertex(&object_inVtx_004FD03[91], 15, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(0, 6, 1, 0, 7, 8, 9, 0),
    gsSP2Triangles(10, 8, 7, 0, 9, 11, 7, 0),
    gsSP1Triangle(12, 13, 14, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoSideburnsTex3, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_inVtx_004FD03[106], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoHeadGradient2Tex3, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadTLUT_pal256(gIngoHeadTLUT4),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPVertex(&object_inVtx_004FD03[110], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoEarTex3, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR |
                         G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadTLUT_pal256(gIngoTLUT24),
    gsSPVertex(&object_inVtx_004FD03[113], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoHeadGradientTex3, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPVertex(&object_inVtx_004FD03[116], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoHeadGradient2Tex3, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadTLUT_pal256(gIngoHeadTLUT4),
    gsSPVertex(&object_inVtx_004FD03[120], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoHairTex3, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR |
                         G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadTLUT_pal256(gIngoTLUT24),
    gsSPVertex(&object_inVtx_004FD03[123], 9, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 7, 8, 0),
    gsSP1Triangle(4, 6, 7, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(gIngoBeardTex3, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR |
                         G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_inVtx_004FD03[132], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(0x08000000, G_IM_FMT_CI, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR |
                         G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadTLUT_pal256(gIngoHeadTLUT4),
    gsSPVertex(&object_inVtx_004FD03[136], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsSP2Triangles(4, 3, 2, 0, 2, 5, 4, 0),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(0x09000000, G_IM_FMT_CI, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR |
                         G_TX_CLAMP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_inVtx_004FD03[142], 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsSP2Triangles(4, 5, 6, 0, 2, 7, 5, 0),
    gsSP2Triangles(1, 0, 8, 0, 3, 5, 4, 0),
    gsSP2Triangles(6, 5, 7, 0, 4, 0, 3, 0),
    gsSP2Triangles(9, 1, 8, 0, 9, 8, 6, 0),
    gsSP2Triangles(9, 6, 7, 0, 8, 0, 4, 0),
    gsSP2Triangles(4, 6, 8, 0, 5, 3, 2, 0),
    gsSPEndDisplayList(),
};

StandardLimb gKeeseSkeletonLimbsLimb_001840 = { 
    { 0, 0, 0 }, LIMB_DONE, LIMB_DONE,
    gIngoChildEraHeadDL4
};

void* gKeeseSkeletonLimbs[] = {
    &gKeeseSkeletonLimbsLimb_001708,
    &gKeeseSkeletonLimbsLimb_001714,
    &gKeeseSkeletonLimbsLimb_001720,
    &gKeeseSkeletonLimbsLimb_00172C,
    &gKeeseSkeletonLimbsLimb_001738,
    &gKeeseSkeletonLimbsLimb_001744,
    &gKeeseSkeletonLimbsLimb_001750,
    &gKeeseSkeletonLimbsLimb_00175C,
    &gKeeseSkeletonLimbsLimb_001768,
    &gKeeseSkeletonLimbsLimb_001774,
    &gKeeseSkeletonLimbsLimb_001780,
    &gKeeseSkeletonLimbsLimb_00178C,
    &gKeeseSkeletonLimbsLimb_001798,
    &gKeeseSkeletonLimbsLimb_0017A4,
    &gKeeseSkeletonLimbsLimb_0017B0,
    &gKeeseSkeletonLimbsLimb_0017BC,
    &gKeeseSkeletonLimbsLimb_0017C8,
    &gKeeseSkeletonLimbsLimb_0017D4,
    &gKeeseSkeletonLimbsLimb_0017E0,
    &gKeeseSkeletonLimbsLimb_0017EC,
    &gKeeseSkeletonLimbsLimb_0017F8,
    &gKeeseSkeletonLimbsLimb_001804,
    &gKeeseSkeletonLimbsLimb_001810,
    &gKeeseSkeletonLimbsLimb_00181C,
    &gKeeseSkeletonLimbsLimb_001828,
    &gKeeseSkeletonLimbsLimb_001834,
    &gKeeseSkeletonLimbsLimb_001840,
};

SkeletonHeader gKeeseSkeleton = { 
    gKeeseSkeletonLimbs, ARRAY_COUNT(gKeeseSkeletonLimbs)
};

