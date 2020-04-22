#ifndef room
#define room

#include "being.hpp"

using namespace std;

struct Region{
    int top;
    int bottom;
    int left;
    int right;
    sf::Vector2f centre(){
        return sf::Vector2f((left+right)/2,(top+bottom)/2);
    };
    Region(int _top=0, int _bottom=699,int _left=0, int _right=1199){
        top=_top;
        bottom=_bottom;
        left=_left;
        right=_right;
    }
};

struct Room;
struct Clickable{
    Region *region;
    string objectType;
    Clickable(string _type, Region *reg):objectType{_type}{
        region=reg;
    }
};
extern Region chestRegion;
extern Region leverRegion;
extern Region fs;
struct Locker:public Clickable{
    bool full=true;
    Locker():Clickable("locker", &chestRegion){};
};
struct Lever:public Clickable{
    string leverType;
    Lever(string _levertype):Clickable("lever",&leverRegion){
        leverType=_levertype;
    }
};
struct WayOn:public Clickable{
    Room *destination;
    string entryDirection="north";
    WayOn(Room *dest, string dir="north", Region *reg=&fs):Clickable("way on", reg){
        destination=dest;
        entryDirection=dir;

    }
};
struct Chest:public Clickable{
    int gold;
    Chest(int g):Clickable("chest", &chestRegion){gold=g;};
};
struct View{
    sf::Sprite sprite;
    sf::Texture texture;
    std::list<Clickable *> clickables;
    View(string name){
        texture.loadFromFile("rooms/"+name+".png");
        sprite.setTexture(texture);
    };
};
struct Room{
    int map=0;
    string name;
    bool dangerous=true;
    View *north, *east, *south, *west;
    Monster *resident=NULL;
    Region mapRegion;
            bool visited=false;
    deque<string> welcomeText;
    Item *item=NULL;
    View* getView(string direction){
        if(direction=="north")return north;
        if(direction=="east") return east;
        if(direction=="south")return south;
        return west;
    }
    Room(Region *mr, string _name, string views="", string typ="wall", int level=1, deque<string> welcome={}){
        mapRegion=*mr;
        name=_name;
        welcomeText=welcome;
        map=level;
        if(views.find("n")!=string::npos)north=new View(name+"North");
        else north = new View(typ);
        if(views.find("e")!=string::npos)east=new View(name+"East");
        else east=new View(typ);
                if(views.find("s")!=string::npos)south=new View(name+"South");
                else south=new View(typ);
                        if(views.find("w")!=string::npos)west=new View(name+"West");
                        else west=new View(typ);


    };
    ~Room(){
        delete north;
        delete east;
        delete south;
        delete west;
    }


    bool hasView(string direction){
        if(direction=="north")return (bool)north;
        if(direction=="east")return (bool)east;
        if(direction=="south")return (bool)south;
        return (bool)west;
    }

};

extern struct Room cell;
extern struct Room passage;
extern struct Room store;
extern struct Room sewer;
extern Room bossRoom;
extern Room pit;
extern Room river;
extern Room changingRoom;
extern Room choke;
extern Room cave2p;
extern Room cave3;
extern Room cave4;
extern struct Room *currentRoom;
#endif



