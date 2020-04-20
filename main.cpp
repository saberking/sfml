 #include <SFML/Graphics.hpp>
#include <stdlib.h>
#include<list>
#include<deque>

#include "code/messages.hpp"
#include "code/battle.hpp"
#include "code/map.hpp"
#include "code/util.hpp"
Being p1("ch1"), p2("ch2"), p3("ch3"), p4("ch4");
Being chars[4]={p1,p2,p3,p4};
Battle battle;
StatementBox msg;
Map mapp;
int gold=0;
sf::Font font;
float turnLength=0.7;
  std::string currentDirection;

 sf::RenderWindow window(sf::VideoMode(1200, 700), "Gob");



 sf::RenderTexture monsters;
 sf::Text goldText;
 sf::Sprite minimap,blood, sidebarSprite, compass, needle, bag, tent,needle2;
 sf::Texture minimapt,bloodt, compasst, needlet, bagt, tentt;
 sf::RenderTexture sidebar;
sf::Sprite fireball, chest;
sf::Texture fireballt, chestt;

void redrawSidebar(){
    sidebar.clear( sf::Color(0, 0, 0, 0));
    goldText.setString(to_string(gold));
    sf::RectangleShape highlight;
    highlight.setSize(sf::Vector2f(56.f,56.f));
    highlight.setFillColor(sf::Color(100,100,50,255));
    if(battle.inCombat){
        // for(int i=0;i<4;i++){
        //     if(chars[i].sta>0){
        //         if(battle.fireball[i]){
        //             highlight.setPosition(sf::Vector2f(127.f, (float)197+120*i));
        //                             sidebar.draw(highlight);

        //         }
        //         fireball.setPosition(sf::Vector2f(130.f,200+120*i));
        //         sidebar.draw(fireball);
        //     }
            
        // }
    }else{
           
    }
     sidebar.draw(bag);

        sidebar.draw(goldText);
        sidebar.draw(tent);
        sidebar.draw(minimap);
    for(int i = 0;i<4;i++){
        if(chars[i].sta>0){
            sidebar.draw(chars[i].sprite);
            sf::RectangleShape rect;
            float fraction=((float)chars[i].sta)/((float)(chars[i].cVit*5));
                    rect.setSize(sf::Vector2f(10.f, fraction*106));
        rect.setFillColor(sf::Color(70,70,55,230));
        rect.setPosition(sf::Vector2f(110.f,(float)200+120*i+106*(1-fraction)));
            sidebar.draw(rect);
        }
    }

    sidebar.display();
sidebarSprite.setTexture(sidebar.getTexture());
sidebarSprite.setPosition(900.f,0.f);
}


void setup(){
    battle.createTexture();
    mapp.reveal(&cell);

    srand(time(NULL));
        font.loadFromFile("fonts/thestrong.ttf");
    for(int i=0;i<4;i++){
        chars[i].sprite.setPosition(sf::Vector2f(0.f, (float)200+120*i));
        chars[i].resizeTexture(0.5f,0.5f);
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
    needle.setOrigin(59.f,59.f);
    needle2.setTexture(needlet);
    needle2.setScale(sf::Vector2f(0.5f,0.5f));
    needle2.setOrigin(59.f,59.f);
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
    minimapt.loadFromFile("other/minimap.png");
    minimap.setTexture(minimapt);
    minimap.setPosition(sf::Vector2f(170.f,190.f));
    fireballt.loadFromFile("other/fireball.png");
    fireball.setTexture(fireballt);
    chestt.loadFromFile("objects/chest.png");
    chest.setTexture(chestt);
}
bool isThereAChest(){
    View* view=currentRoom->getView(currentDirection);
    for(vector<Clickable*>::iterator it=view->clickables.begin();it!=view->clickables.end();it++){
        if((*it)->objectType=="chest"){
            return true;
        }
    }
    return false;
}


void drawWindow(){
            window.clear();
        window.draw(currentRoom->getView(currentDirection)->sprite);
        if(isThereAChest()){
            window.draw(chest);
        }
        if(battle.inCombat){
            window.draw(battle.sprite);

        }else{

        }
                    window.draw(compass);
            needleDirection(currentDirection,needle);
            window.draw(needle);
        window.draw(*msg.getText());
        redrawSidebar();
        window.draw(sidebarSprite);

        if(battle.inCombat&&!battle.getEnemies().size())window.draw(blood);
        if(mapp.visible){
            window.draw(mapp.getSprite());
            sf::Vector2f centre=currentRoom->mapRegion.centre();
            centre.x*=40;centre.x+=40;
            centre.y*=40;centre.y+=40;
            needle2.setPosition(centre);
            needleDirection(currentDirection,needle2);
            window.draw(needle2);
        }
        window.display();
}


int main(){
    setupRooms();
    setup();


    sf::Clock clock;
    sf::Time elapsed;
    sf::Event event;

    window.setFramerateLimit(20);
    while (window.isOpen())
    {

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type==sf::Event::MouseButtonPressed){
                sf::Vector2i pos=sf::Mouse::getPosition(window);
                if(!battle.inCombat){
                    if(event.mouseButton.button==sf::Mouse::Button::Left)leftClick(pos);
                    else rightClick(pos);
                }else{
                    // if(pos.x>1030&&pos.x<1080){
                    //     for(int i=0;i<4;i++){
                    //         if(pos.y>=200+120*i&&pos.y<250+120*i){
                    //             printf("bar\n");
                    //             battle.fireball[i]=!battle.fireball[i];
                    //         }

                    //     }
                    // }
                }
            }
        }
        if(!battle.inCombat&&currentRoom->resident!=NULL){
            battle.start(currentRoom->resident);
        }
                elapsed = clock.getElapsedTime();
        if(elapsed.asSeconds()>turnLength){
            clock.restart();
            if(msg.queue.empty()){
                if(battle.inCombat)battle.nextCharacter();
            }else msg.print();

        }

        drawWindow();
    }

    return 0;
}