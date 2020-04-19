#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include<list>
#include<deque>
#include "code/being.hpp"

#include "code/structs.hpp"
#include "code/messages.hpp"
#include "code/battle.hpp"

sf::RenderWindow window(sf::VideoMode(1200, 700), "Gob");



sf::Sprite blood, sidebarSprite, compass, needle, bag, tent;
sf::Texture bloodt, compasst, needlet, bagt, tentt;
sf::RenderTexture sidebar;
sf::Text goldText;
string currentDirection="north";
void redrawSidebar(){
    sidebar.clear( sf::Color(0, 0, 0, 0));
    sidebar.draw(bag);
    goldText.setString(to_string(gold));
    sidebar.draw(goldText);
    sidebar.draw(tent);
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
        bagt.loadFromFile("other/bag.png");
        bag.setTexture(bagt);
        bag.setPosition(sf::Vector2f(170.f,430.f));
               goldText.setFont(font); // font is a sf::Font

        // set the string to display

        // set the character size
        goldText.setCharacterSize(36); // in pixels, not points!

        // set the color
        goldText.setFillColor(sf::Color::Yellow);

        // set the text style
        goldText.setStyle(sf::Text::Bold );
        goldText.setPosition(sf::Vector2f(210.f, 490.f));
        tentt.loadFromFile("other/tent.png");
        tent.setTexture(tentt);
        tent.setPosition(sf::Vector2f(170.f,310.f));

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
void camp(){
    for(int i=0;i<4;i++){
        chars[i].standing=false;
    }
    battle.start();/*
    for(int i=0;i<4;i++){
        chars[i].sta=chars[i].cVit*5;
    }*/
}
void turnLeft(){
    if(currentDirection=="north")currentDirection="foo";
        if(currentDirection=="east")currentDirection="north";
    if(currentDirection=="south")currentDirection="east";
    if(currentDirection=="west")currentDirection="south";
    if(currentDirection=="foo")currentDirection="west";

}
void turnRight(){
    turnLeft();
    turnLeft();
    turnLeft();
}
Clickable* getClickTarget(sf::Vector2i pos){
            for(vector<Clickable*>::iterator it=currentRoom->getView(currentDirection)->clickables.begin();
        it!=currentRoom->getView(currentDirection)->clickables.end();it++){
            if(mouseInRegion((*it)->region)) return *it;
        }
        return NULL;
}
void leftClick(sf::Vector2i pos){
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
    }else if (pos.x>1060&&pos.y>310&&pos.y<430){
        camp();
    }else if (pos.x>1140)turnRight();
    else if (pos.x<60)turnLeft();
    else{
        Room *destination=currentRoom;
        string newDirection=currentDirection;
        Clickable *target=getClickTarget(pos);
        if (target!=NULL){
            if(!target->objectType.compare("way on")){
                destination=((WayOn*)target)->destination;
                newDirection=((WayOn*)target)->entryDirection;

            }
            if(!target->objectType.compare("chest")){
                msg.addStatement("You got "+to_string(((Chest*)target)->gold)+" gold!");
                                                    gold+=((Chest*)target)->gold;

                ((Chest*)target)->gold=0;
            }
            if(!target->objectType.compare("lever")){
                destination=&pit;
                msg.addStatement("You fall down a pit trap!");
            }

        }
        currentRoom=destination;
        currentDirection=newDirection;
    }
    
}
void rightClick(sf::Vector2i pos){
            Clickable *target=getClickTarget(pos);
            if(target!=NULL){
                if(target->objectType=="chest"){
                    msg.addStatement("You smash the chest! P1 gets a club!");
                    chars[0].weapon=new Club();
                    store.west=new View();
                }
            }

}

int main(){
    setupRooms();
    setup();


    sf::Clock clock;
    sf::Time elapsed;
    sf::Event event;

    window.setFramerateLimit(20);
    battle.start();
    while (window.isOpen())
    {

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type==sf::Event::MouseButtonPressed&&!inCombat){
                sf::Vector2i pos=sf::Mouse::getPosition(window);
                if(event.mouseButton.button==sf::Mouse::Button::Left)leftClick(pos);
                else rightClick(pos);
            }
        }
                elapsed = clock.getElapsedTime();
        if(elapsed.asSeconds()>0.1){
            clock.restart();
            if(msg.queue.empty()){
                if(inCombat)battle.nextCharacter();
            }else msg.print();

        }

        window.clear();
        window.draw(currentRoom->getView(currentDirection)->sprite);

if(inCombat&&battle.getEnemies().size()){
    window.draw(battle.getEnemies().front()->sprite);
}
    window.draw(*msg.getText());
redrawSidebar();
window.draw(sidebarSprite);
window.draw(compass);
needleDirection(currentDirection);
window.draw(needle);
if(inCombat&&!battle.getEnemies().size())window.draw(blood);

        window.display();
    }

    return 0;
}