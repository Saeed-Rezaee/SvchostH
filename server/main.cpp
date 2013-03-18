#include <iostream>
#include <conio.h>

#include <SFML\Network.hpp>

#include "Port.h"

extern int getPort();

sf::UdpSocket g_socket;

void sendToAll(std::string cmd)
{
	unsigned port = getPort();
	sf::Packet packet;

	for(unsigned i = 0; i < 256; i++)
	{
		packet << cmd;
		g_socket.send(packet, sf::IpAddress(10, 0, 0, i), port);
	}
}

int main()
{
	sf::IpAddress addr;
	unsigned int port = getPort();

	std::cout << "Podaj adres ip: ";
	std::cin >> addr;


	int command = -1;
	while (command != 0)
	{
		system("cls");

		std::cout << "Podaj numer komendy do wykonania: ";
		std::cin >> command;

		sf::Packet packet;
		packet << command;
		g_socket.send(packet, addr, port);

		std::cout << "Pakiet wyslany!" << std::endl;
		_getch();
	}

	return 0;
}