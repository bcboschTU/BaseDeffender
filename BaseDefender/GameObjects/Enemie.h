//
//  Enemie.h
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#ifndef __BaseDefender__Enemie__
#define __BaseDefender__Enemie__

#include "GameObject.h"

class Enemie{
public:
    Enemie(std::string _name,
           int _hp,
           float _xPos,
           float _yPos,
           float _width,
           float _height,
           float _angle,
           int _level);
    void draw();
    std::string getName();
    void setName(std::string _name);
    int getHp();
    void setHp(int hp);
    float getXPos();
    void setXPos(float _xPos);
    float getYPos();
    void setYPos(float _yPos);
    float getWidth();
    void setWidth(float _width);
    float getHeight();
    void setHeight(float _height);
    float getAngle();
    void setAngle(float _angle);
    int getLevel();
    void setLevel(int level);
private:
    std::string name;
    int hp;
    float xPos;
    float yPos;
    float width;
    float height;
    float angle;
    int level;
};


#endif /* defined(__BaseDefender__Enemie__) */
