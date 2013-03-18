#include <Windows.h>
#include <mmsystem.h>
#include <string>

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
			// UPDATE CODE
		}
		else
		{
			int argc;
			packet >> argc;

			std::string cmdLine = cmd;

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