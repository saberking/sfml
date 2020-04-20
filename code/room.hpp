#ifndef room
#define room
#include <stdlib.h>
#include<list>
#include<vector>
#include<string>
#include <deque>
#include <SFML/Graphics.hpp>
#include <conio.h>
#include <stdio.h>
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
struct Region fs;
struct Region lft(0, 699, 0, 599);
struct Region leverRegion(100, 400, 400, 800);
Region chestRegion(360,610,400,800);
Region rgt(0, 699, 600, 1199);
struct Room;
struct Clickable{
    Region *region;
    string objectType;
    Clickable(string _type, Region *reg=&fs):objectType{_type}{
        region=reg;
    }
};
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
    std::vector<Clickable *> clickables;
    View(string name){
        texture.loadFromFile("rooms/"+name+".png");
        sprite.setTexture(texture);
    };
    View(){
                texture.loadFromFile("rooms/wall.png");
        sprite.setTexture(texture);
    }
};
struct Room{
    string name;
    bool dangerous=true;
    View *north, *east, *south, *west;
    Monster *resident=NULL;
    Region mapRegion;
    View* getView(string direction){
        if(direction=="north")return north;
        if(direction=="east") return east;
        if(direction=="south")return south;
        return west;
    }
    Room(Region *mr, string _name, string views=""){
        mapRegion=*mr;
        name=_name;
        if(views.find("n")!=string::npos)north=new View(name+"North");
        else north = new View();
        if(views.find("e")!=string::npos)east=new View(name+"East");
        else east=new View();
                if(views.find("s")!=string::npos)south=new View(name+"South");
                else south=new View();
                        if(views.find("w")!=string::npos)west=new View(name+"West");
                        else west=new View();


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

struct Room cell(new Region(14,17,5,8),"cell", "n");
struct Room passage(new Region(11,14, 3, 7),"passage", "nsew");
struct Room store(new Region(8,13,1,4),"store", "we");
struct Room sewer(new Region(8,13,12,16),"sewer", "nesw");
Room bossRoom(new Region(8,13,7,11),"bossRoom", "nesw");
Room pit(new Region(8,13,7,12),"pit","e");
Room river(new Region(5,8,14,16),"river","nesw");
Room changingRoom(new Region(12,16,13,16),"changingRoom","ns");
Room choke(new Region(5,8,12,14),"choke","ew");
Room cave(new Region(5,8,17,23),"cave","nsew");
Room cave2p(new Region(5,8,24,25),"cave2p","nesw");
struct Room *currentRoom;

void setupRooms(){
    currentRoom=&cell;
    cell.north->clickables.push_back(new WayOn(&passage));
    passage.south->clickables.push_back(new WayOn(&cell, "south") );
    passage.north->clickables.push_back(new WayOn(&store, "west", &lft));
    passage.north->clickables.push_back(new WayOn(&bossRoom, "east", &rgt));
    passage.east->clickables.push_back(new WayOn(&bossRoom, "east", &lft));
    passage.east->clickables.push_back(new WayOn(&cell, "south", &rgt));
    passage.west->clickables.push_back(new WayOn(&store,"west",&rgt));
    passage.west->clickables.push_back(new WayOn(&cell, "south", &lft));
    store.east->clickables.push_back(new WayOn(&passage, "east"));
    bossRoom.west->clickables.push_back(new WayOn(&passage, "west"));
    store.west->clickables.push_back(new Chest(10));
    bossRoom.east->clickables.push_back(new Lever("pit trap"));
    pit.east->clickables.push_back(new WayOn(&sewer, "east"));
    sewer.west->clickables.push_back(new WayOn(&pit,"west"));
    sewer.north->clickables.push_back(new WayOn(&river));
    sewer.south->clickables.push_back(new WayOn(&changingRoom, "south"));
    changingRoom.south->clickables.push_back(new Locker());
    changingRoom.north->clickables.push_back(new WayOn(&sewer, "north"));
    sewer.resident=new Rat();
    river.resident=new Fish();
    river.south->clickables.push_back(new WayOn(&sewer, "south"));
    choke.east->clickables.push_back(new WayOn(&river, "east"));
    cave.west->clickables.push_back(new WayOn(&river, "west"));
    cave.east->clickables.push_back(new WayOn(&cave2p,"east",&rgt));
    cave2p.west->clickables.push_back(new WayOn(&cave, "west"));
    cave.resident=new Crab();
    // cave2p.east->clickables.push_back(new WayOn())
}

#endif



