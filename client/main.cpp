#include <iostream>
#include <conio.h>

#include <SFML\Network.hpp>

#include "Port.h"

sf::UdpSocket g_socket;

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