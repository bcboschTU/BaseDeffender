//
//  Player.cpp
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#include "Player.h"

Player::Player(std::string _name,
               int _hp,
               float _xPos,
               float _yPos,
               float _width,
               float _height,
               float _angle,
               int _level):GameObject(_name,_hp,_xPos,_yPos,_width,_height,_angle,_level){
    fireRatePrimary = 0.05;
    fireRateSecondary = 0.1;
    primaryWeaponType = NORMAL;
    secondaryWeaponType = EXPLOSIVE;
    
}

void Player::draw(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(getXPos(), getYPos(), 0);
    
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 1.0f, 0.0f);
    for(double i = 0; i < 2 * PI; i += PI / 128){ //<-- Change this Value
        glVertex3f(cos(i) * getWidth(), sin(i) * getHeight(), 0.0);
    }
    glEnd();
    
    glPopMatrix();
}

void Player::updatePlayer(){
    
}

void Player::shootPrimary(float dirXPos, float dirYPos){
    static double lastTimePrimary = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTimePrimary);
    
    if(deltaTime > fireRatePrimary){
        //calculate angle:
        float xdif = getXPos() - dirXPos;
        float ydif = getYPos() - dirYPos;
        
        float angle = (atan2(ydif, xdif) * 180.0 / PI) + 180;
        
        Bullet bullet = Bullet(getXPos(), getYPos(), angle, primaryWeaponType);
        bullets.push_back(bullet);
        
        lastTimePrimary = currentTime;
    }
}

void Player::shootSecondary(float dirXPos, float dirYPos){
    static double lastTimeSecondary = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTimeSecondary);
    
    if(deltaTime > fireRateSecondary){
        //calculate angle:
        float xdif = getXPos() - dirXPos;
        float ydif = getYPos() - dirYPos;
        
        float angle = (atan2(ydif, xdif) * 180.0 / PI) + 180;
        
        Bullet bullet = Bullet(getXPos(), getYPos(), angle, secondaryWeaponType);
        bullets.push_back(bullet);
        
        lastTimeSecondary = currentTime;
    }
}

std::vector<Bullet> *Player::getBullets(){
    updateBullets();
    
    return &bullets;
}

float Player::getFireRatePrimary(){
    return fireRatePrimary;
}

float Player::getXPos(){
    return GameObject::getXPos();
}
float Player::getYPos(){
    return GameObject::getYPos();
}

void Player::setNewPos(float newXPos, float newYPos){
    setXPos(newXPos);
    setYPos(newYPos);
}

void Player::updateBullets(){
    for(int i = 0; i< bullets.size(); i++){
        Bullet *bullet = &bullets[i];
        bullet->updateBullet();
        if(bullet->getDestroyed()){
            removeBullet(i);
        }
        
    }
}

void Player::removeBullet(int index){
    bullets.erase(bullets.begin() + index);
}
