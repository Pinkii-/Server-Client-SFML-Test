#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "../Utility/Actions.hpp"

sf::UdpSocket socket;
sf::IpAddress ip = "127.0.0.1";
unsigned short serverPort = 54000;
unsigned short clientPort = 54001;

void sendFeedback(sf::Vector2f player) {
    sf::Packet penis;
    penis << player.x << player.y;
    socket.send(penis,ip,clientPort);
}

void recive(std::vector<playerState> &a) {
    sf::Packet penis;
    if(socket.receive(penis,ip,clientPort) == sf::Socket::Done) {
        std::cout << "Server Reciviendo" << std::endl;
        for (uint i = 0; i < playerState::qttPlayerState; ++i) {
            int aux;
            penis >> aux;
            a[i] = static_cast<playerState> (aux);
        }
    }
}

void update(float deltaTime, std::vector<playerState> &a, sf::Vector2f &player){
    for (unsigned int i = 0; i < playerState::qttPlayerState; ++i) {
        if (a[i]) {
            switch (i) {
            case playerState::MOVE_R:
                std::cout << "moviendose asia la dejxa" << std::endl;
                player.x += 1;
                break;
            case playerState::MOVE_L:
                std::cout << "moviendose asia la ijkierda" << std::endl;
                player.x -= 1;
                break;
            case playerState::MOVE_UP:
                std::cout << "moviendose puuuuupp" << std::endl;
                player.y -= 1;
                break;
            case playerState::MOVE_DOWN:
                std::cout << "moviendose down" << std::endl;
                player.y += 1;
                break;
            default:
                break;
            }
        }
    }
}

int main() {

    sf::Vector2f player (400,300);
    socket.setBlocking(false);
    socket.bind(serverPort);
    bool running = true;

    while (running) {
        sf::Clock c;
        float deltaTime = c.restart().asSeconds();
        //        std::cout << deltaTime << std::endl;

        std::vector<playerState> a(playerState::qttPlayerState);
        recive(a);

        update(deltaTime,a, player);

        sendFeedback(player);
    }

    return 0;
}
