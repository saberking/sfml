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
void redrawSidebar(){
    sidebar.clear( sf::Color(0, 0, 0, 0));
    for(int i = 0;i<4;i++){
        if(chars[i].sta>0)sidebar.draw(chars[i].sprite);
    }
    sidebar.display();
sidebarSprite.setTexture(sidebar.getTexture());
sidebarSprite.setPosition(900.f,0.f);
}
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

compasst.loadFromFile("other/compass.png");
compass.setTexture(compasst);
compass.setPosition(1060,560);
needlet.loadFromFile("other/needle.png");
needle.setTexture(needlet);
needle.setPosition(1119,619);
needle.setOrigin(59,59);
        sidebar.create(1200,700);

}


bool mouseInRegion(Region *region){
    sf::Vector2i pos=sf::Mouse::getPosition(window);
    return pos.x>=region->left && pos.x<=region->right&&pos.y>=region->top&&pos.y<=region->bottom;
}
void setDirection(string direction){
    if(currentRoom->hasView(direction))
    currentDirection=direction;
}
void needleDirection(string direction){
    if(direction=="north")needle.setRotation(0);
        if(direction=="east")needle.setRotation(90);
            if(direction=="south")needle.setRotation(180);
    if(direction=="west")needle.setRotation(270);


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
                    string newDirection=currentDirection;
                    for(vector<Clickable*>::iterator it=currentRoom->getView(currentDirection)->clickables.begin();
                        it!=currentRoom->getView(currentDirection)->clickables.end();it++){
                        if(!(*it)->objectType.compare("way on")){
                            if(mouseInRegion((*it)->region)){
                                destination=((WayOn*)*it)->destination;
                                newDirection=((WayOn*)*it)->entryDirection;
                            }

                        }
                    }
                    currentRoom=destination;
                    currentDirection=newDirection;
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
            if(peacetimer<=0)battle.end();
        }

        window.clear();
        window.draw(currentRoom->getView(currentDirection)->sprite);

if(inCombat){
    window.draw(goblin.sprite);
}
    window.draw(msg.text);
redrawSidebar();
window.draw(sidebarSprite);
window.draw(compass);
needleDirection(currentDirection);
window.draw(needle);
if(inCombat&&goblin.sta<=0)window.draw(blood);

        window.display();
    }

    return 0;
}