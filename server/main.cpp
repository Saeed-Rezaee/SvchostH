#include <Windows.h>
#include <mmsystem.h>

#include <SFML\Network.hpp>

sf::UdpSocket g_socket;

int main()
{
	g_socket.setBlocking(true);
	g_socket.bind(34567);

	sf::Packet packet;
	sf::IpAddress addr;
	unsigned short port;
	
	while (true)
	{
		int recvd = 0;

		g_socket.receive(packet, addr, port);

		packet >> recvd;

		if (recvd == 1)
		{
			mciSendString("open CDAudio", NULL, 0, NULL);
			mciSendString("set CDAudio door open", NULL, 0, NULL);
		}
	}
	return 0;
}