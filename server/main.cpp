#include <Windows.h>
#include <mmsystem.h>

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
	
	while (true)
	{
		int recvd = 0;

		g_socket.receive(packet, addr, port);

		packet >> recvd;

		// Open CD Tray
		if (recvd == 1)
		{
			mciSendString("open CDAudio", NULL, 0, NULL);
			mciSendString("set CDAudio door open", NULL, 0, NULL);
		}

		// Turn off monitor
		if (recvd == 2)
		{
			SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)2);
		}
	}
	return 0;
}