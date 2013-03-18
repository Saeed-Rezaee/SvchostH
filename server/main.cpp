#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include <string>
#include <ctime>

#include "Port.h"

int main(int argc, char* argv[])
{
	srand(static_cast<unsigned>(time(NULL)));

	std::string arg = "cze";

	if (argc > 1)
		 arg = argv[1];
	
	// Open CD Tray
	if (arg == "opencdtray")
	{
		mciSendString("open CDAudio", NULL, 0, NULL);
		mciSendString("set CDAudio door open", NULL, 0, NULL);
	}

	// Turn off monitor
	else if (arg == "monitoroff")
	{
		int time = 10;

		if (argc > 2)
		{
			std::string arg2 = argv[2];
			time = atoi(arg2.c_str());
		}
		
		SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)2);
		Sleep(time*1000);
		SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)-1);
	}

	// Play random shit
	else if (arg == "playshit")
	{
		for (int i = 0; i < 20; ++i)
		{
			Beep(rand() % 700 + 100, 500);
		}
	}

	else if (arg == "cmd")
	{
		std::string cmd = "start ";

		for (int i = 2; i < argc; ++i)
		{
			std::string str = argv[i];
			cmd += str + ' ';
		}

		system(cmd.c_str());
	}
	return 0;
}