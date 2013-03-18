#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include <string>
#include <ctime>

#include "Port.h"

int main(int argc, char* argv[])
{
	srand(static_cast<unsigned>(time(NULL)));

	std::string arg = argv[1];
	
	// Open CD Tray
	if (arg == "opencdtray")
	{
		mciSendString("open CDAudio", NULL, 0, NULL);
		mciSendString("set CDAudio door open", NULL, 0, NULL);
	}

	// Turn off monitor
	if (arg == "monitoroff")
	{
		int time = 3;

		std::string arg2 = argv[2];
		time = atoi(arg2.c_str());
		
		SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)2);
		Sleep(time*1000);
		SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)-1);
	}

	// Play random shit
	if (arg == "playshit")
	{
		for (int i = 0; i < 20; ++i)
		{
			Beep(rand() % 700 + 100, 500);
		}
	}

	return 0;
}