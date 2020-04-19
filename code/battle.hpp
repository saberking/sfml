#include <stdlib.h>
#include<list>
#include<vector>
#include<string>
#include <deque>
#include <SFML/Graphics.hpp>
#include <conio.h>
#include <stdio.h>

struct Battle{
    list<Being *> combatants;
    list<Being *>::iterator current;
    vector<Being *> monsters;
    void end(){
        inCombat=false;
        for(list<Being*>::iterator it=combatants.begin();it!=combatants.end();it++){
            (*it)->standing=true;
        }
        for(vector<Being*>::iterator it=monsters.begin();it!=monsters.end();it++){
            delete (*it);
        }
        currentRoom->resident=NULL;
    }
    void start(Monster *mon){
        monsters.clear();
        monsters.push_back(mon);
        inCombat=true;
        combatants.clear();
        for(int i=0;i<4;i++){
            if(chars[i].sta>0)combatants.push_back(&chars[i]);
        }
        combatants.push_back(mon);
        current=combatants.end();
    };
    vector<Being*> getEnemies(){
        vector<Being*> vec;
                for (list<Being*>::iterator it=combatants.begin();it!=combatants.end();it++){
            if((*it)->hostile)vec.push_back(*it);
        }
        return vec;
    }
    vector<Being*>getFriends(){
                vector<Being*> vec;

                for (list<Being*>::iterator it=combatants.begin();it!=combatants.end();it++){
            if(!(*it)->hostile)vec.push_back(*it);
        }
        return vec;
    }
    void nextCharacter(){
        if(current==combatants.end()||++current==combatants.end()){
            current=combatants.begin();
        }   
        vector<Being*>friends=getFriends();
        vector<Being*>enemies=getEnemies();
        Being *defender;
        printf("%s's turn!!enemies:%d,frieds:&d,combatants:%d",(*current)->name.c_str(),enemies.size(),friends.size(),combatants.size());
        if(enemies.size()){
            if(!(*current)->hostile){
                defender=enemies[0];
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
                                if((*current)->hostile){
                                    Monster *m=(Monster*)(*current);
                                    addGold(m->gold);
                                }
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
                        if(defender->hostile){
                                                                Monster *m=(Monster*)(defender);
                                    addGold(m->gold);
                        }
                        combatants.remove(defender);
                    }
                    else if(defender->sta<defender->cVit*2.5) msg.addStatement(defender-> name+ " is winded.");
                }
            }else{
                msg.addStatement((*current)->name+" stands up!");
                (*current)->standing=true;
            }

        }else {
            msg.addStatement("You have defeated the enemies!");
            end();
        }
 
    };
    int attackRoll(Being &a, Being &d){
        int att=rand()%6+a.getAttackBonus();
        int def=rand()%6+d.getDefenceBonus();
        if(!d.standing)def-=4;
        return att-def;
    }

    bool checkBalance(Being &a){
        bool bal= rand()%6<a.Dex;
        if(!bal) a.standing=false;
        return bal;
    }
};
    Battle battle;
