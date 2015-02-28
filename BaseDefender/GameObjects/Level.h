//
//  Level.h
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#ifndef __BaseDefender__Level__
#define __BaseDefender__Level__

#include <stdio.h>
#include <vector>
#include "Bullet.h"
#include "Player.h"

class Level{
public:
    Level();
    Level(int type);
    void loadLevel();
    void drawLevel();
    void updateLevel();
private:
    int type;

    std::vector<Player> players;
    std::vector<Bullet> bullets;
    
};


#endif /* defined(__BaseDefender__Level__) */
