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

struct Being {
    int Str;
    int Dex;
    int Int;
    int Vit;
    int cStr;
    int cDex;
    int cInt;
    int cVit;
    list<Item> stuff;
    Being(){
        Str=1;
        Dex=1;
        Int=1;
        Vit=1;
        cStr=1;
        cDex=1;
        cInt=1;
        cVit=1;
    }
};
void setup(){

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
    StatementBox msg;
int noOfPlayers=5;
int currentPlayer=1;
void nextCharacter(){
    currentPlayer++;
    if(currentPlayer>noOfPlayers)currentPlayer=1;

    msg.addStatement(currentPlayer<=4?"Player " +to_string(currentPlayer)+" attacks. Missed!" :"Goblin attacks. Missed!");
}

int main()
{
    font.loadFromFile("fonts/thestrong.ttf");

sf::Texture texture, ch1t, ch2t, ch3t, ch4t;
    texture.loadFromFile("Gob.png");
    sf::Sprite sprite;
sprite.setTexture(texture);
    ch1t.loadFromFile("pics/ch1.png");
    sf::Sprite ch1;
ch1.setTexture(ch1t);
ch1.setPosition(sf::Vector2f(900.f, 100.f));
ch1.setScale(sf::Vector2f(0.75f, 0.75f));
    ch2t.loadFromFile("pics/ch2.png");
    sf::Sprite ch2;
ch2.setTexture(ch2t);
ch2.setPosition(sf::Vector2f(900.f, 250.f));
ch2.setScale(sf::Vector2f(0.75f, 0.75f));
    ch3t.loadFromFile("pics/ch3.png");
    sf::Sprite ch3;
ch3.setTexture(ch3t);
ch3.setPosition(sf::Vector2f(900.f, 400.f));
ch3.setScale(sf::Vector2f(0.75f, 0.75f));

    ch4t.loadFromFile("pics/ch4.png");
    sf::Sprite ch4;
ch4.setTexture(ch4t);
ch4.setPosition(sf::Vector2f(900.f, 550.f));
ch4.setScale(sf::Vector2f(0.75f, 0.75f));

    sf::RenderWindow window(sf::VideoMode(1200, 700), "SFML works!");

sf::Clock clock;
sf::Time elapsed;
window.setFramerateLimit(20);
    while (window.isOpen())
    {
        elapsed = clock.getElapsedTime();
        if(elapsed.asSeconds()>1){
            clock.restart();
            nextCharacter();
        }
        sf::Event event;
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