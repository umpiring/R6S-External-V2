#pragma once
#include <cstdint>
#include <wtypes.h>
#include <vector>



typedef struct _entity_t
{
	std::uint64_t controller;
	std::uintptr_t pawn;
} entity_t, * p_entity_t;


enum bones
{
    head,
    chest
};

enum box
{
    corner,
    boxd
};

struct _globals
{
    HWND hWnd;
    uint64_t pID;
    uint64_t moduleBase;
    uint64_t gameManager;
    uint64_t gameProfile;
    uint64_t entityList;
    uint64_t replicationinfo;
    uint64_t TeamID;
    uint64_t roundManager;
    uint32_t gamestate;
    uint64_t Drones;
    uintptr_t Name;
    uint32_t entityCount;
    uintptr_t cam;
    uint64_t localPlayer;
    uint64_t localPawn;
    uint64_t localActor;
    float width = 1920.f;
    float height = 1080.f;
    bool teamcheck = true;
    int AimbotBone = bones::head;
    int BoxType = box::corner;
    bool norecoil = false;
    bool spread = false;
    float Recoil = 0.056f;
    float Spread = 0.0f;
    // menu 
    bool menu = false;
    bool enableEsp = true;
    bool cornerbox = false;
    bool skeletons = false;
    bool healthbar = false;
    bool Names = true;
    bool headcirlce = false;
    bool distance = false;
    bool snaplines = false;
    int aimFOV = 200.f;
    bool aimbot = false;
    bool filledbox = false;
    bool showfov = false;
    bool enablesmooth = true;
    int smooth = 1.0;
    int bones = bones::head;
    bool crosshair = false;
    // misc

    

    // extras

    bool drawFOV = false;
    bool headCir = false;
    bool drawLines = false;
    bool Image = false;

    bool OperatorNamesx = false;
    bool PlayerNames = false;
    bool PlayerInfo = false;
    // aimbot


    bool onshoot = true;
    int AimTarget = 11;
    INT aimkey = VK_RBUTTON;

    entity_t best_target;

};

extern _globals globals;

