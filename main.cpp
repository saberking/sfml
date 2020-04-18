#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include<list>
#include<deque>
#include "structs.hpp"

sf::RenderWindow window(sf::VideoMode(1200, 700), "Gob");



sf::Sprite sprite, ch1, ch2, ch3, ch4, blood, sidebarSprite;
sf::Texture texture, ch1t, ch2t, ch3t, ch4t, bloodt;
sf::RenderTexture sidebar;
void setup(){

    srand(time(NULL));
        font.loadFromFile("fonts/thestrong.ttf");

    texture.loadFromFile("Gob.png");
sprite.setTexture(texture);
    ch1t.loadFromFile("pics/ch1.png");
ch1.setTexture(ch1t);
ch1.setPosition(sf::Vector2f(0.f, 100.f));
ch1.setScale(sf::Vector2f(0.75f, 0.75f));
    ch2t.loadFromFile("pics/ch2.png");
ch2.setTexture(ch2t);
ch2.setPosition(sf::Vector2f(0.f, 250.f));
ch2.setScale(sf::Vector2f(0.75f, 0.75f));
    ch3t.loadFromFile("pics/ch3.png");
ch3.setTexture(ch3t);
ch3.setPosition(sf::Vector2f(0.f, 400.f));
ch3.setScale(sf::Vector2f(0.75f, 0.75f));

    ch4t.loadFromFile("pics/ch4.png");
ch4.setTexture(ch4t);
ch4.setPosition(sf::Vector2f(0.f, 550.f));
ch4.setScale(sf::Vector2f(0.75f, 0.75f));
bloodt.loadFromFile("blood.png");
blood.setTexture(bloodt);
blood.setPosition(sf::Vector2f(400.f,200.f));
blood.setScale(sf::Vector2f(0.75f,0.75f));
    sidebar.create(1200,700);
    sidebar.draw(ch1);
    sidebar.draw(ch2);
    sidebar.draw(ch3);
    sidebar.draw(ch4);
    sidebar.display();
sidebarSprite.setTexture(sidebar.getTexture());
sidebarSprite.setPosition(900.f,0.f);
}




int main(){
    setup();


    sf::Clock clock;
    sf::Time elapsed;
    sf::Event event;

    window.setFramerateLimit(20);
    Battle battle;
    while (window.isOpen())
    {

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
                elapsed = clock.getElapsedTime();
        if(elapsed.asSeconds()>1){
            clock.restart();
            if(msg.queue.empty())
            battle.nextCharacter();
            else msg.print();
        }

        window.clear();
window.draw(goblin.sprite);
window.draw(sidebarSprite);
window.draw(msg.text);
if(goblin.sta<=0)window.draw(blood);

        window.display();
    }

    return 0;
}