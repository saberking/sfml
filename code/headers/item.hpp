#ifndef ITEM
#define ITEM
#include "includes.hpp"

using namespace std;
struct Item {
    string name;
    string type;
    int weight;
    Item(string _name, string _type, int _weight):weight{_weight}{
        name.assign(_name);
        type.assign(_type);
        tex.loadFromFile("items/"+name+".png");
        pic.setTexture(tex);
    }
    sf::Sprite pic;
    sf::Texture tex;
};
struct Weapon: public Item{
    int att;
    int def;
    Weapon(string n, int a, int d):Item(n, "weapon", 1){
        att=a;
        def=d;
    }
};
struct Club:public Weapon{
    Club():Weapon("club",1, 0){}
};
#endif