#include <iostream>
#include <unistd.h>

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "../Utility/Actions.hpp"
#include "Player.hpp"

const int FRAMES = 30;

sf::TcpListener listener;
sf::UdpSocket socket;
sf::IpAddress ip = "127.0.0.1";
unsigned short serverPort = 54000;
int id = 0;

void checkNewConnections(std::vector<Player> &players, sf::TcpListener &listener) {
    sf::TcpSocket socket;
    while (listener.accept(socket) == sf::Socket::Done) {
        sf::IpAddress ip = socket.getRemoteAddress();
        unsigned short port = socket.getRemotePort();

        Player player(id,sf::Vector2f(300,300),ip, port);
        players.push_back(player);

        std::cout << "New player " << id << " at " << ip << " " << port << std::endl;
        ++id;
    }
}

void sendFeedback(std::vector<Player> &players) {
    for (Player& player : players) {
        sf::Packet packet;
        packet << player.getPos().x << player.getPos().y;
        socket.send(packet, player.getIp(), player.getPort());
    }
}

void recive(std::vector<Player> &players) {
    for (Player& player : players) {
        sf::Packet packet;
        sf::IpAddress ip = player.getIp();
        unsigned short port = player.getPort();
        std::vector<playerState> *pState = player.getStates();
        if (socket.receive(packet, ip, port) == sf::Socket::Done) {
            std::cout << "Server Reciviendo Player " << player.getId() << std::endl;
            for (uint i = 0; i < playerState::qttPlayerState; ++i) {
                int aux;
                packet >> aux;
                (*pState)[i] = static_cast<playerState> (aux);
            }
        }
    }
}

void update(float deltaTime, std::vector<Player> &players){
    for (Player& player : players) {
        std::vector<playerState> pState = *player.getStates();
        sf::Vector2f pos = player.getPos();
        for (unsigned int i = 0; i < playerState::qttPlayerState; ++i) {
            if (pState[i]) {
                switch (i) {
                case playerState::MOVE_R:
                    std::cout << "moviendose asia la dejxa" << std::endl;
                    pos.x += 1;
                    break;
                case playerState::MOVE_L:
                    std::cout << "moviendose asia la ijkierda" << std::endl;
                    pos.x -= 1;
                    break;
                case playerState::MOVE_UP:
                    std::cout << "moviendose puuuuupp" << std::endl;
                    pos.y -= 1;
                    break;
                case playerState::MOVE_DOWN:
                    std::cout << "moviendose down" << std::endl;
                    pos.y += 1;
                    break;
                default:
                    break;
                }
            }
        }
        player.setPos(pos);
    }
}

int main() {
    std::vector<Player> players;
    listener.setBlocking(false);
    listener.listen(serverPort);

    socket.setBlocking(false);
    socket.bind(serverPort);
    bool running = true;

    while (running) {
        sf::Clock c;

        checkNewConnections(players, listener);

        recive(players);
        update(1/FRAMES, players);

        sendFeedback(players);

        float sleepTime = (1.0f/FRAMES) - c.restart().asSeconds();
        usleep(sleepTime*1000000);
    }

    return 0;
}
