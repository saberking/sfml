#include "headers/room.hpp"
struct Room cell(new Region(14,17,5,8),"cell", "n");
struct Room passage(new Region(11,14, 3, 7),"passage", "nsew");
struct Room store(new Region(8,13,1,4),"store", "e");
struct Room sewer(new Region(8,13,12,16),"sewer", "nesw");
Room bossRoom(new Region(8,13,7,11),"bossRoom", "nesw");
Room pit(new Region(8,13,7,12),"pit","e");
Room river(new Region(5,8,14,16),"river","nesw");
Room changingRoom(new Region(12,16,13,16),"changingRoom","ns");
Room choke(new Region(5,8,12,14),"choke","ew");
Room cave(new Region(5,8,17,23),"cave","nsew");
Room cave2p(new Region(5,8,24,25),"cave2p","nesw");
Room cave3(new Region(2,5, 25,28),"cave3","ns","caveWall");
Room cave4(new Region(8,11,25,28),"cave4","ns","caveWall");
struct Room *currentRoom;
    struct Region fs(0,699,0,1199);
    struct Region lft(0, 699, 0, 599);
    struct Region leverRegion(100, 400, 400, 800);
    Region chestRegion(360,610,400,800);
    Region rgt(0, 699, 600, 1199);

void setupRooms(){

    currentRoom=&cave;
    cell.north->clickables.push_back(new WayOn(&passage));
    passage.south->clickables.push_back(new WayOn(&cell, "south", &fs) );
    passage.north->clickables.push_back(new WayOn(&store, "west", &lft));
    passage.north->clickables.push_back(new WayOn(&bossRoom, "east", &rgt));
    passage.east->clickables.push_back(new WayOn(&bossRoom, "east", &lft));
    passage.east->clickables.push_back(new WayOn(&cell, "south", &rgt));
    passage.west->clickables.push_back(new WayOn(&store,"west",&rgt));
    passage.west->clickables.push_back(new WayOn(&cell, "south", &lft));
    store.east->clickables.push_back(new WayOn(&passage, "east",&fs));
    bossRoom.west->clickables.push_back(new WayOn(&passage, "west",&fs));
    store.west->clickables.push_back(new Chest(10));
    bossRoom.east->clickables.push_back(new Lever("pit trap"));
    pit.east->clickables.push_back(new WayOn(&sewer, "east", &fs));
    sewer.west->clickables.push_back(new WayOn(&pit,"west", &fs));
    sewer.north->clickables.push_back(new WayOn(&river));
    sewer.south->clickables.push_back(new WayOn(&changingRoom, "south", &fs));
    changingRoom.south->clickables.push_back(new Locker());
    changingRoom.north->clickables.push_back(new WayOn(&sewer, "north", &fs));
    sewer.resident=new Rat();
    river.resident=new Fish();
    river.south->clickables.push_back(new WayOn(&sewer, "south", &fs));
    choke.east->clickables.push_back(new WayOn(&river, "east", &fs));
    cave.west->clickables.push_back(new WayOn(&river, "west", &fs));
    cave.east->clickables.push_back(new WayOn(&cave2p,"east",&rgt));
    cave2p.west->clickables.push_back(new WayOn(&cave, "west", &fs));
    cave2p.east->clickables.push_back(new WayOn(&cave3, "north",&lft));
    cave2p.east->clickables.push_back(new WayOn(&cave4, "south",&rgt));
    cave2p.north->clickables.push_back(new WayOn(&cave,"west",&lft));
    cave2p.north->clickables.push_back(new WayOn(&cave3,"north",&rgt));
    cave2p.south->clickables.push_back(new WayOn(&cave4,"south",&lft));
    cave2p.south->clickables.push_back(new WayOn(&cave,"west",&rgt));
    cave3.south->clickables.push_back(new WayOn(&cave2p, "south", &fs));
    cave4.north->clickables.push_back(new WayOn(&cave2p, "north", &fs));
    cave3.north->clickables.push_back(new Chest(10));

    cave2p.resident=new Spider();
    cave.resident=new Crab();
}
