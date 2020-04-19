#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include<list>
#include<deque>
#include "structs.hpp"

sf::RenderWindow window(sf::VideoMode(1200, 700), "Gob");



sf::Sprite blood, sidebarSprite, compass, needle;
sf::Texture bloodt, compasst, needlet;
sf::RenderTexture sidebar;
string currentDirection="north";
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
compasst.loadFromFile("other/compass.png");
compass.setTexture(compasst);
compass.setPosition(1060,560);
needlet.loadFromFile("other/needle.png");
needle.setTexture(needlet);
needle.setPosition(1060,560);
}


bool mouseInRegion(Region const &region){
    sf::Vector2i pos=sf::Mouse::getPosition(window);
    return pos.x>=region.left && pos.x<=region.right&&pos.y>=region.top&&pos.y<=region.bottom;
}
void setDirection(string direction){
    if(currentRoom->hasView(direction))
    currentDirection=direction;
}
int main(){
    setupRooms();
    setup();


    sf::Clock clock;
    sf::Time elapsed;
    sf::Event event;

    window.setFramerateLimit(20);
    Battle battle;
    int peacetimer=5;
    while (window.isOpen())
    {

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type==sf::Event::MouseButtonPressed&&!inCombat){
                sf::Vector2i pos=sf::Mouse::getPosition(window);
                if(pos.x>1060&&pos.y>560){
                    if(pos.y-620>pos.x-1120){
                        if(pos.y-620<1120-pos.x){
                            setDirection("west");
                        }else{
                            setDirection("south");
                        }
                    }else{
                        if(pos.y-620<1120-pos.x){
                            setDirection("north");
                        }else{
                            setDirection("east");
                        }
                    }
                }else{
                    Room *destination=currentRoom;
                    for(vector<Clickable*>::iterator it=currentRoom->clickables.begin();
                        it!=currentRoom->clickables.end();it++){
                        printf((*it)->objectType.c_str());
                        if(!(*it)->objectType.compare("way on")){
                            if(mouseInRegion((*it)->region))
                            destination=((WayOn*)*it)->destination;
                        }
                    }
                    currentRoom=destination;
                }
                
            }
        }
                elapsed = clock.getElapsedTime();
        if(elapsed.asSeconds()>0.1){
            clock.restart();
            if(msg.queue.empty()){
                if(inCombat)battle.nextCharacter();
            }else msg.print();
            if(!hostility)peacetimer--;
            if(peacetimer<=0)inCombat=false;
        }

        window.clear();
if(inCombat){
    window.draw(goblin.sprite);
    window.draw(msg.text);
}
else window.draw(currentRoom->getSprite(currentDirection));
window.draw(sidebarSprite);
window.draw(compass);
window.draw(needle);
if(inCombat&&goblin.sta<=0)window.draw(blood);

        window.display();
    }

    return 0;
}