//
//  QuadTree.cpp
//  BaseDefender
//
//  Created by Bert Bosch on 03-03-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#include "QuadTree.h"

QuadtreeBullet::QuadtreeBullet(float _x, float _y, float _width, float _height, int _level, int _maxLevel)
{
    x =_x;
    y = _y;
    width = _width;
    height = _height;
    level = _level;
    maxLevel  = _maxLevel;
    if (level == maxLevel) {
        return;
    }
    
    NW = new QuadtreeBullet(x, y, width / 2.0f, height / 2.0f, level+1, maxLevel);
    NE = new QuadtreeBullet(x + width / 2.0f, y, width / 2.0f, height / 2.0f, level+1, maxLevel);
    SW = new QuadtreeBullet(x, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel);
    SE = new QuadtreeBullet(x + width / 2.0f, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel);
}

QuadtreeBullet::~QuadtreeBullet()
{
    if (level == maxLevel)
        return;
    
    delete NW;
    delete NE;
    delete SW;
    delete SE;
}

void QuadtreeBullet::AddObject(Bullet *object) {
    if (level == maxLevel) {
        objects.push_back(object);
        return;
    }
    if (contains(NW, object)) {
        NW->AddObject(object); return;
    } else if (contains(NE, object)) {
        NE->AddObject(object); return;
    } else if (contains(SW, object)) {
        SW->AddObject(object); return;
    } else if (contains(SE, object)) {
        SE->AddObject(object); return;
    }
    if (contains(this, object)) {
        objects.push_back(object);
    }
}

std::vector<Bullet*> QuadtreeBullet::GetObjectsAt(float _x, float _y) {
    if (level == maxLevel) {
        return objects;
    }
    
    std::vector<Bullet*> returnObjects, childReturnObjects;
    if (!objects.empty()) {
        returnObjects = objects;
    }
    if (_x > x + width / 2.0f && _x < x + width) {
        if (_y > y + height / 2.0f && _y < y + height) {
            childReturnObjects = SE->GetObjectsAt(_x, _y);
            returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
            return returnObjects;
        } else if (_y > y && _y <= y + height / 2.0f) {
            childReturnObjects = NE->GetObjectsAt(_x, _y);
            returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
            return returnObjects;
        }
    } else if (_x > x && _x <= x + width / 2.0f) {
        if (_y > y + height / 2.0f && _y < y + height) {
            childReturnObjects = SW->GetObjectsAt(_x, _y);
            returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
            return returnObjects;
        } else if (_y > y && _y <= y + height / 2.0f) {
            childReturnObjects = NW->GetObjectsAt(_x, _y);
            returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
            return returnObjects;
        }
    }
    return returnObjects;
}

void QuadtreeBullet::Clear() {
    if (level == maxLevel) {
        objects.clear();
        return;
    } else {
        NW->Clear();
        NE->Clear();
        SW->Clear();
        SE->Clear();
    }
    if (!objects.empty()) {
        objects.clear();
    }
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
    if (level == maxLevel) {
        objects.clear();
        return;
    } else {
        NW->empty();
        NE->empty();
        SW->empty();
        SE->empty();
    }
    if (!objects.empty()) {
        objects.clear();
    }
}
