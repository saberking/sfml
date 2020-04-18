#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include<list>
#include<deque>
#include "structs.hpp"

sf::RenderWindow window(sf::VideoMode(1200, 700), "Gob");



sf::Sprite blood, sidebarSprite;
sf::Texture bloodt;
sf::RenderTexture sidebar;
void setup(){

    srand(time(NULL));
        font.loadFromFile("fonts/thestrong.ttf");
for(int i=0;i<4;i++){
    chars[i].sprite.setPosition(sf::Vector2f(0.f, (float)80+153*i));
    chars[i].resizeTexture(0.75f,0.75f);
}
bloodt.loadFromFile("blood.png");
blood.setTexture(bloodt);
blood.setPosition(sf::Vector2f(400.f,200.f));
blood.setScale(sf::Vector2f(0.75f,0.75f));
    sidebar.create(1200,700);
    for(int i = 0;i<4;i++){
        sidebar.draw(chars[i].sprite);
    }
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