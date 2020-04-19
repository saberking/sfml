#include <stdlib.h>
#include<list>
#include<vector>
#include<string>
#include <deque>
#include <SFML/Graphics.hpp>
#include <conio.h>
#include <stdio.h>

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