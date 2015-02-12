#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>


#include "../Utility/Actions.hpp"
#include "InputManager.hpp"

sf::UdpSocket socket;
sf::IpAddress ip = "127.0.0.1";
unsigned short serverPort = 54000;
unsigned short clientPort = 54001;

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

    socket.setBlocking(false);
    socket.bind(clientPort);

    InputManager::bind(playerState::MOVE_L,sf::Keyboard::Key::A);
    InputManager::bind(playerState::MOVE_R,sf::Keyboard::Key::D);
    InputManager::bind(playerState::MOVE_UP,sf::Keyboard::Key::W);
    InputManager::bind(playerState::MOVE_DOWN,sf::Keyboard::Key::S);



    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }
        InputManager::update();

        sendActions();

        float *penis;
        penis[0] = player.getPosition().x;
        penis[1] = player.getPosition().y;
        recive(penis);

        update(penis,player);

        std::cout << player.getPosition().x << " " << player.getPosition().y << std::endl;

        window.clear();
        window.draw(player);
        window.display();
    }

	return 0;
}
