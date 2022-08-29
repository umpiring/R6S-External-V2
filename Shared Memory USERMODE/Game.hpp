#pragma once
#include "Defines.hpp"
#include "Vector.hpp"
#include <xmmintrin.h>
#include <d3d9.h>
#include "globals.hpp"
#include <emmintrin.h>
#include <intrin.h>
#include <emmintrin.h>
#include <utility>

namespace Game
{

	static uint64_t Gamemanager()
	{
		return __ROL8__(driver::read<uint64_t>(driver::initial::base_address + 0x81F7A60) - 0x24, 0x1A);
	}

	uintptr_t Getcamera()
	{
		uint64_t camera_mgr = driver::read<uint64_t>(driver::initial::base_address + 0x6760E78);
		camera_mgr = __ROL8__(driver::read<uint64_t>(camera_mgr + 0x40) ^ 0xE86459E5EF6B5C18, 0x11) + 0x56737AE56A1000C7;
		return camera_mgr = driver::read<uint64_t>(camera_mgr);
	}
	uint64_t GetEntityList(const uint64_t gamemanager) //controller list 
	{
		return driver::read<uint64_t>(gamemanager + 0x70) - 0x4A;

	}
	uint32_t GetEntityCount(const uint64_t gamemanager)
	{
		uint64_t EntityCount = driver::read<uint64_t>(gamemanager + 0x70 + 0x8) - 0x4A;;
		return EntityCount & 0x3FFFFFFF;
	}

	static uint64_t Skeleton(const uint64_t pawn) {
		return (((driver::read<uint64_t>(pawn + 0x9B8) ^ 0x5A4A3300808D5FBB) - 101) ^ 0x4E1635573171789C);
	}

	uintptr_t Pawn(uintptr_t controller)
	{
		return ((driver::read<uint64_t>(controller + 0x38) - 0x46) ^ 0x7F) + 0x4B10EB6F874EE4C7;
	}

	uintptr_t Actor(uintptr_t pawn)  //actor=component 
	{
		return ((driver::read<uintptr_t>(pawn + 0x18) - 0x64) ^ 0x47A9D613D41EBE75) - 0x12;
	}

	static uint64_t v1;
	static uint64_t v2;
	static uint64_t v3;

	static void init_view_data_decryption(void)
	{
		v1 = 0x76;
		v2 = 0x782FCC5940664331;
		v3 = 0x8F7F4651C426B876;
	}

	static uint64_t decrypt_view_data(const uint64_t x)
	{
		auto b = ((x - v1) ^ v2) + v3;
		v1 += 0x76113CF6FBCE130B;
		v2 += 0x43F1895F3DB46234;
		v3 += 0x22C10F219F85038E;
		return b;
	}

	bool WorldToScreen(vec3 world, vec3& screen)
	{
		uintptr_t viewright = 0x1E0; // matt offset
		uint64_t camera_fovx = 0x31C; //values are close
		uint64_t camera_fovy = 0x314; //values are close

		init_view_data_decryption();

		__m128i pRight = driver::read<__m128i>(globals.cam + viewright);
		pRight.m128i_i64[0] = decrypt_view_data(pRight.m128i_i64[0]);
		pRight.m128i_i64[1] = decrypt_view_data(pRight.m128i_i64[1]);
		vec3 vecRight = *(vec3*)&(pRight);

		__m128i pUp = driver::read<__m128i>(globals.cam + viewright + 0x10);
		pUp.m128i_i64[0] = decrypt_view_data(pUp.m128i_i64[0]);
		pUp.m128i_i64[1] = decrypt_view_data(pUp.m128i_i64[1]);
		vec3 vecUp = *(vec3*)&(pUp);

		__m128i pForward = driver::read<__m128i>(globals.cam + viewright + 0x20);
		pForward.m128i_i64[0] = decrypt_view_data(pForward.m128i_i64[0]);
		pForward.m128i_i64[1] = decrypt_view_data(pForward.m128i_i64[1]);
		vec3 vecForward = *(vec3*)&(pForward);

		__m128i pTranslation = driver::read<__m128i>(globals.cam + viewright + 0x30);
		pTranslation.m128i_i64[0] = decrypt_view_data(pTranslation.m128i_i64[0]);
		pTranslation.m128i_i64[1] = decrypt_view_data(pTranslation.m128i_i64[1]);
		vec3 vecTranslation = *(vec3*)&(pTranslation);

		vec3 temp = world - vecTranslation;
		float x = temp.Dot(vecRight);
		float y = temp.Dot(vecUp);
		float z = temp.Dot(vecForward * -1.f);


		uint32_t fovx__ = driver::read<uint32_t>(globals.cam + camera_fovx);
		uint32_t fovy__ = driver::read<uint32_t>(globals.cam + camera_fovy);

		uint32_t fovy = __ROR4__(fovy__ + 0x63C25563, 0x1D) - 0x64;
		uint32_t fovx = ((fovx__ - 0x78) ^ 0x7B143E85) + 0x70B6841D;

		float fovX = *(float*)&fovx;
		float fovY = *(float*)&fovy;

		screen.x = (globals.width / 2.f) * (1.f + x / -fovX / z); // fovx
		screen.y = (globals.height / 2.f) * (1.f - y / -fovY / z); // fovy
		screen.z = z;
		// return vec3((globals.width / 2) * (1 + x / -fovX / z), (globals.height / 2) * (1 - y / -fovY / z), z);
		//if (screen.x < 0.0f || screen.x > globals.width)
		//	return false;
		return z >= 1.0f;
	}
	uint64_t ReplicationInfo(uint64_t entity) //a
	{
		return((driver::read<uintptr_t>(entity + 0xA8) - 0xB9BC19B078F9299) ^ 0x4B) - 0x5F;
	}
	uint32_t get_team_id(uint64_t replication)
	{
		return __ROL1__(driver::read<uint8_t>(replication + 0x859) + 0x2D, 2) - 0x47;
	}


	std::string OperatorNames[30][7] =
	{
	{"Recruit","SMOKE","MUTE","SLEDGE","THATCHER"}, // 0
	{"Recruit","CASTLE","ASH","PULSE","THERMITE"}, // 1
	{"","DOC","ROOK","TWITCH","MONTAGNE"}, // 2
	{"","GLAZ","FUZE","KAPKAN","TACHANKA"}, // 3
	{"","BLITZ","IQ","JAGER","BANDIT"}, // 4
	{"","BUCK","FROST"}, // 5
	{"","BLACKBEARD","VALKYRIE"}, // 6
	{"","CAPITAO","CAVEIRA"}, // 7
	{"","HIBANA","ECHO"}, // 8
	{"","JACKAL","MIRA"}, // 9
	{"","YING","LESION"}, // 10
	{"","ELA","ZOFIA"}, // 11
	{"","DOKKAEBI","VIGIL"}, // 12
	{"","","LION","FINKA"}, // 13
	{"","MAESTRO","ALIBI"}, // 14
	{"","MAVERICK","CLASH"}, // 15
	{"","NOMAD","KAID", ""}, // 16
	{"","MOZZIE","GRIDLOCK"}, // 17
	{"","NOKK"}, // 18
	{"","WARDEN"}, // 19
	{"","Alexander"}, // 20
	{"","AMARU"}, // 21
	{"","KALI","WAMAI", "ACE", "ARUNI", "OSA"}, // 22
	{"","ORYX", "FLORES", "AZAMI"}, // 23
	{"","IANA"}, // 24
	{"","MELUSI"}, // 25
	{"ZERO"}, // 26
	{"THUNDERBIRD"}, // 27
	{"THORN"}, // 28
	{"SENS"}, // 29
	};

	const char* GetPlayerName(uint64_t& replication)
	{
		return driver::read<const char*>(replication + 0x9D8);
	}
	const std::string GetOperatorName(const uint64_t& replication_info)
	{
		auto CTU = driver::read<uint8_t>(replication_info + 0x120) % 30;
		auto OP = driver::read<uint8_t>(replication_info + 0x121) % 7;
		
		//std::cout << "CTU of array number (recruit): -> " << CTU<< std::endl;
		//std::cout << "OP of array number  (recruit): -> " << OP << std::endl;
		return OperatorNames[driver::read<uint8_t>(replication_info + 0x120) % 30][driver::read<uint8_t>(replication_info + 0x121) % 7];

	}
	vec2 GetOperatorArrayLocation(const uint64_t& replication_info)
	{
		float CTU = driver::read<uint8_t>(replication_info + 0x120) % 30;
		float OP = driver::read<uint8_t>(replication_info + 0x121) % 7;
		return vec2{ CTU, OP };
	}

	uint64_t WeaponManager(uint64_t actor)
	{

		uintptr_t component = driver::read<uintptr_t>(actor + 0xD8); 
		if (!component) {
			return 0;
		}
		BYTE index = driver::read<BYTE>(actor + 0x221);
		if (!index) {
			return 0;
		}
		uintptr_t weaponArray = driver::read<uintptr_t>(component + (index * sizeof(uintptr_t)));
		if (!weaponArray) {
			return 0;
		}
		//79 6F 48 8B 11  end of the sub before if statement 
		uintptr_t entry = ((driver::read<uintptr_t>(weaponArray + 0x68) ^ 0x4310901AECDBC648i64) + 0x702BB7122605A1Ci64);
		entry = driver::read<uintptr_t>(entry);

		uintptr_t array_entry = driver::read<uintptr_t>(entry + 0x1B0);
		if (!array_entry) {
			return 0;
		}
		//F7 D7 0F 43 FE BE ? ? ? ? 89 D9  end of the sub
		uintptr_t current_weapon = __ROL8__(driver::read<uintptr_t>(array_entry + 616) - 0x6B88C874D9CB6D0Ai64, 46) - 0x8855542A312108Bi64;
		if (!current_weapon) {
			return 0;
		}
		return current_weapon;
	}

	uint64_t BulletsPerShotOLD(uint64_t currentweapon)
	{
		uint64_t v47 = driver::read<uint64_t>(currentweapon + 0x280);
		uint64_t v48 = __ROL__<uint64_t>(driver::read<uint64_t>(v47 + 8i64 * driver::read<uint32_t>(v47 + 728) + 544) - 109i64, 62) + 0x77E9AE1599603CC1i64;
		uint64_t v49 = driver::read<uint64_t>(v48 + 0x30) ^ 0xD39C71CF127E07D8ui64;
		uint64_t v50 = driver::read<uint64_t>(v49);
		uint64_t v76 = driver::read<uint64_t>(v50 + 0x168);
		return driver::read<uint64_t>(v76);
	}

	uint64_t BulletsPerShotOLD2(uint64_t currentweapon)
	{
		//F0 4C 01 68 ? 4C 89 F1 FF 15 ? ? ? ? 48 85 F6
		//49 89 CC 48 83 B9 ?? ?? ?? ?? ?? 74 10
		uint64_t v47 = driver::read<uint64_t>(currentweapon + 0x280); //same 
		uint64_t result = __ROL8__(
			driver::read<uint64_t>(((driver::read<uint64_t>(v47 + 8i64 * driver::read<uint32_t>(v47 + 728) + 544) - 30i64) ^ 0xFE00AB21CB605E3Fui64)
				- 80
				+ 0x38)
			- 61i64,
			1);
		uint64_t v49 = driver::read<uint64_t>(result - 0x16AB818EB70A6C4Fi64);
		uint64_t v51 = driver::read<uint64_t>(v49 + 360); //same 
		result = driver::read<uint64_t>(v51);
		return result;
	}
	uintptr_t BulletsPerShot(uintptr_t Weapon)
	{
		__int64 v15; // rax
		__int64 v16; // rcx
		__int64 v17; // rdi
		__int64 v18; // rbx
		__int64 v20; // rcx
		__int64 v21; // rcx
		uintptr_t BPS = 0;

		v16 = (driver::read<uint64_t>(Weapon + 0x28) - 0x192022C2CAF7D650i64) ^ 0x9D30C78BBDB7108Fui64;
		if (v16)
		{
			v17 = driver::read<uint64_t>(v16 + 0x29CBA3B47A69B158i64);
			if (v17)
			{
				v18 = driver::read<uint64_t>(v17);
				if (v18)
				{
					v20 = driver::read<uint64_t>(v18 + 360);
					if (v20)
					{
						v21 = driver::read<uint64_t>(v20);
						if (v21) {
							BPS = (v21 + 96);
							return BPS;
						}
					}
				}
			}
		}
	}

	float Health(uintptr_t actor)
	{
		auto ComponentList = driver::read<uintptr_t>(actor + 0xD8);
		auto DamageComponent = driver::read<uintptr_t>(ComponentList + 0x8);

		return __ROL4__(driver::read<DWORD>(DamageComponent + 0x1E8) + 0x30899296, 0x17);
	}
	vec3 GetPos(uint64_t entPawn)
	{
		return driver::read<vec3>(Actor(entPawn) + 0x50);
	}
	void TransformsCalculation(__int64 pBones, __m128* ResultPosition, __m128* BoneInfo) //23.10.2021
	{
		__m128 v5; // xmm2
		__m128 v6; // xmm3
		__m128 v7; // xmm0
		__m128 v8; // xmm4
		__m128 v9; // xmm1

		__m128 v10 = { 0.500f, 0.500f, 0.500f, 0.500f };
		__m128 v11 = { 2.000f, 2.000f, 2.000f, 0.000f };

		__m128 v12 = driver::read<__m128>(pBones);
		__m128 v13 = driver::read<__m128>(pBones + 0x10);

		v5 = v13;

		v6 = _mm_mul_ps(*(__m128*)BoneInfo, v5);
		v6.m128_f32[0] = v6.m128_f32[0]
			+ (float)(_mm_cvtss_f32(_mm_shuffle_ps(v6, v6, 0x55)) + _mm_cvtss_f32(_mm_shuffle_ps(v6, v6, 0xAA)));
		v7 = _mm_shuffle_ps(v13, v5, 0xFF);
		v8 = _mm_sub_ps(
			_mm_mul_ps(_mm_shuffle_ps(v5, v5, 0xD2), *(__m128*)BoneInfo),
			_mm_mul_ps(_mm_shuffle_ps(*(__m128*)BoneInfo, *(__m128*)BoneInfo, 0xD2), v5));
		v9 = _mm_shuffle_ps(v12, v12, 0x93);
		v9.m128_f32[0] = 0.0;
		*(__m128*)ResultPosition = _mm_add_ps(
			_mm_shuffle_ps(v9, v9, 0x39),
			_mm_mul_ps(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(_mm_shuffle_ps(v8, v8, 0xD2), v7),
						_mm_mul_ps(_mm_shuffle_ps(v6, v6, 0), v5)),
					_mm_mul_ps(
						_mm_sub_ps(_mm_mul_ps(v7, v7), (__m128)v10),
						*(__m128*)BoneInfo)),
				(__m128)v11));
	}
	inline vec3 GetBonePosById(std::uintptr_t playerpawn, int index)
	{
		__m128 Output{};

		std::uintptr_t pBonesChain2 = Skeleton(playerpawn);
		pBonesChain2 = driver::read<std::uintptr_t>(pBonesChain2);

		std::uintptr_t pBones = driver::read<std::uintptr_t>(pBonesChain2 + 0x250);

		std::uintptr_t pBonesData = driver::read<std::uintptr_t>(pBones + 0x58);

		std::uintptr_t idarray = driver::read<std::uintptr_t>(pBonesChain2 + 0xB8);

		index = driver::read<int>(idarray + index * 0x4);

		__m128 BoneInfo = driver::read<__m128>((0x20 * index) + pBonesData);
		TransformsCalculation(pBones, &Output, &BoneInfo);

		return { Output.m128_f32[0], Output.m128_f32[1], Output.m128_f32[2] };
	}
	uint64_t GetLightManager()
	{
		uint64_t LightManager = driver::read<uint64_t>(driver::initial::base_address + 0x6AB9F18);
		return driver::read<uint64_t>((__ROL8__(driver::read<uint64_t>(driver::read<uint64_t>(driver::initial::base_address + 0x6AB9F18) + 0x10), 0x5) + 0x48F86F8042ADADAA) + 0x3F8);
	}
	std::pair<uint64_t, uint32_t> get_gadget_list()
	{
		//48 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 41 80 66 6C FB
		uintptr_t networkManager = driver::read<uint64_t>(driver::initial::base_address + 111966936); //0x6AC7AD8

		const auto decryption = [&networkManager](const uint32_t offset = 0) -> uint64_t
		{
			return driver::read<uint64_t>(networkManager + 0x40 + offset);
		};

		return { decryption(), static_cast<uint32_t>(decryption(8) & 0x3FFFFFFF) };
	}

}




