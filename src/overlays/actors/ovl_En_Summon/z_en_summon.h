#ifndef Z_EN_SUMMON_H
#define Z_EN_SUMMON_H

#include "ultra64.h"
#include "global.h"

struct EnSummon;

typedef void (*EnSummonActionFunc)(struct EnSummon*, PlayState*);

typedef struct EnSummon {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ Vec3f bodyPartsPos[3];
    /* 0x0170 */ SkelAnime skelAnime;
    /* 0x01B4 */ EnSummonActionFunc actionFunc;
    /* 0x01BA */ s16 timer;
    /* 0x01BC */ s16 targetPitch;
    /* 0x01BE */ Vec3s jointTable[28];
    /* 0x0266 */ Vec3s morphTable[28];
    /* 0x0310 */ f32 maxAltitude;
    /* 0x0314 */ ColliderJntSph collider;
    /* 0x0344 */ ColliderJntSphElement colliderItems[1];
} EnSummon; // size = 0x0374

#endif
