//
//  Base.cpp
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#include "Base.h"

Base::Base(std::string _name,
               int _hp,
               float _xPos,
               float _yPos,
               float _width,
               float _height,
               float _angle,
               int _level):GameObject(_name,_hp,_xPos,_yPos,_width,_height,_angle,_level){
}


void Base::draw(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    
    glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
        glColor4f(1.0f, 1.0f, 1.0f,1.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(getXPos() - getWidth(), getYPos() - getHeight());    // x, y
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(getXPos() + getWidth(), getYPos() - getHeight());
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(getXPos() + getWidth(), getYPos() + getHeight());
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(getXPos() - getWidth(), getYPos() + getHeight());
    glEnd();
    
    glPopMatrix();
}

void Base::drawObj(std::vector<tinyobj::shape_t> shapes, std::vector<tinyobj::material_t> materials){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    
    glTranslatef(getXPos(), getYPos(), 0);
    glScaled(0.2, 0.2, 0.2);
    glRotated(getAngle()+270, 1.0, 0.0, 0.0);
    glTranslatef(-getXPos(), -getYPos(), 0);
    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < shapes.size()-6; i++) {
        for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
                glColor4f(1.0f, 1.0f, 1.0f,1.0f);
                glNormal3f(shapes[i].mesh.normals[3*shapes[i].mesh.indices[3*f+0]],
                           shapes[i].mesh.normals[3*shapes[i].mesh.indices[3*f+0]+1],
                           shapes[i].mesh.normals[3*shapes[i].mesh.indices[3*f+0]+2]);
                glVertex3f(shapes[i].mesh.positions[3*shapes[i].mesh.indices[3*f+0]],
                           shapes[i].mesh.positions[3*shapes[i].mesh.indices[3*f+0]+1],
                           shapes[i].mesh.positions[3*shapes[i].mesh.indices[3*f+0]+2]);
                glNormal3f(shapes[i].mesh.normals[3*shapes[i].mesh.indices[3*f+1]],
                           shapes[i].mesh.normals[3*shapes[i].mesh.indices[3*f+1]+1],
                           shapes[i].mesh.normals[3*shapes[i].mesh.indices[3*f+1]+2]);
                glVertex3f(shapes[i].mesh.positions[3*shapes[i].mesh.indices[3*f+1]],
                           shapes[i].mesh.positions[3*shapes[i].mesh.indices[3*f+1]+1],
                           shapes[i].mesh.positions[3*shapes[i].mesh.indices[3*f+1]+2]);
                glNormal3f(shapes[i].mesh.normals[3*shapes[i].mesh.indices[3*f+2]],
                           shapes[i].mesh.normals[3*shapes[i].mesh.indices[3*f+2]+1],
                           shapes[i].mesh.normals[3*shapes[i].mesh.indices[3*f+2]+2]);
                glVertex3f(shapes[i].mesh.positions[3*shapes[i].mesh.indices[3*f+2]],
                           shapes[i].mesh.positions[3*shapes[i].mesh.indices[3*f+2]+1],
                           shapes[i].mesh.positions[3*shapes[i].mesh.indices[3*f+2]+2]);

        }
    }
    glEnd();
    glPopMatrix();
}

bool Base::getHitByEnemie(float enemieXPos, float enemieYPos, float enemieWidth, int dmg){
    float distance = calculateDistance(getXPos(), enemieXPos, getYPos(), enemieYPos);
    float hitDistance = getWidth() + enemieWidth;
    if(distance < hitDistance){
        setHp(getHp()- dmg);
        return true;
    }
    return false;
}

float Base::getXPos(){
    return GameObject::getXPos();
}
float Base::getYPos(){
    return GameObject::getYPos();
}

int Base::getHp(){
    return GameObject::getHp();
}