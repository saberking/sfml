#include <stdlib.h>
#include<list>
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
    int com, ban, mag;
    int sta;
    list<Item> stuff;
    string name;
    bool standing;
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
        standing=true;
    }
};