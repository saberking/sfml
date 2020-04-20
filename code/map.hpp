#include <stdlib.h>
#include<list>
#include<vector>
#include<string>
#include <deque>
#include <SFML/Graphics.hpp>
#include <conio.h>
#include <stdio.h>
#include "room.hpp"
    sf::RenderTexture texture;

struct Map{
    bool fog[17][30];
    bool visible=false;
    sf::Texture tex;
    sf::Sprite mapSprite,sprite;
    sf::RectangleShape rect;
    Map(){
        rect.setSize(sf::Vector2f(40.f, 40.f));
        rect.setFillColor(sf::Color(0,0,0,255));
        tex.loadFromFile("map.png");
        mapSprite.setTexture(tex);
        // texture=new sf::RenderTexture();
        texture.create(1200.f,700.f);
        for(int i=0;i<17;i++){
            for(int j=0;j<30;j++){
                fog[i][j]=true;
            }
        }
    }
    void reveal(Room* r){
        for(int i=r->mapRegion.top;i<=r->mapRegion.bottom;i++){
            for(int j=r->mapRegion.left;j<=r->mapRegion.right;j++){
                fog[i][j]=false;
            }
        }
    }
    void draw(){
        texture.clear(sf::Color(0,0,0,255));
        texture.draw(mapSprite);
        for(int i=0;i<17;i++){
            for( int j=0;j<30;j++){
                if(fog[i][j]){
                    rect.setPosition((float)j*40,(float)i*40);
                    texture.draw(rect);
                }
            }
        }
        texture.display();
    }
    sf::Sprite getSprite(){
        draw();
        sprite.setTexture(texture.getTexture());
        return sprite;
    }
};
Map mapp;