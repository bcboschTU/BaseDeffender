//
//  Level.cpp
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#include "Level.h"

Level::Level(){
    
}


Level::Level(int _type){
    type = _type;
    loadLevel();
}

void Level::loadLevel(){
    Player player = Player("Player1", 200, 0, 0, 0.5, 0.5, 0, 1);
    players.push_back(player);
}

void Level::drawLevel(){
    for (int i = 0; i<players.size(); i++) {
        Player * player = &players[i];
        player->draw();
    }
    
    for (int i = 0; i<bullets.size(); i++) {
        //Bullet *bullet = &bullet[i];
    }
}

void Level::updateLevel(){
    for (int i = 0; i<players.size(); i++) {
        Player * player = &players[i];
        player->updatePlayer();
    }
}