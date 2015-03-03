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
#include <GLUT/glut.h>
#include "Bullet.h"
#include "Player.h"
#include "Base.h"
#include "Turret.h"
#include "Enemie.h"
#include "Background.h"
#include "Explosion.h"
#include "texture.hpp"
#include "QuadTree.h"

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
    void generateEnemies();
    Player* getPlayer(int i);
    float rand_FloatRange(float a, float b, bool between);
    void pauseGame();
    void checkIfGameOver();
    void resetLevel();
    void loadTextures();
    void renderString(float x, float y, void *font, const std::string &string);
    void generateExplosionBullet(float _xPos, float _yPos, WeaponType _weaponType);
    void generateExplosion(float _xPos, float _yPos, ExplosionType _explosionType);
    void updateExplosions();
private:
    int type;

    std::vector<Player> players;
    std::vector<Bullet*> bullets;
    std::vector<Base> bases;
    std::vector<Turret> turrets;
    std::vector<Enemie> enemies;
    std::vector<Explosion> explosions;
    Background background = Background(0,0,20,20);
    
    GLuint texture1;
    GLuint texture2;
    GLuint texture3;
    GLuint texture4;
    GLuint texture5;
    std::vector<GLuint> textures;
    std::vector<std::string> textureNamesPosition;
    
    bool pause;
    float lastTimePause;
    float lastTimeLevel;
    
};


#endif /* defined(__BaseDefender__Level__) */
