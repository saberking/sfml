#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include<list>
sf::Font font;
using namespace std;
struct Item {
    string name;
    string type;
    int weight;
    Item(string _name, string _type, int _weight):weight{_weight}{
        name.assign(_name);
        type.assign(_type);
    }
};
    sf::RenderWindow window(sf::VideoMode(1200, 700), "SFML works!");

struct Being {
    int Str;
    int Dex;
    int Int;
    int Vit;
    int cStr;
    int cDex;
    int cInt;
    int cVit;
    int com, ban, mag;
    int sta;
    list<Item> stuff;
    string name;
    Being(string _name){
        Str=1;
        Dex=1;
        Int=1;
        Vit=1;
        cStr=1;
        cDex=1;
        cInt=1;
        cVit=1;
        com=0;
        ban=0;
        mag=0;
        name=_name;
        sta=Vit*5;
    }
};
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
    return rand()%6<a.Dex;
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
    string message=attacker->name+" attacks "+defender->name+".";
    int dam=attackRoll(*attacker, *defender);
    if(dam<1){
        message+=" Missed!";
        if(!checkBalance(*attacker))message+=" "+attacker->name+" falls over!";
    }else{
        dam*=attacker->Str;
        defender->sta-=dam;
        message+=" "+to_string(dam)+" stamina lost.";
    }
    msg.addStatement(message);
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
        if(elapsed.asSeconds()>1){
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