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
    
}

void Player::draw(){
    glColor3f(0.0f, 1.0f, 0.0f);

    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    glPushMatrix();
    glTranslatef(getXPos(), getYPos(), 0);
    
    glBegin(GL_POLYGON);
    for(double i = 0; i < 2 * PI; i += PI / 32){ //<-- Change this Value
            glVertex3f(cos(i) * getWidth(), sin(i) * getHeight(), 0.0);
    }
    glEnd();
    
    glPopMatrix();
}

void Player::updatePlayer(){
    
}
