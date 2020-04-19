#include <stdlib.h>
#include<list>
#include<vector>
#include<string>
#include <deque>
#include <SFML/Graphics.hpp>
#include <conio.h>
#include <stdio.h>

using namespace std;
bool inCombat=true, hostility=true;
struct Item {
    string name;
    string type;
    int weight;
    Item(string _name, string _type, int _weight):weight{_weight}{
        name.assign(_name);
        type.assign(_type);
    }
};
struct Region{
    int top;
    int bottom;
    int left;
    int right;
    Region(int _top=0, int _bottom=699,int _left=0, int _right=1199){
        top=_top;
        bottom=_bottom;
        left=_left;
        right=_right;
    }
};
struct Region fs;
struct Region left(0, 699, 0, 599);
Region right(0, 699, 600, 1199);
struct Room;
struct Clickable{
    Region region;
    string objectType;
    Clickable(string _type):objectType{_type}{
        region=fs;
        printf("Foo");
    }
};
struct WayOn:public Clickable{
    Room *destination;
    string entryDirection="north";
    WayOn():Clickable("way on"){};
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
                texture.loadFromFile("rooms/cellEast.png");
        sprite.setTexture(texture);
    }
};
WayOn cellArch, passageSouth;
struct Room{
    string name;
    View *north, *east, *south, *west;
    View* getView(string direction){
        if(direction=="north")return north;
        if(direction=="east") return east;
        if(direction=="south")return south;
        return west;
    }
    Room(string _name, string views="n"){
        name=_name;
        north=new View(name+"North");
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
struct Room cell("cell", "e");
struct Room passage("passage", "s");
struct Room *currentRoom;
void setupRooms(){
    currentRoom=&cell;
    cellArch.destination=&passage;
    cell.north->clickables.push_back(&cellArch);
    passageSouth.destination=&cell;
    passageSouth.entryDirection="south";
    passage.south->clickables.push_back(&passageSouth);
}
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
    }
};
Being p1("ch1"), p2("ch2"), p3("ch3"), p4("ch4"), goblin("gob", true);
Being chars[4]={p1,p2,p3,p4};

sf::Font font;

struct StatementBox{
    string statements[7];
    int noOfLines;
    deque<string> queue;
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
        queue.push_back(statement);
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
        queue.pop_front();
        string longStatement="";
        for(int i=0;i<7;i++){
            longStatement+=statements[i]+"\n";
        }
        text.setString(longStatement);
    };
    sf::Text text;
};
    StatementBox msg;

struct Battle{
    list<Being *> combatants;
    list<Being *>::iterator current;
    Battle(){
        for(int i=0;i<4;i++){
            combatants.push_back(&chars[i]);
        }
        combatants.push_back(&goblin);
        current=combatants.end();
    };

    void nextCharacter(){
        if(current==combatants.end()||++current==combatants.end()){
            current=combatants.begin();
        }   
        vector<Being*>friends;
        vector<Being*>enemies;
        Being *defender;
        for (list<Being*>::iterator it=combatants.begin();it!=combatants.end();it++){
            if((*it)->hostile)enemies.push_back(*it);
            else friends.push_back(*it);
        }
        if(enemies.size()){
            if(!(*current)->hostile){
                defender=&goblin;
            }else{
                defender=friends.at(rand()%friends.size());
            }
            if((*current)->standing){
                string message=(*current)->name+" attacks "+defender->name+".";
                if(!defender->standing){
                    msg.addStatement(message);
                    message=defender->name+ " is lying on the floor!";
                }
                int dam=attackRoll(*(*current), *defender);
                if(dam<1){
                    message+=" Missed!";
                    if(!checkBalance(*(*current))){
                        int loss=rand()%5+1;
                        msg.addStatement(message);
                        message=(*current)->name+" falls over! "+to_string(loss)+" stamina lost.";
                        (*current)->sta-=loss;
                            msg.addStatement(message);
                            if((*current)->sta<=0){
                                msg.addStatement((*current)->name+" falls unconscious!");
                                Being *toDelete=*current;
                                if(current==combatants.begin()){
                                    current=--combatants.end();
                                }else current--;

                                combatants.remove(toDelete);
                            }
                    }
                }else{
                    dam*=(*current)->Str;
                    defender->sta-=dam;
                    message+=" "+to_string(dam)+" stamina lost.";
                    msg.addStatement(message);
                    if(defender->sta<=0){
                        msg.addStatement(defender->name+ " falls unconscious!");
                        combatants.remove(defender);
                    }
                    else if(defender->sta<defender->cVit*2.5) msg.addStatement(defender-> name+ " is winded.");
                }
            }else{
                msg.addStatement((*current)->name+" stands up!");
                (*current)->standing=true;
            }

        }else {
            msg.addStatement("You have defeated the goblin!");
            hostility=false;
        }
 
    };
    int attackRoll(Being &a, Being &d){
        int att=rand()%6+a.com+a.Dex;
        int def=rand()%6+d.com+d.Dex;
        if(!d.standing)def-=4;
        return att-def;
    }

    bool checkBalance(Being &a){
        bool bal= rand()%6<a.Dex;
        if(!bal) a.standing=false;
        return bal;
    }
};
