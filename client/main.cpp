#include <iostream>
#include <conio.h>
#include <sstream>

#include <SFML\Network.hpp>

#include "Port.h"

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

sf::Packet parseCommand(std::string cmd)
{
	sf::Packet packet;

	std::string buffer;

	std::string command;
	int argc = -1;
	std::vector<std::string> args;
	for(unsigned i = 0; i < cmd.size(); i++)
	{
		if(cmd[i] == ' ')
		{
			if(argc == -1)
			{
				command = buffer;
				buffer.clear();
				argc++;
			}
			else
			{
				args.push_back(buffer);
				buffer.clear();
			}
		}
		else buffer += cmd[i];
	}
	args.push_back(buffer);

	packet << command;
	packet << static_cast<int>(args.size());
	for(unsigned i = 0; i < args.size(); i++) packet << args[i];

	return packet;
}

int main()
{
	sf::IpAddress addr;
	unsigned int port = getPort();

	std::cout << "Enter target ip: ";
	std::cin >> addr;
	std::cin.ignore();

	std::string cmd = "";
	while (cmd != "exit")
	{
		system("cls");

		std::cout << "Enter desired command: ";
		std::getline(std::cin, cmd);

		sf::Packet packet;
		g_socket.send(parseCommand(cmd), addr, port);

		std::cout << "Pakiet wyslany!" << std::endl;
		_getch();
	}

	return 0;
}