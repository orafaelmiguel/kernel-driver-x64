#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "../Dependecies/json.h"
#include <Windows.h>
#include <optional>
#include <optional>
#include <string>
#include <iostream>
#include <windows.h>
using namespace std;
using json = nlohmann::json;

namespace Offset {


    struct GeneralOffsets
    {
        DWORD dwEntityList;
        DWORD dwGlobalVars;
        DWORD dwLocalPlayerController;
        DWORD dwLocalPlayerPawn;
        DWORD LocalPlayerPawn;
        DWORD dwPlantedC4;
        DWORD dwViewAngles;
        DWORD PlantedC4;
        DWORD InputSystem;
        DWORD Sensitivity;
        DWORD dwViewMatrix;
        DWORD dwWindowHeight;
        DWORD dwWindowWidth;
    } General;

    struct EntityOffsets {
        DWORD m_bPawnIsAlive;
        DWORD m_hPlayerPawn;
        DWORD m_iszPlayerName;
        DWORD m_flGravityScale;
    } Entity;

    struct PawnOffsets {
        DWORD m_pMovementServices;//
        DWORD m_pWeaponServices;//
        DWORD m_pBulletServices;//
        DWORD m_pCameraServices;//
        DWORD m_pViewModelServices;//
        DWORD m_pClippingWeapon;//
        DWORD m_hViewModel;
        DWORD m_nCrouchState;
        DWORD m_bIsScoped;
        DWORD m_bIsDefusing;
        DWORD m_totalHitsOnServer;
        DWORD m_vOldOrigin;
        DWORD m_ArmorValue;
        DWORD m_iMaxHealth;
        DWORD m_iHealth;
        DWORD m_pGameSceneNode;
        DWORD m_modelState;
        DWORD m_vecOrigin;
        DWORD m_hOwnerEntity;
        DWORD m_angEyeAngles;
        DWORD m_vecLastClipCameraPos;
        DWORD m_iShotsFired;
        DWORD m_flFlashMaxAlpha;
        DWORD m_flFlashDuration;
        DWORD m_aimPunchAngle;
        DWORD m_aimPunchCache;
        DWORD m_iIDEntIndex;
        DWORD m_iTeamNum;
        DWORD m_iDesiredFOV;
        DWORD m_iFOVStart;
        DWORD m_entitySpottedState;
        DWORD m_bSpottedByMask;
        DWORD m_vecAbsVelocity;
        DWORD m_bIsBuyMenuOpen;
    } Pawn;

    struct GlobalVarOffsets {
        DWORD RealTime;
        DWORD FrameCount;
        DWORD MaxClients;
        DWORD IntervalPerTick;
        DWORD CurrentTime;
        DWORD CurrentTime2;
        DWORD TickCount;
        DWORD IntervalPerTick2;
        DWORD CurrentNetchan;
        DWORD CurrentMap;
        DWORD CurrentMapName;
    } GlobalVar;

    struct PlayerControllerOffsets {
        DWORD m_hPawn;
        DWORD m_pObserverServices;
        DWORD m_hObserverTarget;
        DWORD m_hController;
        DWORD m_iPawnArmor;
        DWORD m_bPawnHasDefuser;
        DWORD m_bPawnHasHelmet;
    } PlayerController;

    struct EconEntityOffsets {
        DWORD m_AttributeManager;
        DWORD m_nFallbackPaintKit;
        DWORD m_nFallbackSeed;
        DWORD m_flFallbackWear;
        DWORD m_nFallbackStatTrak;
        DWORD m_szCustomName;
        DWORD m_iEntityQuality;
        DWORD m_iItemIDHigh;
    } EconEntity;

    struct WeaponBaseOffsets {
        DWORD WeaponDataPTR;
        DWORD szName;
        DWORD Clip1;
        DWORD m_iMaxClip1;
        DWORD m_flCycleTime;
        DWORD m_flPenetration;
        DWORD m_WeaponType;
        DWORD m_flInaccuracyMove;
        DWORD m_bInReload;
        DWORD WeaponSize;
        DWORD m_hActiveWeapon;
        DWORD m_Item;
        DWORD m_iItemDefinitionIndex;
        DWORD m_MeshGroupMask;
    } WeaponBase;

    struct C4Offsets {
        DWORD m_bBeingDefused;
        DWORD m_flDefuseCountDown;
        DWORD m_nBombSite;
    } C4;

    struct InGameMoneyServicesOffsets {
        DWORD m_pInGameMoneyServices;
        DWORD m_iAccount;
        DWORD m_iTotalCashSpent;
        DWORD m_iCashSpentThisRound;
    } InGameMoneyServices;

    struct SmokeGrenadeProjectileOffsets {
        DWORD m_nSmokeEffectTickBegin;
        DWORD m_bDidSmokeEffect;
        DWORD m_nRandomSeed;
        DWORD m_vSmokeColor;
        DWORD m_vSmokeDetonationPos;
        DWORD m_VoxelFrameData;
        DWORD m_bSmokeVolumeDataReceived;
        DWORD m_bSmokeEffectSpawned;
    } SmokeGrenadeProjectile;

    bool UpdateOffsets();
}