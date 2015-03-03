//
//  QuadTree.h
//  BaseDefender
//
//  Created by Bert Bosch on 03-03-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#ifndef __BaseDefender__QuadTree__
#define __BaseDefender__QuadTree__

#include <stdio.h>
#include <vector>
#include "Bullet.h"

class QuadtreeBullet {
public:
    QuadtreeBullet(float x, float y, float width, float height, int level, int maxLevel);
    
    ~QuadtreeBullet();
    
    void					AddObject(Bullet *object);
    std::vector<Bullet*>	GetObjectsAt(float x, float y);
    void					Clear();
    void                    empty();
    
private:
    float					x;
    float					y;
    float					width;
    float					height;
    int                     level;
    int                     maxLevel;
    std::vector<Bullet*>	objects;
    
    QuadtreeBullet *		parent;
    QuadtreeBullet *		NW;
    QuadtreeBullet *		NE;
    QuadtreeBullet *		SW;
    QuadtreeBullet *		SE;
    
    bool					contains(QuadtreeBullet *child, Bullet *object);
};


#endif /* defined(__BaseDefender__QuadTree__) */
