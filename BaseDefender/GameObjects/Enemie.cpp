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
}

void Enemie::draw(){
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