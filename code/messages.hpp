#ifndef messages
#define messages
#include <stdlib.h>
#include<list>
#include<vector>
#include<string>
#include <deque>
#include <SFML/Graphics.hpp>
#include <conio.h>
#include <stdio.h>
using namespace std;
extern sf::Font font;

struct StatementBox{
    string statements[7];
    int noOfLines;
    deque<string> queue;
    StatementBox(){
        for(int i =0;i<7;i++){
            statements[i].assign("");
        }
                    noOfLines=0;

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

    };
    void addStatement(string statement){
        queue.push_back(statement);
    };
    void clear(){
noOfLines=0;
                    update();

    };
    void update(){
                string longStatement="";
        for(int i=0;i<noOfLines;i++){
            longStatement+=statements[i]+"\n";
        }
        text.setString(longStatement);

    }
            sf::Clock clock;
    sf::Time elapsed;
    sf::Text *getText(){
                elapsed=clock.getElapsedTime();
        if(elapsed.asSeconds()>3){
            clock.restart();
            clear();
        }
                    return &text;

    };
    void print(){
        if(noOfLines==7){
            for(int i=0;i<6;i++){
                statements[i].assign(statements[i+1]);
            }
            statements[6].assign(queue.front());
        }else{
            statements[noOfLines++].assign(queue.front());
        }
        printf(statements[0].c_str());
        clock.restart();
        queue.pop_front();
        update();
    };
    sf::Text text;

};
extern int gold;

 extern   StatementBox msg;

#endif