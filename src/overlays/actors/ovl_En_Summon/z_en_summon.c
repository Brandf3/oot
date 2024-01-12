/*
 * File: z_en_summon.c
 * Overlay: ovl_En_Summon
 * Description: Summon
 */

#include "z_en_summon.h"
#include "assets/objects/object_firefly/object_firefly.h"

#define FLAGS (ACTOR_FLAG_0 | ACTOR_FLAG_2 | ACTOR_FLAG_IGNORE_QUAKE | ACTOR_FLAG_14)

void EnSummon_Init(Actor* thisx, PlayState* play);
void EnSummon_Destroy(Actor* thisx, PlayState* play);
void EnSummon_Update(Actor* thisx, PlayState* play2);
void EnSummon_Draw(Actor* thisx, PlayState* play);

void EnSummon_DiveAttack(EnSummon* this, PlayState* play);
void EnSummon_SeekEnemy(EnSummon* this, PlayState* play);

ActorInit En_Summon_InitVars = {
    /**/ ACTOR_EN_SUMMON,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ OBJECT_FIREFLY,
    /**/ sizeof(EnSummon),
    /**/ EnSummon_Init,
    /**/ EnSummon_Destroy,
    /**/ EnSummon_Update,
    /**/ EnSummon_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000080, 0x00, 0x01 },
            { 0xFFCFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_HARD,
            BUMP_ON,
            OCELEM_ON,
        },
        { 1, { { 0, 1000, 0 }, 15 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_PLAYER,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit,
};

static CollisionCheckInfoInit sColChkInfoInit = { 1, 10, 10, 30 };

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 5, ICHAIN_CONTINUE),  ICHAIN_F32_DIV1000(gravity, -500, ICHAIN_CONTINUE),
    ICHAIN_F32(minVelocityY, -4, ICHAIN_CONTINUE),    ICHAIN_U8(targetMode, 2, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 4000, ICHAIN_STOP),
};

void EnSummon_Init(Actor* thisx, PlayState* play) {
    EnSummon* this = (EnSummon*)thisx;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 25.0f);
    SkelAnime_Init(play, &this->skelAnime, &gKeeseSkeleton, &gKeeseFlyAnim, this->jointTable, this->morphTable, 28);
    Collider_InitJntSph(play, &this->collider);
    Collider_SetJntSph(play, &this->collider, &this->actor, &sJntSphInit, this->colliderItems);

    this->actionFunc = EnSummon_SeekEnemy;
    this->actor.speed = 2.5f;
    this->collider.elements[0].info.toucher.effect = 0; // Nothing
    this->collider.elements[0].dim.worldSphere.radius = sJntSphInit.elements[0].dim.modelSphere.radius;
}

void EnSummon_Destroy(Actor* thisx, PlayState* play) {
    EnSummon* this = (EnSummon*)thisx;

    Collider_DestroyJntSph(play, &this->collider);
    Actor_Kill(&this->actor);
}

void EnSummon_SeekEnemy(EnSummon* this, PlayState* play) {
    Actor* findTorch;
    Actor* closestTorch;
    f32 torchDist;
    f32 currentMinDist;
    Vec3f flamePos;

    findTorch = play->actorCtx.actorLists[ACTORCAT_ENEMY].head;
    closestTorch = NULL;
    currentMinDist = 35000.0f;
    while (findTorch != NULL) {
        torchDist = Actor_WorldDistXYZToActor(&this->actor, findTorch);
        if (torchDist < currentMinDist) {
            currentMinDist = torchDist;
            closestTorch = findTorch;
        }
        findTorch = findTorch->next;
    }
    
    if (closestTorch != NULL) {
        flamePos.x = closestTorch->world.pos.x;
        flamePos.y = closestTorch->world.pos.y;
        flamePos.z = closestTorch->world.pos.z;
        Math_ScaledStepToS(&this->actor.shape.rot.y, Actor_WorldYawTowardActor(&this->actor, closestTorch),
                            0x300);
        Math_ScaledStepToS(&this->actor.shape.rot.x, Actor_WorldPitchTowardPoint(&this->actor, &flamePos) + 0x1554,
                            0x100); 
    } else {
        Actor_Kill(&this->actor);
    }
}

void EnSummon_Update(Actor* thisx, PlayState* play2) {
    EnSummon* this = (EnSummon*)thisx;
    PlayState* play = play2;

    if (this->collider.base.atFlags & AT_HIT) {
        this->collider.base.atFlags &= ~AT_HIT;
        Actor_PlaySfx(&this->actor, NA_SE_EN_FFLY_ATTACK);
        Actor_Kill(&this->actor);
    }
    
    this->actionFunc(this, play);

    //if (!(this->actor.flags & ACTOR_FLAG_15)) {
    this->actor.world.rot.x = 0x1554 - this->actor.shape.rot.x;
    Actor_MoveXYZ(&this->actor);
    //}

    Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, 10.0f, 15.0f,
                            UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_2);
    this->collider.elements[0].dim.worldSphere.center.x = this->actor.world.pos.x;
    this->collider.elements[0].dim.worldSphere.center.y = this->actor.world.pos.y + 10.0f;
    this->collider.elements[0].dim.worldSphere.center.z = this->actor.world.pos.z;

    //if (this->actionFunc == EnSummon_DiveAttack) {
    CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
    //}

    if (this->actor.colChkInfo.health != 0) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_FFLY_FLY);
        }
    }

    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    this->actor.focus.pos.x =
        (10.0f * Math_SinS(this->actor.shape.rot.x) * Math_SinS(this->actor.shape.rot.y)) + this->actor.world.pos.x;
    this->actor.focus.pos.y = (10.0f * Math_CosS(this->actor.shape.rot.x)) + this->actor.world.pos.y;
    this->actor.focus.pos.z =
        (10.0f * Math_SinS(this->actor.shape.rot.x) * Math_CosS(this->actor.shape.rot.y)) + this->actor.world.pos.z;
}

s32 EnSummon_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx,
                               Gfx** gfx) {
    EnSummon* this = (EnSummon*)thisx;

    if (limbIndex == 1) {
        pos->y += 2300.0f;
    }
    return false;
}

void EnSummon_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx, Gfx** gfx) {
    static Vec3f limbSrc = { 0.0f, 0.0f, 0.0f };
    Vec3f* limbDest;
    EnSummon* this = (EnSummon*)thisx;

    if (limbIndex == 27) {
        gSPDisplayList((*gfx)++, gKeeseEyesDL);
    }

    if ((limbIndex == 15) || (limbIndex == 21) || (limbIndex == 10)) {
        if (limbIndex == 15) {
            limbDest = &this->bodyPartsPos[0];
        } else if (limbIndex == 21) {
            limbDest = &this->bodyPartsPos[1];
        } else {
            limbDest = &this->bodyPartsPos[2];
        }

        Matrix_MultVec3f(&limbSrc, limbDest);
        limbDest->y -= 5.0f;
    }
}

void EnSummon_Draw(Actor* thisx, PlayState* play) {
    EnSummon* this = (EnSummon*)thisx;

    OPEN_DISPS(play->state.gfxCtx, "../z_en_summon.c", 1733);
    Gfx_SetupDL_25Opa(play->state.gfxCtx);

    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);

    POLY_OPA_DISP = SkelAnime_Draw(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   EnSummon_OverrideLimbDraw, EnSummon_PostLimbDraw, &this->actor, POLY_OPA_DISP);
    CLOSE_DISPS(play->state.gfxCtx, "../z_en_summon.c", 1763);
}
