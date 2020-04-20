#ifndef being


#include <stdlib.h>
#include<list>
#include<vector>
#include<string>
#include <deque>
#include <SFML/Graphics.hpp>
#include <conio.h>
#include <stdio.h>
#include "item.hpp"

using namespace std;
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
    bool hostile;
    list<Item> stuff;
    string name;
    bool standing;
    sf::Sprite sprite;
    sf::Texture texture;
    Weapon *weapon;
    void resizeTexture(float x, float y){
                sprite.setScale(sf::Vector2f(x, y));
    }
    Being(string _name, bool _hostile=false){
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
        standing=true;
        hostile=_hostile;
        texture.loadFromFile("pics/"+name+".png");
        sprite.setTexture(texture);
        weapon=NULL;
    }
    int getAttackBonus(){
        return cDex+com+(weapon==NULL?0:weapon->att);
    }
    int getDefenceBonus(){
        return cDex+com+(weapon==NULL?0:weapon->def);
    }
    ~Being(){}
};
struct Monster:public Being{
    int gold;
    Monster(string _name, int g):Being(_name, true){
        gold=g;
    }
};
struct Goblin:public Monster{
    Goblin():Monster("gob", 10){

    }
};
struct Fish:public Monster{
    Fish():Monster("fish", 0){}
};
struct Rat:public Monster{
    Rat():Monster("rat", 0){}
};
struct Security:public Monster{
    Security():Monster("security", 20){}
};
struct Crab:Monster{
    Crab():Monster("crab", 0){};
};
struct Spider:Monster{
    Spider():Monster("spider", 0){}
};
extern Being p1, p2, p3, p4;
extern Being chars[4];

#define being
#endif