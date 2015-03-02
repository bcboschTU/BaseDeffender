//
//  Enemie.cpp
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#include "Enemie.h"

Enemie::Enemie(std::string _name,
               int _hp,
               float _xPos,
               float _yPos,
               float _width,
               float _height,
               float _angle,
               int _level){
    name = _name;
    hp = _hp;
    xPos = _xPos;
    yPos = _yPos;
    width = _width;
    height = _height;
    level = _level;
    
    nextXpos = _xPos;
    nextYpos = _yPos;
    
    dmg = 10;
    
    //movement:
    agility = 0.03;
    movementSpeed = 0;
    movementXdir = 0;
    movementYdir = 0;
    maxSpeed = 1;
    acceleration = 0.1;
    deceleration = 0.01;
    
    //target
    targetType = -1;
    
}

void Enemie::draw(){
    if(hp>0){
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        glTranslatef(getXPos(), getYPos(), 0);
    
    
        glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 1.0f);
        for(double i = 0; i < 2 * PI; i += PI / 128){ //<-- Change this Value
            glVertex3f(cos(i) * getWidth(), sin(i) * getHeight(), 0.0);
        }
        glEnd();
    
        glPopMatrix();
    }
}

void Enemie::updateEnemie(){
    calculateNewPos();
    if(nextXpos == getXPos() && nextYpos == getYPos() && movementSpeed >= 0){
        movementSpeed -= deceleration;
    }
    if((nextXpos != getXPos() || nextYpos != getYPos()) &&  movementSpeed < maxSpeed){
        movementSpeed += acceleration;
    }
    if (movementSpeed < 0) {
        movementXdir = 0;
        movementYdir = 0;
    }
    
    if(movementXdir == 0 && movementYdir == 0){
        float xDif = nextXpos - getXPos();
        float yDif = nextYpos - getYPos();
        movementXdir = xDif;
        movementYdir = yDif;
    }
    else{
        float xDif = nextXpos - getXPos();
        float yDif = nextYpos - getYPos();
        movementXdir = movementXdir * (1-agility) + (xDif * agility);
        movementYdir = movementYdir * (1-agility) + (yDif * agility);;
    }
    
    nextXpos = getXPos() + movementXdir * (movementSpeed);
    nextYpos = getYPos() + movementYdir * (movementSpeed);
    
    setXPos(nextXpos);
    setYPos(nextYpos);
}

void Enemie::gotHit(std::vector<Bullet*> bullets){
    for (int i = 0; i< bullets.size(); i++) {
        Bullet* bullet = bullets[i];
        float distance = calculateDistance(xPos, bullet->getXPos(), yPos, bullet->getYPos());
        float hitDistance = width + bullet->getWidth();
        if(distance < hitDistance){
            hp = hp - bullet->getDmg();
            //bullet set on destroyed;
            bullet->setDestroyed(true);
        }
    }
}


void Enemie::setTargetPlayer(Player *_target){
    targetType =1 ;
    targetPlayer = _target;
}
void Enemie::setTargetBase(Base *_target){
    targetType = 2;
    targetBase = _target;
}

void Enemie::calculateNewPos(){
    // Compute time difference between current and last frame
    if (targetType != -1) {
        
        switch (targetType) {
            case 1:
                calculateNewPosPlayer();
                break;
            case 2:
                calculateNewPosBase();
                break;
            default:
                break;
        }
    }
}

void Enemie::calculateNewPosPlayer(){
    nextXpos = targetPlayer->getXPos();
    nextYpos = targetPlayer->getYPos();
    
    //normalise next pos
    float xdif = getXPos() - targetPlayer->getXPos();
    float ydif = getYPos() - targetPlayer->getYPos();
    
    float angle = (atan2(ydif, xdif) * 180.0 / PI) + 180;
    
    nextXpos = getXPos() + cosf(angle * PI/180)  * 0.02;
    nextYpos = getYPos() + sinf(angle * PI/180)  * 0.02;
    
    //nextXpos = nextXpos;
    //nextYpos = nextYpos;
}

void Enemie::calculateNewPosBase(){
    nextXpos = targetBase->getXPos();
    nextYpos = targetBase->getYPos();
    
    //normalise next pos
}


std::string Enemie::getName(){
    return name;
}
void Enemie::setName(std::string _name){
    name = _name;
}
int Enemie::getHp(){
    return hp;
}
void Enemie::setHp(int _hp){
    hp = _hp;
}
float Enemie::getXPos(){
    return xPos;
}
void Enemie::setXPos(float _xPos){
    xPos = _xPos;
}
float Enemie::getYPos(){
    return yPos;
}
void Enemie::setYPos(float _yPos){
    yPos = _yPos;
}
float Enemie::getWidth(){
    return width;
}
void Enemie::setWidth(float _width){
    width = _width;
}
float Enemie::getHeight(){
    return height;
}
void Enemie::setHeight(float _height){
    height = _height;
}
float Enemie::getAngle(){
    return angle;
}
void Enemie::setAngle(float _angle){
    angle = _angle;
}
int Enemie::getLevel(){
    return level;
}
void Enemie::setLevel(int _level){
    level = _level;
}

int Enemie::getDmg(){
    return dmg;
}
void Enemie::setDmg(int _dmg){
    dmg = _dmg;
}

float Enemie::calculateDistance(float x1, float x2, float y1, float y2){
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx*dx + dy*dy);
}
