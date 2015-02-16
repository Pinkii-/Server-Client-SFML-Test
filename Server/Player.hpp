#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "../Utility/Actions.hpp"

class Player {
private:
    int id;
    sf::Vector2f pos;
    std::vector<playerState> states;

    sf::IpAddress ip;
    unsigned short port;
public:
    Player();
    Player(int id, sf::Vector2f pos, sf::IpAddress ip, unsigned short port);
    int getId();
    sf::Vector2f getPos();
    sf::IpAddress getIp();
    unsigned short getPort();
    std::vector<playerState> *getStates();
    void setPos(sf::Vector2f pos);
};

#endif // PLAYER_HPP
