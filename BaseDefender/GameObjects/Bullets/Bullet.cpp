//
//  Bullet.cpp
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#include "Bullet.h"


Bullet::Bullet(float _xPos, float _yPos, float _angle, WeaponType _bulletType){
    xPos = _xPos;
    yPos = _yPos;
    angle = _angle;
    bulletType = _bulletType;
    lifeStart = glfwGetTime();
    lifetime = 4.0;
    destroyed = false;
    exploding = false;
    bulletSetup();
    
}

void Bullet::bulletSetup(){
    switch (bulletType) {
        case NORMAL:
            width = 0.1;
            height = 0.1;
            speed = 0.1;
            break;
        case EXPLOSIVE:
            width = 0.15;
            height = 0.15;
            speed = 0.08;
            break;
        case DUAL:
            width = 0.05;
            height = 0.05;
            speed = 0.01;
            break;
        case ROCKET:
            width = 0.1;
            height = 0.1;
            speed = 0.01;
            break;
        default:
            break;
    }
}

void Bullet::draw(){
    if(!destroyed){
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        glTranslatef(xPos, yPos, 0);
        
        
        glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.0f, 0.0f);
        for(double i = 0; i < 2 * PI; i += PI / 32){ //<-- Change this Value
            glVertex3f(cos(i) * width, sin(i) * height, 0.0);
        }
        glEnd();
        
        
        glBegin(GL_POLYGON);
        glColor3f(1.0f, 1.0f, 0.0f);
        for(double i = 0; i < 2 * PI; i += PI / 32){ //<-- Change this Value
            glVertex3f(cos(i) * (width/4)*3, sin(i) * (height/4)*3, 0.0);
        }
        glEnd();
        glPopMatrix();
        
    }
    
}

void Bullet::updateBullet(){
    //life
    checkIfAlive();
    
    
    if(exploding){
        width += 0.02;
        height += 0.02;
    }
    else{
        //update xpos and ypos;
        float xPosNew = xPos;
        float yPosNew = yPos;
        
        float xdif = cosf(angle * PI/180);
        float ydif = sinf(angle * PI/180);
        
        
        xPos = xPosNew + xdif*speed;
        yPos = yPosNew + ydif*speed;
    }
}

void Bullet::explodeBullet(){
    exploding = true;
    lifeStart = glfwGetTime();
}

bool Bullet::getExploding(){
    return exploding;
}

void Bullet::setExploding(bool _exploding){
    exploding = _exploding;
}

void Bullet::checkIfAlive(){
    float currentTime = glfwGetTime();
    if(currentTime - lifeStart > lifetime){
        destroyed = true;
    }
}

bool Bullet::getDestroyed(){
    float currentTime = glfwGetTime();
    if(currentTime - lifeStart > lifetime){
        return true;
    }
    return false;
}
