#include "Player.hpp"

Player::Player() {

}

Player::Player(int id, sf::Vector2f pos, sf::IpAddress ip, unsigned short port) :
    id(id),
    pos(pos),
    ip(ip),
    port(port) {

    states = std::vector<playerState>(playerState::qttPlayerState);
}

int Player::getId() {
    return id;
}

sf::Vector2f Player::getPos() {
    return pos;
}

sf::IpAddress Player::getIp() {
    return ip;
}

unsigned short Player::getPort() {
    return port;
}

std::vector<playerState> *Player::getStates() {
    return &states;
}

void Player::setPos(sf::Vector2f pos) {
    this->pos = pos;
}
