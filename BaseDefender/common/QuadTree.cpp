//
//  QuadTree.cpp
//  BaseDefender
//
//  Created by Bert Bosch on 03-03-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#include "QuadTree.h"

QuadtreeBullet::QuadtreeBullet(float _x, float _y, float _width, float _height, int _level, int _maxLevel,int _maxObjects)
{
    x		=_x;
    y		=_y;
    width	=_width;
    height	=_height;
    level	=_level;
    maxLevel=_maxLevel;
    maxObjects =_maxObjects;
    nextLevel = false;
    addedChildern = false;
}

void QuadtreeBullet::AddObject(Bullet *object) {
    if(nextLevel){
        if (contains(NW, object)) {
            NW->AddObject(object);
        } else if (contains(NE, object)) {
            NE->AddObject(object);
        } else if (contains(SW, object)) {
            SW->AddObject(object);
        } else if (contains(SE, object)) {
            SE->AddObject(object);
        }
    }
    else if(this->objects.size() > maxObjects){
        if(!addedChildern){
            NW = new QuadtreeBullet(x, y, width / 2.0f, height / 2.0f, level+1, maxLevel,maxObjects);
            NE = new QuadtreeBullet(x + width / 2.0f, y, width / 2.0f, height / 2.0f, level+1, maxLevel,maxObjects);
            SW = new QuadtreeBullet(x, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel,maxObjects);
            SE = new QuadtreeBullet(x + width / 2.0f, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1,  maxLevel,maxObjects);
            addedChildern = true;
        }
        
        //distribute objects over the quadrands
        for(Bullet* bullet: objects){
            if (contains(NW, bullet)) {
                NW->AddObject(bullet);
            } else if (contains(NE, bullet)) {
                NE->AddObject(bullet);
            } else if (contains(SW, bullet)) {
                SW->AddObject(bullet);
            } else if (contains(SE, bullet)) {
                SE->AddObject(bullet);
            }
        }
        objects.clear();
        
        if (contains(NW, object)) {
            NW->AddObject(object);
        } else if (contains(NE, object)) {
            NE->AddObject(object);
        } else if (contains(SW, object)) {
            SW->AddObject(object);
        } else if (contains(SE, object)) {
            SE->AddObject(object);
        }
        nextLevel = true;
    }
    else{
        objects.push_back(object);
    }
}

std::vector<Bullet*> QuadtreeBullet::GetObjectsAt(float _x, float _y) {
    std::vector<Bullet*> returnObjects, childReturnObjects;
    if(nextLevel){
        if (_x > x + width / 2.0f && _x < x + width) {
            if (_y > y + height / 2.0f && _y < y + height) {
                return SE->GetObjectsAt(_x, _y);
            } else if (_y > y && _y <= y + height / 2.0f) {
                return NE->GetObjectsAt(_x, _y);
            }
        } else if (_x > x && _x <= x + width / 2.0f) {
            if (_y > y + height / 2.0f && _y < y + height) {
                return SW->GetObjectsAt(_x, _y);
            } else if (_y > y && _y <= y + height / 2.0f) {
                return NW->GetObjectsAt(_x, _y);
            }
        }
        return returnObjects;
    }
    else{
        return objects;
    }
    
    /*
    if (objects.size() > 0) {
        return objects;
        //returnObjects = objects;
    }
     */
}

bool QuadtreeBullet::contains(QuadtreeBullet *child, Bullet *object) {
    return	 !(object->getXPos() < child->x ||
               object->getYPos() < child->y ||
               object->getXPos() > child->x + child->width  ||
               object->getYPos() > child->y + child->height ||
               object->getXPos() + object->getWidth() < child->x ||
               object->getYPos() + object->getWidth() < child->y ||
               object->getXPos() + object->getWidth() > child->x + child->width ||
               object->getYPos() + object->getWidth() > child->y + child->height);
}

void QuadtreeBullet::empty(){
    if (!nextLevel) {
        objects.clear();
        return;
    } else {
        nextLevel = false;
        NW->empty();
        NE->empty();
        SW->empty();
        SE->empty();
    }
}
