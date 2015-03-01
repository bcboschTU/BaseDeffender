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
    
    Base base1 = Base("Base1", 500, 0, 0, 0.4, 0.4, 0, 1);
    bases.push_back(base1);
    
    Turret turret1 = Turret("Turret1Base1", 100, 0.4, 0.4, 0.15, 0.15, 0, 1);
    turrets.push_back(turret1);
    
    Turret turret2 = Turret("Turret2Base1", 100, -0.4, -0.4, 0.15, 0.15, 0, 1);
    turrets.push_back(turret2);
    
    Turret turret3 = Turret("Turret2Base1", 100, -0.4, 0.4, 0.15, 0.15, 0, 1);
    turrets.push_back(turret3);
    
    for(int i = 0; i<100; i++){
        float xPos = rand_FloatRange(-5,5);
        float yPos = rand_FloatRange(-5,5);
        Enemie enemie = Enemie("enemie", 20, xPos, yPos, 0.2, 0.2, 0, 1);
        enemies.push_back(enemie);
    }
}

void Level::drawLevel(){
    //update all the vector array elements first
    updateLevel();
    
    //draw all the elements of all the vector arrays
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
        Bullet *bullet = bullets[i];
        bullet->draw();
    }
}

void Level::updateLevel(){
    //clear all the bullets from last frame
    bullets.clear();
    //get all bullets:
    getBullets();
    
    
    //check if a bullet hits anything
    checkIfBulletsHit();
    
    //check if a enemy hits a player or a turret
    checkIfEnemieHit();
    
    
    //update player
    for (int i = 0; i<players.size(); i++) {
        Player * player = &players[i];
        player->updatePlayer();
    }
    
    //update enemie
    updateEnemieVector();
    for (int i = 0; i<enemies.size(); i++) {
        Enemie * enemie = &enemies[i];
        enemie->updateEnemie();
    }
    
    //update the turrets targets
    for (int i = 0; i< turrets.size(); i++){
        Turret *turret = &turrets[i];
        turret->setTarget(&enemies);
    }
    
    
}

void Level::getBullets(){
    for (int i = 0; i<players.size(); i++) {
        Player * player = &players[i];
        std::vector<Bullet> *tempBullets = player->getBullets();
        for(int j = 0; j<tempBullets->size(); j++){
            bullets.push_back(&tempBullets->at(j));
        }
    }
    
    for (int i = 0; i<turrets.size(); i++) {
        Turret * turret = &turrets[i];
        std::vector<Bullet> *tempBullets = turret->getBullets();
        for(int j = 0; j<tempBullets->size(); j++){
            bullets.push_back(&tempBullets->at(j));
        }
    }
    
}

void Level::checkIfBulletsHit(){
    for (int i = 0; i<players.size(); i++) {
        Player * player = &players[i];
        //check if player is hit by a bullet
    }
    
    for (int i = 0; i<enemies.size(); i++) {
        Enemie * enemie = &enemies[i];
        enemie->gotHit(bullets);
         //check if enemie is hit by a bullet
    }
    
    //update the turrets targets
    for (int i = 0; i< turrets.size(); i++){
        Turret *turret = &turrets[i];
         //check if turret is hit by a bullet
    }
    
    
}
void Level::checkIfEnemieHit(){
    for (int i = 0; i<players.size(); i++) {
        Player * player = &players[i];
        //check if player is hit by a enemie
    }
    
    //update the turrets targets
    for (int i = 0; i< turrets.size(); i++){
        Turret *turret = &turrets[i];
        //check if turret is hit by a enemie
    }
    
    //update the turrets targets
    for (int i = 0; i< bases.size(); i++){
        Base *base = &bases[i];
        //check if base is hit by a enemie
    }
}

void Level::updateEnemieVector(){
    //check if enemie is alive, if not erase
    for (int i = 0; i<enemies.size(); i++) {
        Enemie* enemie = &enemies[i];
        if(enemie->getHp() < 0){
            //remove enemie from enemies;
            enemies.erase(enemies.begin() + i);
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

