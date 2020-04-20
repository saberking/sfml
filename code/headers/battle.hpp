#ifndef BATTLE
#define BATTLE
#include <stdlib.h>
#include<list>
#include<vector>
#include<string>
#include <deque>
#include <SFML/Graphics.hpp>
#include <conio.h>
#include <stdio.h>
#include "being.hpp"
#include "room.hpp"
#include "messages.hpp"

struct Battle{
    list<Being *> combatants;
    list<Being *>::iterator current;
    vector<Being *> monsters;
    sf::RenderTexture tex;
    sf::Sprite sprite;
    bool inCombat;
    bool fireball[4];
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
            fireball[i]=false;
        }
        combatants.push_back(mon);
        current=combatants.end();
        tex.clear( sf::Color(0, 0, 0, 0));
        tex.draw(monsters.front()->sprite);
        tex.display();
        sprite.setTexture(tex.getTexture());
        msg.clear();
        msg.addStatement("You are attacked by a "+mon->name+"!");
        msg.addStatement("");
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
    void castSpell(Being &a, Being &d){
        msg.addStatement(a.name+" casts fireball at "+d.name);
        int castingCost=rand()%6;
        castingCost-=a.cInt;
        if(castingCost<1)castingCost=1;
        if(castingCost<=a.sta){
            int dam=(rand()%6)*a.cInt;
            d.sta-=dam;
            msg.addStatement(to_string(dam)+" stamina lost!");
        }else {
            msg.addStatement("Spell fizzles!");
        }
        a.sta-=castingCost;
    }
    void ko(void *a){
                                msg.addStatement(((Being*)a)->name+" falls unconscious!");
                                if(((Being*)a)->hostile&&((Monster*)a)->gold){
                                    gold+=(((Monster*)a)->gold);
                                    msg.addStatement("You got some gold!");
                                }
                                Being *toDelete=(Being*)a;
                                if(a==*current){
                                    if(current==combatants.begin()){
                                        current=--combatants.end();
                                    }else current--;
                                }
                                combatants.remove(toDelete);
    }
    void attack(Being &a, Being &d){
                string message=a.name+" attacks "+d.name+".";
                if(!d.standing){
                    msg.addStatement(message);
                    message=d.name+ " is lying on the floor!";
                }
                int dam=attackRoll(a, d);
                if(dam<1){
                    message+=" Missed!";
                    if(!checkBalance(a)){
                        int loss=rand()%5+1;
                        msg.addStatement(message);
                        message=a.name+" falls over! "+to_string(loss)+" stamina lost.";
                        a.sta-=loss;
                            msg.addStatement(message);
  
                    }
                }else{
                    dam*=a.Str;
                    d.sta-=dam;
                    message+=" "+to_string(dam)+" stamina lost.";
                    msg.addStatement(message);

                }

    }
    void nextCharacter(){
        if(current==combatants.end()||++current==combatants.end()){
            current=combatants.begin();
        }   
        vector<Being*>friends=getFriends();
        vector<Being*>enemies=getEnemies();
        Being *defender;
        if(enemies.size()){
            if(!(*current)->hostile){
                defender=enemies[0];
            }else{
                defender=friends.at(rand()%friends.size());
            }
            if((*current)->standing){
                bool f=false;
                // if(!(*current)->hostile){
                //     for(int i=0;i<4;i++){
                //         if(*current==&chars[i]){
                //             if(fireball[i]){
                //                 f=true;
                //                 fireball[i]=false;
                //             }
                //         }
                //     }
                // }
                // else 
                if(rand()%2){
                    f=true;
                }
                if(f){
                    castSpell(**current, *defender);
                }else{
                    attack(**current, *defender);
                }
            }else{
                msg.addStatement((*current)->name+" stands up!");
                (*current)->standing=true;
            }
            list<Being*>knockouts(combatants.size());
            auto it=copy_if(combatants.begin(),combatants.end(),knockouts.begin(), [](Being *b){return b->sta<=0;});
            knockouts.resize(distance(knockouts.begin(), it));

            for(list<Being*>::iterator it=knockouts.begin();it!=knockouts.end();it++){
                    ko(*it);
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
    void createTexture(){
        tex.create(1200,700);

    }
};
#endif