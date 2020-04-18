#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include<list>
#include "structs.hpp"
sf::Font font;

    sf::RenderWindow window(sf::VideoMode(1200, 700), "SFML works!");


Being p1("p1"), p2("p2"), p3("p3"), p4("p4"), goblin("goblin");
Being chars[4]={p1,p2,p3,p4};
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
int attackRoll(Being &a, Being &d){
    int att=rand()%6+a.com+a.Dex;
    int def=rand()%6+d.com+d.Dex;
    if(!d.standing)def-=4;
    return att-def;
}
struct StatementBox{
    string statements[7];
    int noOfLines;
    StatementBox(){
        for(int i =0;i<7;i++){
            statements[i].assign("");
            noOfLines=0;
        }
        // select the font
text.setFont(font); // font is a sf::Font

// set the string to display

// set the character size
text.setCharacterSize(24); // in pixels, not points!

// set the color
text.setFillColor(sf::Color::Red);

// set the text style
text.setStyle(sf::Text::Bold | sf::Text::Underlined);
text.setPosition(sf::Vector2f(100.f, 500.f));
addStatement("You are attacked by an unarmed goblin!");

    };
    void addStatement(string statement){
        if(noOfLines==7){
            for(int i=0;i<6;i++){
                statements[i].assign(statements[i+1]);
            }
            statements[6].assign(statement);
        }else{
            statements[noOfLines++].assign(statement);
        }
        string longStatement="";
        for(int i=0;i<7;i++){
            longStatement+=statements[i]+"\n";
        }
        text.setString(longStatement);
    };
    sf::Text text;
};
bool checkBalance(Being &a){
    bool bal= rand()%6<a.Dex;
    if(!bal) a.standing=false;
    return bal;
}
    StatementBox msg;
int noOfPlayers=5;
int currentPlayer=1;
void nextCharacter(){
    currentPlayer++;
    if(currentPlayer>noOfPlayers)currentPlayer=1;
    Being *attacker, *defender;
    if(currentPlayer<5){
        attacker=&chars[currentPlayer-1];
        defender=&goblin;
    }else{
        attacker=&goblin;
        defender=&chars[rand()%4];
    }
    if(attacker->sta<=0) msg.addStatement(attacker->name+ " is unconscious!");
    else if(attacker->standing){
        string message=attacker->name+" attacks "+defender->name+".";
        if(!defender->standing){
            msg.addStatement(message);
            message=defender->name+ " is lying on the floor!";
        }
        int dam=attackRoll(*attacker, *defender);
        if(dam<1){
            message+=" Missed!";
            if(!checkBalance(*attacker)){
                int loss=rand()%5+1;
                msg.addStatement(message);
                message=attacker->name+" falls over! "+to_string(loss)+" stamina lost.";
                attacker->sta-=loss;
                    msg.addStatement(message);

            }
        }else{
            dam*=attacker->Str;
            defender->sta-=dam;
            message+=" "+to_string(dam)+" stamina lost.";
            msg.addStatement(message);
            if(defender->sta<=0) msg.addStatement(defender->name+ " falls unconscious!");
            else if(defender->sta<defender->cVit*2.5) msg.addStatement(defender-> name+ " is winded.");
        }
    }else{
        msg.addStatement(attacker->name+" stands up!");
        attacker->standing=true;
    }

}

int main()
{
setup();


sf::Clock clock;
sf::Time elapsed;
        sf::Event event;

window.setFramerateLimit(20);
    while (window.isOpen())
    {
        elapsed = clock.getElapsedTime();
        if(elapsed.asSeconds()>2){
            clock.restart();
            nextCharacter();
        }
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
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