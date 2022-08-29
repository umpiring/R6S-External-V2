#define WIN32_LEAN_AND_MEAN


#include <iostream>
#include <Windows.h>
#include "../Game.hpp"
#include "../Overlay.hpp"
#include <xmmintrin.h>
#include "../Defines.hpp"
#include "../globals.hpp"
#include <random>
#include "../Loading/xor.h"

HWND hwnd = nullptr;
using namespace std;



int main()
{
	std::cout << xorstr_("\n [ -> ] Initializing...") << std::endl;




	while (!FindWindowA(xorstr_("R6Game"), xorstr_("Rainbow Six"))) {
		printf(".");
		
	}
	Sleep(1000);
	driver::pid = find_process_by_id(xorstr_("RainbowSix.exe"));
	driver::base_address = get_module_base(driver::initial::pid, (char*)xorstr_("RainbowSix.exew"));
	// Updated
	std::cout << xorstr_("[ -> ] Pid -> ") << driver:pid << std::endl;
	std::cout << xorstr_("[ -> ] Base -> 0x") << std::hex << driver::base_address << std::dec << std::endl;


	

	setup_window();
	setup_directx(MyWnd);


	 main_loop();



	std::getchar();
}
