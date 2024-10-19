#ifndef Z_EN_RD_H
#define Z_EN_RD_H

#include "ultra64.h"
#include "global.h"

struct EnRd;

typedef void (*EnRdActionFunc)(struct EnRd*, PlayState*);

#define REDEAD_GET_RDFLAGS(thisx) PARAMS_GET_S((thisx)->params, 8, 8)

typedef enum RedeadGibdoLimb {
    /*  0 */ REDEAD_GIBDO_LIMB_NONE,
    /*  1 */ REDEAD_GIBDO_LIMB_ROOT,
    /*  2 */ REDEAD_GIBDO_LIMB_LEFT_LEG_ROOT,
    /*  3 */ REDEAD_GIBDO_LIMB_LEFT_THIGH,
    /*  4 */ REDEAD_GIBDO_LIMB_LEFT_SHIN,
    /*  5 */ REDEAD_GIBDO_LIMB_LEFT_FOOT_ROOT,
    /*  6 */ REDEAD_GIBDO_LIMB_LEFT_FOOT,
    /*  7 */ REDEAD_GIBDO_LIMB_RIGHT_LEG_ROOT,
    /*  8 */ REDEAD_GIBDO_LIMB_RIGHT_THIGH,
    /*  9 */ REDEAD_GIBDO_LIMB_RIGHT_SHIN,
    /* 10 */ REDEAD_GIBDO_LIMB_RIGHT_FOOT_ROOT,
    /* 11 */ REDEAD_GIBDO_LIMB_RIGHT_FOOT,
    /* 12 */ REDEAD_GIBDO_LIMB_UPPER_BODY_ROOT,
    /* 13 */ REDEAD_GIBDO_LIMB_TORSO_ROOT,
    /* 14 */ REDEAD_GIBDO_LIMB_TORSO,
    /* 15 */ REDEAD_GIBDO_LIMB_LEFT_ARM_ROOT,
    /* 16 */ REDEAD_GIBDO_LIMB_LEFT_UPPER_ARM,
    /* 17 */ REDEAD_GIBDO_LIMB_LEFT_FOREARM,
    /* 18 */ REDEAD_GIBDO_LIMB_LEFT_HAND,
    /* 19 */ REDEAD_GIBDO_LIMB_RIGHT_ARM_ROOT,
    /* 20 */ REDEAD_GIBDO_LIMB_RIGHT_UPPER_ARM,
    /* 21 */ REDEAD_GIBDO_LIMB_RIGHT_FOREARM,
    /* 22 */ REDEAD_GIBDO_LIMB_RIGHT_HAND,
    /* 23 */ REDEAD_GIBDO_LIMB_HEAD_ROOT,
    /* 24 */ REDEAD_GIBDO_LIMB_HEAD,
    /* 25 */ REDEAD_GIBDO_LIMB_PELVIS,
    /* 26 */ REDEAD_GIBDO_LIMB_MAX
} RedeadGibdoLimb;

typedef enum EnRdType {
    /* -3 */ REDEAD_TYPE_GIBDO_RISING_OUT_OF_COFFIN = -3,
    /* -2 */ REDEAD_TYPE_GIBDO,
    /* -1 */ REDEAD_TYPE_DOES_NOT_MOURN,
    /*  0 */ REDEAD_TYPE_DOES_NOT_MOURN_IF_WALKING,
    /*  1 */ REDEAD_TYPE_REGULAR,
    /*  2 */ REDEAD_TYPE_CRYING,
    /*  3 */ REDEAD_TYPE_INVISIBLE
} EnRdType;

typedef enum {
    /* 0x00 */ INGO_LIMB_NONE,
    /* 0x01 */ INGO_LIMB_ROOT,
    /* 0x02 */ INGO_LEFT_THIGH_LIMB,
    /* 0x03 */ INGO_LEFT_LEG_LIMB,
    /* 0x04 */ INGO_LEFT_FOOT_LIMB,
    /* 0x05 */ INGO_RIGHT_THIGH_LIMB,
    /* 0x06 */ INGO_RIGHT_LEG_LIMB,
    /* 0x07 */ INGO_RIGHT_FOOT_LIMB,
    /* 0x08 */ INGO_TORSO_LIMB,
    /* 0x09 */ INGO_CHEST_LIMB,
    /* 0x0A */ INGO_LEFT_SHOULDER_LIMB,
    /* 0x0B */ INGO_LEFT_ARM_LIMB,
    /* 0x0C */ INGO_LEFT_HAND_LIMB,
    /* 0x0D */ INGO_RIGHT_SHOULDER_LIMB,
    /* 0x0E */ INGO_RIGHT_ARM_LIMB,
    /* 0x0F */ INGO_RIGHT_HAND_LIMB,
    /* 0x10 */ INGO_HEAD_LIMB,
    /* 0x11 */ INGO_LEFT_EYEBROW_LIMB,
    /* 0x12 */ INGO_RIGHTEYEBROW_LIMB,
    /* 0x13 */ INGO_MUSTACHE_LIMB,
    /* 0x14 */ INGO_LIMB_MAX
} IngoLimb;

typedef struct EnRd {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ Vec3s firePos[10];
    /* 0x0188 */ SkelAnime skelAnime;
    /* 0x01CC */ Vec3s jointTable[INGO_LIMB_MAX];
    /* 0x0268 */ Vec3s morphTable[INGO_LIMB_MAX];
    /* 0x0304 */ u8 grabState;
    /* 0x0305 */ u8 isMourning;
    /* 0x0306 */ u8 playerStunWaitTimer; // Cannot stun the player if this is non-zero
    /* 0x0307 */ u8 grabWaitTimer; // Cannot grab the player if this is non-zero
    /* 0x0308 */ EnRdActionFunc actionFunc;
    /* 0x030C */ s16 timer;
    /* 0x030E */ s16 headYRotation;
    /* 0x0310 */ s16 upperBodyYRotation;
    /* 0x0312 */ s16 rdFlags;
    /* 0x0314 */ s16 alpha;
    /* 0x0316 */ s16 sunsSongStunTimer;
    /* 0x0318 */ u8 stunnedBySunsSong;
    /* 0x0319 */ u8 grabDamageTimer;
    /* 0x031A */ u8 fireTimer;
    /* 0x031B */ u8 action;
    /* 0x031C */ u8 damageEffect;
    /* 0x031D */ u8 unk_31D; // related to player->unk_845
    /* 0x0320 */ ColliderCylinder collider;
    Vec3s unk_330[INGO_LIMB_MAX];
} EnRd; // size = 0x036C

#endif
