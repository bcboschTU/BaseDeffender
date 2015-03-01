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
#include "Base.h"
#include "Turret.h"
#include "Enemie.h"

class Level{
public:
    Level();
    Level(int type);
    void loadLevel();
    void drawLevel();
    void updateLevel();
    void getBullets();
    void checkIfBulletsHit();
    void checkIfEnemieHit();
    void updateEnemieVector();
    Player* getPlayer(int i);
    float rand_FloatRange(float a, float b);
private:
    int type;

    std::vector<Player> players;
    std::vector<Bullet*> bullets;
    std::vector<Base> bases;
    std::vector<Turret> turrets;
    std::vector<Enemie> enemies;
    
    bool pause;
};


#endif /* defined(__BaseDefender__Level__) */
