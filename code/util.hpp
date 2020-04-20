#include <stdlib.h>
#include<list>
#include<vector>
#include<string>
#include <deque>
#include <SFML/Graphics.hpp>
#include <conio.h>
#include <stdio.h>
void leftClick(sf::Vector2i pos);
void rightClick(sf::Vector2i pos);
std::string currentDirection="north";
void needleDirection(std::string direction, sf::Sprite &n);
sf::RenderWindow window(sf::VideoMode(1200, 700), "Gob");

float turnLength=0.7;

sf::Sprite minimap,blood, sidebarSprite, compass, needle, bag, tent,needle2;
sf::Texture minimapt,bloodt, compasst, needlet, bagt, tentt;
sf::RenderTexture sidebar;
sf::RenderTexture monsters;
sf::Text goldText;