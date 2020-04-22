#ifndef ITEM
#define ITEM
#include "includes.hpp"

using namespace std;
struct Item {
    string name;
    string type;
    int weight;
    Item(string _name, string _type, int _weight, int v=0):weight{_weight}, value{v}{
        name.assign(_name);
        type.assign(_type);
        tex.loadFromFile("items/"+name+".png");
        pic.setTexture(tex);
    }
    sf::Sprite pic;
    sf::Texture tex;
    int value;
};
struct Weapon: public Item{
    int att;
    int def;
    Weapon(string n, int a, int d, int v):Item(n, "weapon", 1,v){
        att=a;
        def=d;
    }
};
struct Club:public Weapon{
    Club():Weapon("club",1, 0,0){}
};
struct Bow:public Weapon{
    Bow():Weapon("bow",2,-4,10){}
};
#endif