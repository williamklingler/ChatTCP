#include <SFML\Graphics.hpp> 
#include <SFML\Audio.hpp>
#include <SFML\Network.hpp>
#include <string>
#include <iostream>
#include <map>
#include <conio.h>
#include <thread>

using namespace std;
void windowThread();
int main()
{
	thread t1(windowThread);
	t1.detach();
	cout << "TCP Messaging Portal!" << endl;
	sf::IpAddress ip;
	sf::TcpSocket socket;
	char connectionType, mode; 
	string text = "Connect to ";
	char buffer[2000];
	size_t received;
	cout << "Enter s for server, enter c for client" << endl;
	cin >> connectionType;
	if (connectionType == 's')
	{
		int port = 2000;
		cout << "Enter the port you would like to listen on (public ports are > 1024): ";
		cin >> port;
		sf::TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);
		cout << "Connection to " << socket.getRemoteAddress() << " established on port:  " << socket.getRemotePort() << endl;
		text += "Server";
		mode = 's';
		
	}
	else if (connectionType == 'c')
	{
		string ipString;
		cin.get();
		cin.ignore();
		cout << "Enter the public ip address of server you would like to connect to: ";
		getline(cin, ipString);
		ip = sf::IpAddress::IpAddress(ipString);
		cout << ip << endl;
		int port = 2000;
		cout << "Enter the port you would like to connect to: ";
		cin >> port;
		sf::Socket::Status status = socket.connect(ip, port);
		if (status != sf::Socket::Done)
		{
			cout << "Something went wrong" << endl;
		}
		else {

			cout << "Connection to " << socket.getRemoteAddress() << " established on port: " << socket.getRemotePort() << endl;
			text += "Client";
			mode = 'r';

		}
	}
	socket.send(text.c_str(), text.length() + 1);
	socket.receive(buffer, sizeof(buffer), received);
	cout << buffer << endl;

	bool done = false;

	while (!done)
	{
		if (mode == 's')
		{
			getline(cin, text);
			socket.send(text.c_str(), text.length() + 1);
			mode = 'r';
		}
		else if (mode == 'r')
		{
			socket.receive(buffer, sizeof(buffer), received);
			if (received > 0)
			{
				cout << "Receieved: " << buffer << endl;
				mode = 's';
			}
		}

	}
	
	system("Pause");
	return 0;
}

/*void windowThread()
{
	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode()), "SFML window", sf::Style::Default);
	sf::Font font;
	font.loadFromFile("arial.ttf");
	// Create a text
	sf::Text text("hello", font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	// Draw it
	window.draw(text);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		window.clear();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.draw(shape);
		window.display();
	}

}*/