#pragma once
#include "./imgui/imgui.h"
#include "./imgui/imgui_internal.h"
#include "./imgui/imgui_impl_win32.h"
#include <dwmapi.h>
#pragma comment(lib, "dwmapi")
#include <d3d9.h>
#include "./imgui/imgui_impl_dx9.h"
#pragma comment(lib, "d3d9")
#include "Game.hpp"
#include "Visuals.hpp"
#pragma warning(disable : 4838)
#pragma warning(disable : 4244)
#include "globals.hpp"
#include <d3dx9core.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <winerror.h>
#include "image.h"
IDirect3DTexture9* ksk;

IDirect3DTexture9* OperatorPictures;

HWND GameWnd = 0, MyWnd = 0;
RECT GameRect = {};

IDirect3D9Ex* p_Object = nullptr;
extern IDirect3DDevice9Ex* p_Device;
D3DPRESENT_PARAMETERS p_Params = { 0 };
extern LPDIRECT3DDEVICE9 d3ddev;
extern ID3DXLine* dx_Line;
extern ID3DXFont* dx_Font;
LPDIRECT3D9 d3d;
float ColorsVisuals[4] = { 127, 127, 127, 255 };
ImVec2 menuSize = ImVec2(750, 450);

template<typename T> void SetColor(T value, float R, float G, float B, float A) {
	value[0] = R; value[1] = G; value[2] = B; value[3] = A;
}
void Style()
{
	// Dark Theme
	ImGuiStyle* style = &ImGui::GetStyle();
	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
	//ImGui::PopStyleColor();

}
void Line(int newId)
{
	std::string id = ("imguipp_line_" + std::to_string(newId));
	ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
	{
		ImGui::BeginChild(id.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 1), false);
		ImGui::Separator();
		ImGui::EndChild();
	}
	ImGui::PopStyleColor();
}
void CenterTextEx(const char* text, float width, int lineId, bool separator)
{
	if (text == nullptr)
		return;

	ImGui::Spacing();
	ImGui::SameLine((width / 2) - (ImGui::CalcTextSize(text).x / 2));
	ImGui::Text(text);
	ImGui::Spacing();

	if (separator)
		Line(lineId);
}
inline void __fastcall set_window_to_target()
{
	while (true)
	{
		GameWnd = FindWindowA(("R6Game"), 0);
		if (GameWnd)
		{
			ZeroMemory(&GameRect, sizeof(GameRect));
			GetWindowRect(GameWnd, &GameRect);

			globals.width = GameRect.right - GameRect.left;
			globals.height = GameRect.bottom - GameRect.top;

			DWORD dwStyle = GetWindowLong(GameWnd, GWL_STYLE);
			if (dwStyle & WS_BORDER)
			{
				GameRect.top += 32;
				globals.height -= 39;
			}

			MoveWindow(MyWnd, GameRect.left - 2.f, GameRect.top - 2.f, globals.width + 2.f, globals.width + 2.f, true);
		}
		else exit(8);
	}
}
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);
inline auto __fastcall wnd_proc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) -> LRESULT
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
		return true;

	switch (Message)
	{
	case WM_DESTROY:
		if (p_Device != 0)
		{
			p_Device->EndScene();
			p_Device->Release();
		}

		if (p_Object != 0)
		{
			p_Object->Release();
		}

		PostQuitMessage(0);
		exit(4);
		break;
	case WM_SIZE:
		if (p_Device != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			p_Params.BackBufferWidth = LOWORD(lParam);
			p_Params.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = p_Device->Reset(&p_Params);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}
void Update()
{
	HWND activeWnd = GetForegroundWindow();
	if (activeWnd == MyWnd)
	{
		HWND hwndtest = GetWindow(activeWnd, GW_HWNDPREV);
		SetWindowPos(MyWnd, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}

	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		globals.menu = !globals.menu;

		if (globals.menu)
		{
			SetWindowLongA(MyWnd, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
		}
		else
		{
			// Add layer flag so we cannot click through to application
			SetWindowLongA(MyWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
		}
	}
}
inline auto __fastcall setup_window() -> void
{
	WNDCLASSEX wClass =
	{
		sizeof(WNDCLASSEX),
		0,
		wnd_proc,
		0,
		0,
		nullptr,
		LoadIcon(nullptr, IDI_APPLICATION),
		LoadCursor(nullptr, IDC_ARROW),
		nullptr,
		nullptr,
		("MonkHook"),
		LoadIcon(nullptr, IDI_APPLICATION)
	};

	if (!RegisterClassEx(&wClass))
		exit(1);

	//R6Game
	GameWnd = FindWindowA(("R6Game"), 0);

	if (GameWnd)
	{
		GetClientRect(GameWnd, &GameRect);
		POINT xy;
		ClientToScreen(GameWnd, &xy);
		GameRect.left = xy.x;
		GameRect.top = xy.y;

		globals.width = GameRect.right;
		globals.height = GameRect.bottom;
	}
	else exit(2);

	MyWnd = CreateWindowExA(0, wClass.lpszClassName, ("MonkHook"), WS_POPUP | WS_VISIBLE, GameRect.left - 2.f, GameRect.top - 2.f, globals.width + 2.f, globals.height + 2.f, 0, 0, 0, 0);


	MARGINS Margin = { GameRect.left - 2.f, GameRect.top - 2.f, globals.width + 2.f, globals.height + 2.f };
	DwmExtendFrameIntoClientArea(MyWnd, &Margin);

	SetWindowLongA(MyWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
	ShowWindow(MyWnd, SW_SHOW);
	UpdateWindow(MyWnd);
}
inline auto setup_directx(HWND hWnd) -> int
{
	ents Entityss;
	Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object);

	D3DPRESENT_PARAMETERS p_Params;

	ZeroMemory(&p_Params, sizeof(p_Params));
	p_Params.Windowed = TRUE;
	p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	p_Params.hDeviceWindow = hWnd;
	p_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	p_Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	p_Params.BackBufferWidth = globals.width + 2.f;
	p_Params.BackBufferHeight = globals.height + 2.f;
	p_Params.EnableAutoDepthStencil = TRUE;
	p_Params.AutoDepthStencilFormat = D3DFMT_D16;
	p_Params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	p_Params.MultiSampleQuality = DEFAULT_QUALITY;

	if (FAILED(p_Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_Params, 0, &p_Device)))
	{
		p_Object->Release();
		exit(4);
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\System Bold.ttf", 10);


	if (!dx_Line)
	{
		D3DXCreateLine(p_Device, &dx_Line);
	}

	// draw

	D3DXCreateFont(p_Device, 18, 0, FW_LIGHT, 1, false, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, "Arial", &dx_Font);

	if (FAILED(D3DXCreateTextureFromFileInMemory(p_Device, kskpng, sizeof(kskpng), &ksk)))
		return false;





	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(p_Device);
	Style();


	p_Object->Release();
}
enum
{
	TAB_VISUALS = 0,
	TAB_AIMBOT
};


void RenderMenu()
{
	ImGuiIO& io = ImGui::GetIO();
	if (globals.menu)
	{
		ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x / 2.f - menuSize.x / 2.f, io.DisplaySize.y / 2.f - menuSize.y / 2.f), ImGuiCond_Once);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 10.f);
		ImGui::Begin(("Possible Paste"), (bool*)0);
		{




			ImGui::Text("Aimbot");
			ImGui::Spacing();
			//ImGui::Checkbox("Aimbot", );
			ImGui::Checkbox("Aimbot", &globals.aimbot);
			ImGui::Checkbox("Draw FOV", &globals.drawFOV);

			if(globals.drawFOV)
			{
				ImGui::SliderInt("Aimbot FOV", &globals.aimFOV, 0, 360);
			}
			
			ImGui::Combo("Target", &globals.AimTarget, ("Head\0Neck\0Chest\0Spine\0"));
			ImGui::SliderInt("Smoothing", &globals.smooth, 0,10);



			ImGui::Spacing();
			ImGui::Text("Visuals");
			ImGui::Spacing();
			ImGui::Checkbox("Enable Visuals", &globals.enableEsp);
			if (globals.enableEsp)
			{
				ImGui::Checkbox("Player Box", &globals.cornerbox);
				if (globals.cornerbox)
				{
					ImGui::Combo(("##BoxType"), &globals.BoxType, ("Corner\0Box\0"));
				}
				ImGui::Checkbox("Player Filled Box", &globals.filledbox);
				ImGui::Checkbox("Player Health", &globals.healthbar);
				ImGui::Checkbox("Skeletons", &globals.skeletons);
				ImGui::Spacing();
				ImGui::Checkbox("Draw Image", &globals.Image);
				ImGui::Checkbox("Draw Lines", &globals.drawLines);
				ImGui::Checkbox("Draw Head Circles", &globals.headCir);
				ImGui::ColorEdit3("Box Colour", (float*)&BoxColour);
				ImGui::Checkbox("Player Info", &globals.PlayerInfo);
				ImGui::Checkbox("Team Check", &globals.teamcheck);
			}
			ImGui::Spacing();
			ImGui::Text("Misc");
			ImGui::Checkbox("No Spread", &globals.spread);
			if (globals.spread)
			{
				ImGui::SliderFloat("No Spread", &globals.Spread, 0.0f, 1.f);
			}
			ImGui::Spacing();
			ImGui::Checkbox("No Recoil", &globals.norecoil);
			if (globals.norecoil)
			{
				ImGui::SliderFloat("No Recoil", &globals.Recoil, 0.0001, 1.f);
			}
		
			// ImGui::Checkbox("Crosshair", &globals.crosshair);

		}
		ImGui::PopStyleVar(0);
		ImGui::End();
	}
}

void cache()
{
	auto currentweapon = Game::WeaponManager(globals.localActor);

	if (globals.norecoil)
	{
		driver::write<uint32_t>(driver::initial::connection, currentweapon + 0x1BC, (*(uint32_t*)&globals.Recoil) + 0x290B099F); //recoil 1 = 0.056
		driver::write<uint32_t>(driver::initial::connection, currentweapon + 0x1B8, (*(uint32_t*)&globals.Recoil) + 0xDEA00457); //recoil 2 = 0.056
	}
	if (globals.spread)
	{
		driver::write<uint32_t>(driver::initial::connection, currentweapon + 0x30, __ROR4__(__ROR4__(*(uint32_t*)(&globals.Spread), 8) + 1992768509, 1));
	}

}


inline auto __fastcall main_loop() -> WPARAM
{
	

	static RECT old_rc;
	static MSG Message;

	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT)
	{
		globals.gameManager = Game::Gamemanager();
		globals.cam = Game::Getcamera();
		globals.entityList = Game::GetEntityList(globals.gameManager);
		globals.entityCount = Game::GetEntityCount(globals.gameManager);
		globals.localPlayer = driver::read<uint64_t>(globals.entityList);
		globals.replicationinfo = Game::ReplicationInfo(globals.localPlayer);
		globals.localPawn = Game::Pawn(globals.localPlayer);
		globals.localActor = Game::Actor(globals.localPawn);


		std::vector<entity_t> tmp = { {} };
		std::vector<std::string> tmp2 = { {} };
		std::vector<uint64_t> tmp3 = { {} };


		for (int i = 1; i < globals.entityCount; i++)
		{

			//if (globals.entityCount > 50 || globals.entityCount < 0) break;
			//if (!globals.entityCount == 1) break;
			//if (!globals.localPlayer) break;
			//if (!globals.localPawn) break;

			uint64_t player = driver::read<uint64_t>(globals.entityList + (i * sizeof(uint64_t)));
			if (!player) continue;

			uint64_t pawn = Game::Pawn(player);
			if (!pawn) continue;
			if (!player || player == globals.localPlayer) continue; //check for fake entity 

			uint64_t actor = Game::Actor(pawn);

			if (globals.teamcheck)
			{
				globals.TeamID = Game::get_team_id(globals.replicationinfo);
				uint64_t replicationInfo = Game::ReplicationInfo(player);
				if (Game::get_team_id(replicationInfo) == globals.TeamID) continue;
				std::string operatorname = Game::GetOperatorName(replicationInfo);
				tmp2.push_back(operatorname);

			}

			entity_t entity{ {} };
			entity.controller = player;
			entity.pawn = pawn;
			tmp.push_back(entity);
			tmp3.push_back(actor);

			float best_dist = FLT_MAX;
			entity_t best_target = {};

			if (!entity.controller || !entity.pawn) continue;


			vec3 Head = Game::GetBonePosById(entity.pawn, /*AimbotTargeting[globals.AimTarget]*/11);

			vec3 w2s_head{};
			if (!Game::WorldToScreen(Head, w2s_head)) continue;

			float x = w2s_head.x - globals.width / 2.f;
			float y = w2s_head.y - globals.height / 2.f;
			float crosshair_dist = sqrtf((x * x) + (y * y));

			if (crosshair_dist <= FLT_MAX && crosshair_dist <= best_dist) {
				if (crosshair_dist > globals.aimFOV)
					continue;

				best_dist = crosshair_dist;
				globals.best_target = entity;
			}
			Aimbot::aimbot();

		}
		Visuals::entities = tmp;
		Visuals::opname = tmp2;
		Visuals::actor = tmp3;


		

		

		if (PeekMessageA(&Message, MyWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessageA(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();

		if (GetAsyncKeyState(VK_END) & 1)
			exit(8);

		if (hwnd_active == GameWnd)
		{
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(MyWnd, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(GameWnd, &rc);
		ClientToScreen(GameWnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = GameWnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(VK_LBUTTON)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
			io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{
			old_rc = rc;

			globals.width = rc.right;
			globals.height = rc.bottom;

			p_Params.BackBufferWidth = globals.width + 2.f;
			p_Params.BackBufferHeight = globals.height + 2.f;
			SetWindowPos(MyWnd, 0, xy.x, xy.y, globals.width + 2.f, globals.height + 2.f, SWP_NOREDRAW);
			p_Device->Reset(&p_Params);
		}
	

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		Style();

		Update();
		RenderMenu();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0)); // Invisible 
		ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
		ImGui::Begin(("##scene"), nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);



		std::thread(Visuals::Esp).join();
		//std::thread(Aimbot::aimbot).join();
		std::thread(cache).join();
		//std::thread(Visuals::Esp).join();

		ImGui::GetWindowDrawList()->PushClipRectFullScreen();
		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar(2);

		ImGui::EndFrame();

		p_Device->SetRenderState(D3DRS_ZENABLE, false);
		p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		p_Device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);

		p_Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
		if (p_Device->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			p_Device->EndScene();
		}

		if (p_Device->Present(0, 0, 0, 0) == D3DERR_DEVICELOST && p_Device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			p_Device->Reset(&p_Params);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
	}

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	if (p_Device != 0)
	{
		p_Device->EndScene();
		p_Device->Release();
	}

	if (p_Object != 0)
	{
		p_Object->Release();
	}

	DestroyWindow(MyWnd);
	return Message.wParam;
}
