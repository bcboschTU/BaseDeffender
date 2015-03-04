//
//  Level.cpp
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#include "Level.h"
//QuadtreeBullet quadtree = QuadtreeBullet( -10.0f, -10.0f, 20.0f, 20.0f, 0, 10, 3 );
Level::Level(){

}


Level::Level(int _type){
    type = _type;
    loadLevel();
    pause = false;
    lastTimeLevel = glfwGetTime();
    lastTimePause = glfwGetTime();
    background.setXPos(0);
    background.setYPos(0);
    background.setWidth(10);
    background.setHeight(6.5);
    
}

void Level::loadLevel(){
    Player player1 = Player("Player1", 200, 1, 1, 0.4, 0.4, 0, 1);
    players.push_back(player1);
    
    Base base1 = Base("Base1", 500, 0, 0, 0.8, 0.8, 0, 1);
    bases.push_back(base1);
    
    Turret turret11 = Turret("Turret1Base1", 100, 0.7, 0.7, 0.15, 0.15, 45, 1, 10, 80);
    turrets.push_back(turret11);
    
    Turret turret12 = Turret("Turret2Base1", 100, -0.7, -0.7, 0.15, 0.15, 225, 1, 190, 260);
    turrets.push_back(turret12);
    
    Turret turret13 = Turret("Turret3Base1", 100, -0.7, 0.7, 0.15, 0.15, 135, 1, 100, 170);
    turrets.push_back(turret13);
    
    Turret turret14 = Turret("Turret4Base1", 100, 0.7, -0.7, 0.15, 0.15, 315, 1, 280, 350);
    turrets.push_back(turret14);
    
    Base base2 = Base("Base2", 500, -3, 0, 0.8, 0.8, 0, 1);
    bases.push_back(base2);
    
    Turret turret21 = Turret("Turret1Base2", 100, 0.7-3, 0.7, 0.15, 0.15, 45, 1, 10, 80);
    turrets.push_back(turret21);
    
    Turret turret22 = Turret("Turret2Base2", 100, -0.7-3, -0.7, 0.15, 0.15, 225, 1, 190, 260);
    turrets.push_back(turret22);
    
    Turret turret23 = Turret("Turret3Base2", 100, -0.7-3, 0.7, 0.15, 0.15, 135, 1, 100, 170);
    turrets.push_back(turret23);
    
    Turret turret24 = Turret("Turret4Base2", 100, 0.7-3, -0.7, 0.15, 0.15, 315, 1, 280, 350);
    turrets.push_back(turret24);
    
    
    Base base3 = Base("Base3", 500, 3, 0, 0.8, 0.8, 0, 1);
    bases.push_back(base3);
    
    Turret turret31 = Turret("Turret1Base3", 100, 0.7 + 3, 0.7, 0.15, 0.15, 45, 1, 10, 80);
    turrets.push_back(turret31);
    
    Turret turret32 = Turret("Turret2Base3", 100, -0.7 + 3, -0.7, 0.15, 0.15, 225, 1, 190, 260);
    turrets.push_back(turret32);
    
    Turret turret33 = Turret("Turret3Base3", 100, -0.7 + 3, 0.7, 0.15, 0.15, 135, 1, 100, 170);
    turrets.push_back(turret33);
    
    Turret turret34 = Turret("Turret4Base3", 100, 0.7 + 3, -0.7, 0.15, 0.15, 315, 1, 280, 350);
    turrets.push_back(turret34);
    
    
    loadTextures();
}

void Level::drawLevel(){
    if(!pause){
        //update all the vector array elements first
        updateLevel();
    }
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture3);
    background.drawBackGround();
    
    glBindTexture(GL_TEXTURE_2D, texture2);
    for (int i = 0; i<turrets.size(); i++) {
        Turret * turret = &turrets[i];
        turret->draw();
    }
    
    glBindTexture(GL_TEXTURE_2D, texture1);
    for (int i = 0; i<bases.size(); i++) {
        Base * base = &bases[i];
        base->draw();
    }
    
    //draw all the elements of all the vector arrays
    glBindTexture(GL_TEXTURE_2D, texture4);
    for (int i = 0; i<players.size(); i++) {
        Player * player = &players[i];
        player->draw();
    }
    
    glBindTexture(GL_TEXTURE_2D, texture5);
    for (int i = 0; i<enemies.size(); i++) {
        Enemie * enemie = &enemies[i];
        enemie->draw();
    }
    
    glDisable(GL_TEXTURE_2D);
    
    
    
    
    
    
    for (int i = 0; i<bullets.size(); i++) {
        Bullet *bullet = bullets[i];
        bullet->draw();
    }
    
    for (int i = 0; i<explosions.size(); i++) {
        Explosion *explosion = &explosions[i];
        explosion->draw();
    }
    
    
    
    
    
    renderString(-2, -2, GLUT_BITMAP_HELVETICA_18, "test");
    
    
}

void Level::updateLevel(){
    checkIfGameOver();
    //clear all the bullets from last frame

    bullets.clear();
    //quadtree.empty();
    //get all bullets:
    getBullets();
    
    
    //check if a bullet hits anything
    checkIfBulletsHit();
    //check if a enemy hits a player or a turret
    checkIfEnemieHit();
    
    generateEnemies();
    
    updateExplosions();
    
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
    
    for(int i = 0; i<explosions.size(); i++){
        Explosion * explosion = &explosions[i];
        explosion->updateExplosion();
    }
}

void Level::getBullets(){
    for (int i = 0; i<players.size(); i++) {
        Player * player = &players[i];
        std::vector<Bullet> *tempBullets = player->getBullets();
        for(int j = 0; j<tempBullets->size(); j++){
            bullets.push_back(&tempBullets->at(j));
            //quadtree.AddObject(&tempBullets->at(j));
        }
    }
    
    for (int i = 0; i<turrets.size(); i++) {
        Turret * turret = &turrets[i];
        std::vector<Bullet> *tempBullets = turret->getBullets();
        for(int j = 0; j<tempBullets->size(); j++){
            bullets.push_back(&tempBullets->at(j));
            //quadtree.AddObject(&tempBullets->at(j));
        }
    }
    
}

void Level::checkIfBulletsHit(){
    for (int i = 0; i<players.size(); i++) {
        //Player * player = &players[i];
        //check if player is hit by a bullet
    }
    
    for (int i = 0; i<enemies.size(); i++) {
        Enemie * enemie = &enemies[i];
        int bulletHit = enemie->gotHit(bullets);
        //int bulletHit = enemie->gotHitTree(&quadtree);
        if(bulletHit != -1){
            Bullet *bullet = bullets[bulletHit];
            generateExplosionBullet(bullet->getXPos(), bullet->getYPos(),bullet->getType());
        }
        //check if enemie is hit by a bullet
    }
    
    //update the turrets targets
    for (int i = 0; i< turrets.size(); i++){
        //Turret *turret = &turrets[i];
        //check if turret is hit by a bullet
    }
    
    
}
void Level::checkIfEnemieHit(){
    for (int i = 0; i<players.size(); i++) {
        Player * player = &players[i];
        //check if player is hit by a enemie
        for (int i = 0; i<enemies.size(); i++) {
            Enemie * enemie = &enemies[i];
            player->getHitByEnemie(enemie->getXPos(), enemie->getYPos(), enemie->getWidth(), enemie->getDmg());
        }
    }
    
    for (int i = 0; i< turrets.size(); i++){
        //Turret *turret = &turrets[i];
        //check if turret is hit by a enemie
    }
    
    for (int i = 0; i< bases.size(); i++){
        //Base *base = &bases[i];
        //check if base is hit by a enemie
    }
}

void Level::updateEnemieVector(){
    //check if enemie is alive, if not erase
    for (int i = 0; i<enemies.size(); i++) {
        Enemie* enemie = &enemies[i];
        if(enemie->getHp() <= 0){
            //add explosion:
            generateExplosion(enemie->getXPos(), enemie->getYPos(), MEDIUM);
            //remove enemie from enemies;
            enemies.erase(enemies.begin() + i);
            
        }
    }
}

Player* Level::getPlayer(int i){
    return &players[i];
}


float Level::rand_FloatRange(float a, float b, bool between){
    float randomValue = ((b-a)*((float)rand()/RAND_MAX))+a;
    if (between) {
        if(randomValue > 10 || randomValue < -10){
            return randomValue;
        }
        else{
            return rand_FloatRange(a,b, between);
        }
    }
    else{
        return randomValue;
    }
}

void Level::generateEnemies(){
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTimeLevel);
    if(deltaTime > 0.01 && enemies.size() < 500){
        for(int i = 0; i< 1; i++){
            float xPos = rand_FloatRange(-14,14, true);
            float yPos = rand_FloatRange(-14,14, false);
            Enemie enemie = Enemie("enemie", 10, xPos, yPos, 0.2, 0.2, 0, 1);
            enemie.setTargetPlayer(&players[0]);
            //enemie.setTargetBase(&bases[0]);
            enemies.push_back(enemie);
            lastTimeLevel = currentTime;
        }
    }
}


void Level::pauseGame(){
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTimePause);
    if(deltaTime > 0.2){
        pause = !pause;
        lastTimePause = currentTime;
    }
    
    if(!pause){
        //unpause all vectors, set time.
    }
}

void Level::checkIfGameOver(){
    for (int i = 0; i<players.size(); i++) {
        Player * player = &players[i];
        if(player->getHp() <= 0){
            resetLevel();
        }
    }
}

void Level::resetLevel(){
    players.clear();
    bullets.clear();
    bases.clear();
    turrets.clear();
    enemies.clear();
    explosions.clear();
    glDeleteTextures(1, &texture1);
    glDeleteTextures(1, &texture2);
    glDeleteTextures(1, &texture3);
    glDeleteTextures(1, &texture4);
    glDeleteTextures(1, &texture5);
    loadLevel();
}

void Level::loadTextures(){
    texture1 = loadPng("/Users/bertbosch/Documents/delft/game/BaseDeffender/BaseDefender/Textures/base.png");
    texture2 = loadPng("/Users/bertbosch/Documents/delft/game/BaseDeffender/BaseDefender/Textures/tank_turret.png");
    texture3 = loadPng("/Users/bertbosch/Documents/delft/game/BaseDeffender/BaseDefender/Textures/background2.png");
    texture4 = loadPng("/Users/bertbosch/Documents/delft/game/BaseDeffender/BaseDefender/Textures/player.png");
    texture5 = loadPng("/Users/bertbosch/Documents/delft/game/BaseDeffender/BaseDefender/Textures/tank1.png");
}

void Level::renderString(float x, float y, void *font, const std::string &string)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);
    for (int n=0; n<string.size(); ++n) {
        glutBitmapCharacter(font, string[n]);
    }
}

void Level::generateExplosionBullet(float _xPos, float _yPos, WeaponType _weaponType){
    if (_weaponType == NORMAL) {
        generateExplosion(_xPos,_yPos,SMALL);
    }
}

void Level::generateExplosion(float _xPos, float _yPos, ExplosionType _type){
    Explosion explosion = Explosion(_xPos,_yPos,_type);
    explosions.push_back(explosion);
}

void Level::updateExplosions(){
    for (int i = 0; i<explosions.size(); i++) {
        Explosion* explosion = &explosions[i];
        if(explosion->getDestroyed()){
            explosions.erase(explosions.begin() + i);
            
        }
    }
}
