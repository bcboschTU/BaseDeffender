//
//  Level.cpp
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#include "Level.h"

Level::Level(){
    
}


Level::Level(int _type){
    type = _type;
    loadLevel();
    pause = false;
}

void Level::loadLevel(){
    Player player1 = Player("Player1", 200, 1, 1, 0.2, 0.2, 0, 1);
    players.push_back(player1);
    
    Base base1 = Base("Base1", 200, 0, 0, 0.4, 0.4, 0, 1);
    bases.push_back(base1);
    
    Turret turret1 = Turret("Turret1Base1", 1000, 0.4, 0.4, 0.15, 0.15, 0, 1);
    turrets.push_back(turret1);
    
    Turret turret2 = Turret("Turret2Base1", 1000, -0.4, -0.4, 0.15, 0.15, 0, 1);
    turrets.push_back(turret2);
    
    for(int i = 0; i<100; i++){
        float xPos = rand_FloatRange(-5,5);
        float yPos = rand_FloatRange(-5,5);
        Enemie enemie = Enemie("enemie", 20, xPos, yPos, 0.2, 0.2, 0, 1);
        enemies.push_back(enemie);
    }
}

void Level::drawLevel(){
    for (int i = 0; i<players.size(); i++) {
        Player * player = &players[i];
        player->draw();
    }
    
    for (int i = 0; i<bases.size(); i++) {
        Base * base = &bases[i];
        base->draw();
    }
    
    for (int i = 0; i<turrets.size(); i++) {
        Turret * turret = &turrets[i];
        turret->draw();
    }
    
    for (int i = 0; i<enemies.size(); i++) {
        Enemie * enemie = &enemies[i];
        enemie->draw();
    }
    
    for (int i = 0; i<bullets.size(); i++) {
        Bullet *bullet = &bullets[i];
        bullet->draw();
    }
}

void Level::updateLevel(){
    for (int i = 0; i<players.size(); i++) {
        Player * player = &players[i];
        player->updatePlayer();
    }
    
    for (int i = 0; i< turrets.size(); i++){
        Turret *turret = &turrets[i];
        turret->setTarget(&enemies);
    }
    
    
    bullets.clear();
    //get all bullets:
    getBullets();
}

void Level::getBullets(){
    for (int i = 0; i<players.size(); i++) {
        Player * player = &players[i];
        std::vector<Bullet> *tempBullets = player->getBullets();
        for(int j = 0; j<tempBullets->size(); j++){
            bullets.push_back(tempBullets->at(j));
        }
    }
    
    for (int i = 0; i<turrets.size(); i++) {
        Turret * turret = &turrets[i];
        std::vector<Bullet> *tempBullets = turret->getBullets();
        for(int j = 0; j<tempBullets->size(); j++){
            bullets.push_back(tempBullets->at(j));
        }
    }
    
}

Player* Level::getPlayer(int i){
    return &players[i];
}


float Level::rand_FloatRange(float a, float b){
    float randomValue = ((b-a)*((float)rand()/RAND_MAX))+a;
    if(randomValue > 1 || randomValue < -1){
        return randomValue;
    }
    else{
        return rand_FloatRange(a,b);
    }
}

