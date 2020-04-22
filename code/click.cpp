
#include "headers/messages.hpp"
#include "headers/battle.hpp"
#include "headers/map.hpp"
#include "headers/util.hpp"
extern string mode;
extern Room cave;
void camp(){
    if(rand()%2){
        for(int i=0;i<4;i++){
            chars[i].standing=false;
        }
        battle.start(new Goblin());
    }else

    for(int i=0;i<4;i++){
        chars[i].sta=chars[i].cVit*5;
        chars[i].standing=true;
    }
}
void turnLeft(){
    if(currentDirection=="north")currentDirection="foo";
        if(currentDirection=="east")currentDirection="north";
    if(currentDirection=="south")currentDirection="east";
    if(currentDirection=="west")currentDirection="south";
    if(currentDirection=="foo")currentDirection="west";

}
void turnRight(){
    turnLeft();
    turnLeft();
    turnLeft();
}
bool mouseInRegion(Region *region){
    sf::Vector2i pos=sf::Mouse::getPosition(window);
    return pos.x>=region->left && pos.x<=region->right&&pos.y>=region->top&&pos.y<=region->bottom;
}
Clickable* getClickTarget(sf::Vector2i pos){
            for(list<Clickable*>::iterator it=currentRoom->getView(currentDirection)->clickables.begin();
        it!=currentRoom->getView(currentDirection)->clickables.end();it++){
            if(mouseInRegion((*it)->region)) return *it;
        }
        return NULL;
}



void setDirection(string direction){
    if(currentRoom->hasView(direction))
    currentDirection=direction;
}
void needleDirection(string direction, sf::Sprite &n){
    if(direction=="north")n.setRotation(0);
        if(direction=="east")n.setRotation(90);
            if(direction=="south")n.setRotation(180);
    if(direction=="west")n.setRotation(270);


}
void leftClick(sf::Vector2i pos){
    if(mode=="inventory"){
        mode="main";
        return;
    }
    if(mapp.visible){
        mapp.visible=false;
        return;
    }
    if(pos.x>1060&&pos.y>560){
        if(pos.y-620>pos.x-1120){
            if(pos.y-620<1120-pos.x){
                setDirection("west");
            }else{
                setDirection("south");
            }
        }else{
            if(pos.y-620<1120-pos.x){
                setDirection("north");
            }else{
                setDirection("east");
            }
        }
    }else if (pos.x>1060&&pos.y>310&&pos.y<430){
        camp();
    }else if(pos.x>1060&&pos.y>190&&pos.y<310){
        mapp.visible=true;
    }
    else if (pos.x>1140)turnRight();
    else if (pos.x<60)turnLeft();
    else if(pos.x>900&&pos.x<1020&&pos.y>200&&pos.y<680){
        mode="inventory";
    }
    else{
        Room *destination=currentRoom;
        string newDirection=currentDirection;
        Clickable *target=getClickTarget(pos);
        if (target!=NULL){
            if(!target->objectType.compare("way on")){
                destination=((WayOn*)target)->destination;
                newDirection=((WayOn*)target)->entryDirection;
            }
            if(!target->objectType.compare("chest")){
                msg.addStatement("You got "+to_string(((Chest*)target)->gold)+" gold!");
                                                    gold+=((Chest*)target)->gold;

                ((Chest*)target)->gold=0;
            }
            if(!target->objectType.compare("lever")){
                destination=&pit;
                msg.addStatement("You fall down a pit trap!");
            }
            if(!target->objectType.compare("locker")){
                if(((Locker*)target)->full)
                msg.addStatement("You get 4 wetsuits!");
                ((Locker*)target)->full=false;
                sewer.resident=new Security();
                river.east->clickables.push_back(new WayOn(&cave, "east"));
                river.west->clickables.push_back(new WayOn(&choke, "west"));
            }
        }
        if(destination!=currentRoom){
                            mapp.reveal(destination);
        currentRoom=destination;
        if(!currentRoom->visited){
            currentRoom->visited=true;
            if(!currentRoom->welcomeText.empty()){
                msg.addStatement(currentRoom->welcomeText);
            }
        }

        }
        currentDirection=newDirection;
    }
    
}
void rightClick(sf::Vector2i pos){
            Clickable *target=getClickTarget(pos);
            if(target!=NULL){
                if(target->objectType=="chest"){
                    msg.addStatement("You smash the chest!");
                    currentRoom->getView(currentDirection)->clickables.remove(target);

                    for(int i=0;i<4;i++){
                        if(chars[i].weapon==NULL){
                            msg.addStatement("P"+to_string(i+1)+" gets a club!");
                            chars[i].weapon=new Club();
                        }
                    }

                }
            }

}