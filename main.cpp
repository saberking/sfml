#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include<list>
#include<deque>
#include "structs.hpp"

sf::RenderWindow window(sf::VideoMode(1200, 700), "Gob");



sf::Sprite sprite, ch1, ch2, ch3, ch4;
sf::Texture texture, ch1t, ch2t, ch3t, ch4t;

void setup(){
    srand(time(NULL));
        font.loadFromFile("fonts/thestrong.ttf");

    texture.loadFromFile("Gob.png");
sprite.setTexture(texture);
    ch1t.loadFromFile("pics/ch1.png");
ch1.setTexture(ch1t);
ch1.setPosition(sf::Vector2f(900.f, 100.f));
ch1.setScale(sf::Vector2f(0.75f, 0.75f));
    ch2t.loadFromFile("pics/ch2.png");
ch2.setTexture(ch2t);
ch2.setPosition(sf::Vector2f(900.f, 250.f));
ch2.setScale(sf::Vector2f(0.75f, 0.75f));
    ch3t.loadFromFile("pics/ch3.png");
ch3.setTexture(ch3t);
ch3.setPosition(sf::Vector2f(900.f, 400.f));
ch3.setScale(sf::Vector2f(0.75f, 0.75f));

    ch4t.loadFromFile("pics/ch4.png");
ch4.setTexture(ch4t);
ch4.setPosition(sf::Vector2f(900.f, 550.f));
ch4.setScale(sf::Vector2f(0.75f, 0.75f));
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
window.draw(sprite);
window.draw(ch1);
window.draw(ch2);
window.draw(ch3);
window.draw(ch4);
window.draw(msg.text);

        window.display();
    }

    return 0;
}