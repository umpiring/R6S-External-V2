#pragma once
#include "Game.hpp"
#include "Defines.hpp"
#include "globals.hpp"
#include <d3dx9core.h>
#include <bcrypt.h>
#include "imgui/imgui.h"
#include <D3D11.h>


ImFont* m_pFont;
LPDIRECT3DDEVICE9 d3ddev;
ID3DXLine* dx_Line;
ID3DXFont* dx_Font;
IDirect3DDevice9Ex* p_Device;
extern IDirect3DTexture9* ksk;
#define M_PI	3.14159265358979323846264338327950288419716939937510
int box;
std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}
void DrawCorneredBox(int X, int Y, int W, int H, const ImU32& color, int thickness)
{
	float lineW = (W / 3);
	float lineH = (H / 3);

	////black outlines
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);

	//corners
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
}
void DrawBox(float X, float Y, float W, float H, const ImU32 color)
{
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(X + 1, Y + 1), ImVec2(((X + W) - 1), ((Y + H) - 1)), ImGui::GetColorU32(color));
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(X, Y), ImVec2(X + W, Y + H), ImGui::GetColorU32(color));
}
void DrawStrokeText(int x, int y, const char* str)
{
	//ImFont a;
	std::string utf_8_1 = std::string(str);
	std::string utf_8_2 = string_To_UTF8(utf_8_1);

	//ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	//ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	//ImGui::GetOverlayDrawList()->AddText(ImVec2(x - 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	//ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(255, 255, 255, 255)), utf_8_2.c_str());
}

typedef struct
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
}RGBA;





void DrawImage(ImTextureID ptexture, float_t x, float_t y, float_t w, float_t h, ImColor color)
{
	ImGui::GetOverlayDrawList()->AddImage(ptexture, ImVec2(x, y), ImVec2(x + w, y + h), ImVec2(0, 0), ImVec2(1, 1), color);
}


void DrawFilledRect(float x, float y, float w, float h, D3DCOLOR color)
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, NULL, NULL);
}
void Line(ImVec2 pos, ImVec2 size, ImU32 color, float thickness)
{
	ImGui::GetWindowDrawList()->AddLine(pos, size, color, thickness);
}
void crosshair()
{
	float MidX = 1920 / 2;
	float MidY = 1080 / 2;

	Line({ MidX - 10, MidY }, { MidX - 0, MidY }, ImColor(255.f, 255.f, 255.f, 1.f), 1.6);
	Line({ MidX, MidY - 10 }, { MidX, MidY - 0 }, ImColor(255.f, 255.f, 255.f, 1.f), 1.6);
	Line({ MidX + 10, MidY }, { MidX + 0, MidY }, ImColor(255.f, 255.f, 255.f, 1.f), 1.6);
	Line({ MidX, MidY + 10 }, { MidX, MidY + 0 }, ImColor(255.f, 255.f, 255.f, 1.f), 1.6);
}
void FillArea(float x, float y, float width, float height, D3DCOLOR color)
{
	D3DXVECTOR2 vectorLine[2];
	dx_Line->SetWidth(width);

	vectorLine[0].x = x + width / 2;
	vectorLine[0].y = y;
	vectorLine[1].x = x + width / 2;
	vectorLine[1].y = y + height;

	dx_Line->Draw(vectorLine, 2, color);
}
void DrawString(int x, int y, DWORD color, LPD3DXFONT g_pFont, const char* fmt, ...)
{
	char buf[1024] = { 0 };
	va_list va_alist;
	RECT FontPos = { x, y, x + 120, y + 16 };
	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);
	g_pFont->DrawTextA(NULL, buf, -1, &FontPos, DT_NOCLIP, color);
}
void DrawCircle(int x, int y, int radius, const ImU32& color, int segments)
{
	ImGui::GetOverlayDrawList()->AddCircle(ImVec2(x, y), radius, ImGui::GetColorU32(color), segments);
}
void DrawFilledRectangle1(int x, int y, int w, int h, D3DCOLOR color)
{
	D3DRECT rect = { x, y, x + w, y + h };
	p_Device->Clear(1, &rect, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 0, 0);
}
// Hope this pissed you off lmaoo ^^^^

DWORD blackColor = D3DCOLOR_ARGB(255, 0, 0, 0);
DWORD RedColour = D3DCOLOR_ARGB(255, 0, 55, 255);
DWORD WhiteColor = D3DCOLOR_ARGB(255, 255, 255, 255);
DWORD healthBarColor = D3DCOLOR_ARGB(200, 000, 255, 000);
DWORD Name = D3DCOLOR_ARGB(255, 255, 255, 255);
ImColor BoxColour = ImColor(255, 255, 255, 255);

struct player_bones
{
	int head, neck, spine, pelvis;
	int left_shoulder, left_elbow, left_hand;
	int right_shoulder, right_elbow, right_hand;
	int left_thigh, left_knee, left_ankle, left_toe;
	int right_thigh, right_knee, right_ankle, right_toe;
};


const char* OperatorNamess[100][10]{};

player_bones player_bones_by_name(const char* c) {
	player_bones Ianna = {
	11, 6, 4, 2,
	7, 8, 9,
	13, 14, 15,
	26, 27, 28, 29,
	30, 31, 32, 33
	};
	player_bones Clash = {
		11, 6, 4, 2,
		7, 8, 9,
		13, 14, 15,
		20, 21, 22, 23,
		24, 25, 26, 27
	};
	player_bones Finka = {
		11, 6, 4, 2,
		7, 8, 9,
		13, 14, 15,
		20, 21, 22, 23,
		24, 25, 26, 27
	};
	player_bones Recruit = {
		11, 6, 4, 2,
		7, 8, 9,
		13, 14, 15,
		20, 21, 22, 23,
		24, 25, 26, 27
	};
	player_bones Aruni = {
		11, 6, 4, 2,
		7, 8, 9,
		13, 14, 15,
		20, 21, 22, 23,
		24, 25, 26, 27
	};
	player_bones Monty = {
		11, 6, 4, 2,
		7, 8, 9,
		13, 14, 15,
		20, 21, 22, 23,
		24, 25, 26, 27
	};
	player_bones Fuze = {
		11, 6, 4, 2,
		7, 8, 9,
		13, 14, 15,
		20, 21, 22, 23,
		24, 25, 26, 27
	};
	player_bones Blitz = {
		11, 6, 4, 2,
		7, 8, 9,
		13, 14, 15,
		20, 21, 22, 23,
		24, 25, 26, 27
	};
	player_bones Amaru = {
		11, 6, 4, 2,
		7, 8, 9,
		13, 14, 15,
		20, 21, 22, 23,
		24, 25, 26, 27
	};
	player_bones Default = {
		11, 6, 4, 2,
		7, 8, 9,
		13, 14, 15,
		19, 20, 21, 22,
		23, 24, 25, 26
	};

	if (c == "Ianna")
		return Ianna;
	else  if (c == "Finka")
		return Finka;
	else  if (c == "Montagne")
		return Monty;
	else  if (c == "Blitz")
		return Blitz;
	else  if (c == "Fuze")
		return Fuze;
	else  if (c == "Aruni")
		return Aruni;
	else  if (c == "Clash")
		return Clash;
	else  if (c == "Amaru")
		return Amaru;
	else  if (c == "Recruit")
		return Recruit;
	else
		return Default;
};

typedef struct ents
{
	uint64_t controller;
	uintptr_t pawn;
	uint32_t team;
	uint64_t replicationinfo;
	uint8_t CTU;
	uint8_t OP;
	char Name[16];
} ents, * ent_t;

enum BONES
{
	BONE_BOTTOM = 0,
	BONE_HEAD = 11,
	BONE_NECK = 10,
	BONE_CHEST = 4,
	BONE_SPINE = 20,

	BONE_LEFTSHOULDER = 13,
	BONE_RIGHTSHOULDER = 7,

	BONE_LEFTELBOWROLL = 14,
	BONE_RIGHTELBOWROLL = 8,

	BONE_LEFTHAND = 15,
	BONE_RIGHTHAND = 9,

	BONE_LEFTKNEEROLL = 25,
	BONE_RIGHTKNEEROLL = 21,

	BONE_LEFTFOOT = 26,
	BONE_RIGHTFOOT = 22
};


int AimbotTargeting[]{
	BONES::BONE_HEAD,
	BONES::BONE_NECK,
	BONES::BONE_CHEST,
	BONES::BONE_SPINE
};
ImColor NameTagColor = ImColor((int)40, (int)40, (int)40, 150);

// all of this is horribly done and can be cleaned up, this was meant for personal use not for anything else lol



namespace Visuals
{
	ents Entityss;
	std::vector<entity_t> entities = {};
	std::vector<uint64_t> actor = {};
	std::vector<std::string> opname = {};

	void Esp()
	{

		std::string Texttoshow = {};
		std::string Wowie = "Possible TM ";
		Texttoshow = Wowie + std::to_string((int)std::round(ImGui::GetIO().Framerate)) + " FPS";
		DrawStrokeText(2, 2, Texttoshow.c_str());

		for (int i = 1; i < entities.size(); i++)
		{
			auto Entities = entities[i];
			auto opnames = opname[i];
			auto actors = actor[i];


			if (!Entities.controller || !Entities.pawn) continue;

			vec3 rootPos = Game::GetPos(Entities.pawn);
			vec3 rootPosScreen;

			vec3 Head = Game::GetBonePosById(Entities.pawn, 6);
			vec3 HeadScreen;

			vec3 Foot = Game::GetBonePosById(Entities.pawn, 0);
			vec3 FootScreen;

			if (!Game::WorldToScreen(rootPos, rootPosScreen)) continue;
			if (!Game::WorldToScreen(Head, HeadScreen)) continue;
			if (!Game::WorldToScreen(Foot, FootScreen)) continue;

			float height = abs(HeadScreen.y - rootPosScreen.y);
			float width = height * 0.65;

			//std::string testName = Game::GetPlayerName(Entities.controller); // Profile Name
			//std::string opname = Game::OpName(Entities.controller); // Player Operator Name

			float Health = Game::Health(actors); // Entities Health
			float CurrentHealth = Health / 120.0f;
			if (CurrentHealth < 0 || CurrentHealth >= 1) CurrentHealth = 1;


			if (globals.enableEsp)
			{
				


				if (globals.cornerbox)
				{
					switch (globals.BoxType)
					{
					case corner:
					{
					
						DrawCorneredBox(HeadScreen.x - (width / 2) - 1, HeadScreen.y - (height / 5) - 1, width + 2, height + 12, BoxColour, 2);
						break;
					}
					case boxd:
					{
						DrawBox(HeadScreen.x - (width / 2) - 1, HeadScreen.y - (height / 5) - 1, width + 2, height + 12, BoxColour);
						break;
					}
					}
				}
				if (globals.drawFOV)
				{
					DrawCircle(1920 / 2, 1080 / 2, globals.aimFOV, BoxColour, 100);
				}
				if (globals.skeletons)
				{
					
					ImColor TEAMCOLORWOW = ImColor(255, 255, 255, 255);

					vec3 BONE_SPINEScreen;
					vec3 BONE_NECKScreen;
					vec3 BONE_PELVISScreen;
					vec3 BONE_LEFTSHOULDERScreen;
					vec3 BONE_RIGHTSHOULDERScreen;
					vec3 BONE_LEFTELBOWScreen;
					vec3 BONE_RIGHTELBOWScreen;
					vec3 BONE_LEFTHANDScreen;
					vec3 BONE_RIGHTHANDScreen;
					vec3 BONE_LEFTKNEEScreen;
					vec3 BONE_RIGHTKNEEScreen;
					vec3 BONE_LEFTTHIGHScreen;
					vec3 BONE_RIGHTTHIGHScreen;
					vec3 BONE_LEFTANKLEScreen;
					vec3 BONE_RIGHTANKLEScreen;

					Game::WorldToScreen(Game::GetBonePosById(Entities.pawn, player_bones_by_name(OperatorNamess[Entityss.CTU][Entityss.OP]).neck), BONE_NECKScreen);
					Game::WorldToScreen(Game::GetBonePosById(Entities.pawn, player_bones_by_name(OperatorNamess[Entityss.CTU][Entityss.OP]).spine), BONE_SPINEScreen);
					Game::WorldToScreen(Game::GetBonePosById(Entities.pawn, player_bones_by_name(OperatorNamess[Entityss.CTU][Entityss.OP]).pelvis), BONE_PELVISScreen);
					Game::WorldToScreen(Game::GetBonePosById(Entities.pawn, player_bones_by_name(OperatorNamess[Entityss.CTU][Entityss.OP]).left_shoulder), BONE_LEFTSHOULDERScreen);
					Game::WorldToScreen(Game::GetBonePosById(Entities.pawn, player_bones_by_name(OperatorNamess[Entityss.CTU][Entityss.OP]).right_shoulder), BONE_RIGHTSHOULDERScreen);
					Game::WorldToScreen(Game::GetBonePosById(Entities.pawn, player_bones_by_name(OperatorNamess[Entityss.CTU][Entityss.OP]).left_elbow), BONE_LEFTELBOWScreen);
					Game::WorldToScreen(Game::GetBonePosById(Entities.pawn, player_bones_by_name(OperatorNamess[Entityss.CTU][Entityss.OP]).right_elbow), BONE_RIGHTELBOWScreen);
					Game::WorldToScreen(Game::GetBonePosById(Entities.pawn, player_bones_by_name(OperatorNamess[Entityss.CTU][Entityss.OP]).left_hand), BONE_LEFTHANDScreen);
					Game::WorldToScreen(Game::GetBonePosById(Entities.pawn, player_bones_by_name(OperatorNamess[Entityss.CTU][Entityss.OP]).right_hand), BONE_RIGHTHANDScreen);
					Game::WorldToScreen(Game::GetBonePosById(Entities.pawn, player_bones_by_name(OperatorNamess[Entityss.CTU][Entityss.OP]).left_thigh), BONE_LEFTTHIGHScreen);
					Game::WorldToScreen(Game::GetBonePosById(Entities.pawn, player_bones_by_name(OperatorNamess[Entityss.CTU][Entityss.OP]).right_thigh), BONE_RIGHTTHIGHScreen);
					Game::WorldToScreen(Game::GetBonePosById(Entities.pawn, player_bones_by_name(OperatorNamess[Entityss.CTU][Entityss.OP]).left_knee), BONE_LEFTKNEEScreen);
					Game::WorldToScreen(Game::GetBonePosById(Entities.pawn, player_bones_by_name(OperatorNamess[Entityss.CTU][Entityss.OP]).right_knee), BONE_RIGHTKNEEScreen);
					Game::WorldToScreen(Game::GetBonePosById(Entities.pawn, player_bones_by_name(OperatorNamess[Entityss.CTU][Entityss.OP]).left_ankle), BONE_LEFTANKLEScreen);
					Game::WorldToScreen(Game::GetBonePosById(Entities.pawn, player_bones_by_name(OperatorNamess[Entityss.CTU][Entityss.OP]).right_ankle), BONE_RIGHTANKLEScreen);

					ImGui::GetOverlayDrawList()->AddLine(ImVec2(HeadScreen.x, HeadScreen.y), ImVec2(BONE_NECKScreen.x, BONE_NECKScreen.y), TEAMCOLORWOW, 0.5);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(BONE_NECKScreen.x, BONE_NECKScreen.y), ImVec2(BONE_SPINEScreen.x, BONE_SPINEScreen.y), TEAMCOLORWOW, 0.5);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(BONE_SPINEScreen.x, BONE_SPINEScreen.y), ImVec2(BONE_PELVISScreen.x, BONE_PELVISScreen.y), TEAMCOLORWOW, 0.5);

					ImGui::GetOverlayDrawList()->AddLine(ImVec2(BONE_NECKScreen.x, BONE_NECKScreen.y), ImVec2(BONE_LEFTSHOULDERScreen.x, BONE_LEFTSHOULDERScreen.y), TEAMCOLORWOW, 0.5);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(BONE_LEFTSHOULDERScreen.x, BONE_LEFTSHOULDERScreen.y), ImVec2(BONE_LEFTELBOWScreen.x, BONE_LEFTELBOWScreen.y), TEAMCOLORWOW, 0.5);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(BONE_LEFTELBOWScreen.x, BONE_LEFTELBOWScreen.y), ImVec2(BONE_LEFTHANDScreen.x, BONE_LEFTHANDScreen.y), TEAMCOLORWOW, 0.5);

					ImGui::GetOverlayDrawList()->AddLine(ImVec2(BONE_NECKScreen.x, BONE_NECKScreen.y), ImVec2(BONE_RIGHTSHOULDERScreen.x, BONE_RIGHTSHOULDERScreen.y), TEAMCOLORWOW, 0.5);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(BONE_RIGHTSHOULDERScreen.x, BONE_RIGHTSHOULDERScreen.y), ImVec2(BONE_RIGHTELBOWScreen.x, BONE_RIGHTELBOWScreen.y), TEAMCOLORWOW, 0.5);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(BONE_RIGHTELBOWScreen.x, BONE_RIGHTELBOWScreen.y), ImVec2(BONE_RIGHTHANDScreen.x, BONE_RIGHTHANDScreen.y), TEAMCOLORWOW, 0.5);


					ImGui::GetOverlayDrawList()->AddLine(ImVec2(BONE_PELVISScreen.x, BONE_PELVISScreen.y), ImVec2(BONE_LEFTTHIGHScreen.x, BONE_LEFTTHIGHScreen.y), TEAMCOLORWOW, 0.5);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(BONE_LEFTTHIGHScreen.x, BONE_LEFTTHIGHScreen.y), ImVec2(BONE_LEFTKNEEScreen.x, BONE_LEFTKNEEScreen.y), TEAMCOLORWOW, 0.5);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(BONE_LEFTKNEEScreen.x, BONE_LEFTKNEEScreen.y), ImVec2(BONE_LEFTANKLEScreen.x, BONE_LEFTANKLEScreen.y), TEAMCOLORWOW, 0.5);

					ImGui::GetOverlayDrawList()->AddLine(ImVec2(BONE_PELVISScreen.x, BONE_PELVISScreen.y), ImVec2(BONE_RIGHTTHIGHScreen.x, BONE_RIGHTTHIGHScreen.y), TEAMCOLORWOW, 0.5);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(BONE_RIGHTTHIGHScreen.x, BONE_RIGHTTHIGHScreen.y), ImVec2(BONE_RIGHTKNEEScreen.x, BONE_RIGHTKNEEScreen.y), TEAMCOLORWOW, 0.5);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(BONE_RIGHTKNEEScreen.x, BONE_RIGHTKNEEScreen.y), ImVec2(BONE_RIGHTANKLEScreen.x, BONE_RIGHTANKLEScreen.y), TEAMCOLORWOW, 0.5);
					//for (int BoneID = 1; BoneID < 30; BoneID++)
					//{
					//	vec3 Bone = Game::GetBoneLocationByIndex(Entities.pawn, BoneID);
					//	vec3 BoneScreen;
					//	if (Game::WorldToScreen(Bone, BoneScreen))
					//	DrawStrokeText(BoneScreen.x, BoneScreen.y, std::to_string(BoneID).c_str());
					//}
				}
				if (globals.filledbox)
				{
					DrawFilledRect(HeadScreen.x - (width / 2) - 1, HeadScreen.y - (height / 5) - 1, width + 2, height + 12, D3DCOLOR_ARGB(93, 0, 0, 0));

				}
				if (globals.drawLines)
				{
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(1920 / 2, 1080 / 2), ImVec2(HeadScreen.x, HeadScreen.y), BoxColour, 1.0);
				}
				if (globals.headCir)
				{
					DrawCircle(HeadScreen.x, HeadScreen.y, 3, BoxColour, 1000);
				}
				if (globals.PlayerInfo)
				{
					
					std::string Full = {};
					Full = std::to_string((int)std::round(FootScreen.z)) + "m  " + opnames.c_str();

					const ImVec2 text_dimension = ImGui::CalcTextSize(Full.c_str());
					const float text_width = text_dimension.x + 5.f;
					const float mid_width = HeadScreen.x - (text_width / 2);
					DrawFilledRect(mid_width + 2.f, HeadScreen.y - 25.f - 25.f, text_width + 10.f, text_dimension.y + 5.f, NameTagColor);
					DrawStrokeText(mid_width + 6.f, (HeadScreen.y - 25.f - 25.f) + 2.f, Full.c_str());
					DrawFilledRect(mid_width + 2.f, HeadScreen.y - 25.f - 25.f + (text_dimension.y + 5.f), text_width + 10.f, 3, RedColour);

					//DrawStrokeText(HeadScreen.x - (width / 2) - 1, HeadScreen.y - (height / 5) - 20, opnames.c_str());


					DrawFilledRect(HeadScreen.x - (width / 2) - 6 - 1, HeadScreen.y - (height / 5) - 1, 5, height + 10 + 2, blackColor);
					DrawFilledRect(HeadScreen.x - (width / 2) - 6, HeadScreen.y - (height / 5), 3, (height + 10) * CurrentHealth, healthBarColor);

				}
				if (globals.Image) {
					std::string Full = {};
					Full = std::to_string((int)std::round(FootScreen.z)) + "m  " + opnames.c_str();
					const ImVec2 text_dimension = ImGui::CalcTextSize(Full.c_str());

					const float text_width = text_dimension.x + 5.f;

					const float mid_width = HeadScreen.x - (text_width / 2);

					DrawImage(ksk, mid_width - 24.f, HeadScreen.y - 28.f - 25.f, 28.f, 28.f,  WhiteColor);
				}
				if (globals.healthbar)
				{
					std::string Full = {};
					Full = std::to_string((int)std::round(FootScreen.z)) + "m  " + opnames.c_str();

					const ImVec2 text_dimension = ImGui::CalcTextSize(Full.c_str());
					const float text_width = text_dimension.x + 5.f;
					const float mid_width = HeadScreen.x - (text_width / 2.5);
					DrawFilledRect(mid_width + 2.f, HeadScreen.y - 25.f - 25.f + (text_dimension.y + 5.f), (text_width + 10.f)* CurrentHealth, 3, healthBarColor);

				}

			}
		}
	}
}


namespace Aimbot
{
	inline auto move_to(float x, float y) -> void {
		float center_x = (ImGui::GetIO().DisplaySize.x / 2);
		float center_y = (ImGui::GetIO().DisplaySize.y / 2);

		float target_x = 0.f;
		float target_y = 0.f;

		if (x != 0.f)
		{
			if (x > center_x)
			{
				target_x = -(center_x - x);
				target_x /= globals.smooth;
				if (target_x + center_x > center_x * 2.f) target_x = 0.f;
			}

			if (x < center_x)
			{
				target_x = x - center_x;
				target_x /= globals.smooth;
				if (target_x + center_x < 0.f) target_x = 0.f;
			}
		}

		if (y != 0.f)
		{
			if (y > center_y)
			{
				target_y = -(center_y - y);
				target_y /= globals.smooth;
				if (target_y + center_y > center_y * 2.f) target_y = 0.f;
			}

			if (y < center_y)
			{
				target_y = y - center_y;
				target_y /= globals.smooth;
				if (target_y + center_y < 0.f) target_y = 0.f;
			}
		}

		mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(target_x), static_cast<DWORD>(target_y), 0, 0);
	}

	inline auto aimbot() -> void {

		if (globals.aimbot)
		{
			if (GetAsyncKeyState(VK_RBUTTON)) {
				auto target = globals.best_target;

				if (!target.controller || !target.pawn) return;

				vec3 Target = Game::GetBonePosById(target.pawn, AimbotTargeting[globals.AimTarget]);

				vec3 w2s_Target{};
				if (!Game::WorldToScreen(Target, w2s_Target)) return;

				if (Game::Health(target.pawn) == 0) return;

				move_to(w2s_Target.x, w2s_Target.y);
			}
		}
		
	}
}