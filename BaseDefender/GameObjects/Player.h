//
//  Player.h
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#ifndef __BaseDefender__Player__
#define __BaseDefender__Player__

#include <stdio.h>
#include "GameObject.h"

class Player:GameObject{
public:
    Player(std::string _name,
           int _hp,
           float _xPos,
           float _yPos,
           float _width,
           float _height,
           float _angle,
           int _level);
    void draw();
    void updatePlayer();
};

#endif /* defined(__BaseDefender__Player__) */
