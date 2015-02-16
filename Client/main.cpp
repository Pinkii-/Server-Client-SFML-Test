#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>


#include "../Utility/Actions.hpp"
#include "InputManager.hpp"

sf::TcpSocket conector;
sf::UdpSocket socket;
sf::IpAddress ip = "147.83.175.33";
unsigned short serverPort = 50000;
unsigned short clientPort;

void sendActions() {
    sf::Packet penis;
    for (unsigned j = 0; j < playerState::qttPlayerState; ++j) {
        penis << InputManager::action(j);
    }
    socket.send(penis,ip,serverPort);
}

void recive(float *a) {
    sf::Packet penis;
    if(socket.receive(penis,ip,serverPort) == sf::Socket::Done) {
        penis >> a[0] >> a[1];
    }
}

void update(float penis[], sf::RectangleShape &shape){
    shape.setPosition(penis[0],penis[1]);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800,600), "Cliente");

    sf::RectangleShape player;
    player.setSize(sf::Vector2f(100,100));
    player.setPosition(400,300);
    player.setFillColor(sf::Color::Blue);

    conector.setBlocking(false);
    conector.connect(ip,serverPort);
    clientPort = conector.getLocalPort();

    char data[1] = {0};
    conector.send(data, 1);

    socket.setBlocking(false);
    socket.bind(clientPort);

    InputManager::bind(playerState::MOVE_L,     sf::Keyboard::Key::A);
    InputManager::bind(playerState::MOVE_R,     sf::Keyboard::Key::D);
    InputManager::bind(playerState::MOVE_UP,    sf::Keyboard::Key::W);
    InputManager::bind(playerState::MOVE_DOWN,  sf::Keyboard::Key::S);

    int n = 0;

    while (window.isOpen()) {
        if (n % 1000000 == 0) {
            n = 0;

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Key::Escape) window.close();
                break;
            default:
                break;
            }
        }
        InputManager::update();

        sendActions();

        float penis[2];
        penis[0] = player.getPosition().x;
        penis[1] = player.getPosition().y;

        recive(penis);

        update(penis,player);

        std::cout << player.getPosition().x << " " << player.getPosition().y << std::endl;

        window.clear();
        window.draw(player);
        window.display();
        }
        ++n;
    }

	return 0;
}
