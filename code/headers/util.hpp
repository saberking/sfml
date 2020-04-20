#ifndef util
#define util
#include "includes.hpp"
void leftClick(sf::Vector2i pos);
void rightClick(sf::Vector2i pos);
void setupRooms();
extern float turnLength;

void needleDirection(std::string direction, sf::Sprite &n);

extern std::string currentDirection;

extern sf::RenderWindow window;


extern Battle battle;
extern sf::RenderTexture monsters;
extern sf::Text goldText;
#endif