//
//  GameObject.h
//  BaseDefender
//
//  Created by Bert Bosch on 28-02-15.
//  Copyright (c) 2015 Bossos. All rights reserved.
//

#ifndef __BaseDefender__GameObject__
#define __BaseDefender__GameObject__

#include <stdio.h>

class GameObject{
public:
    GameObject();
private:
    float xPos;
    float yPos;
    float width;
    float height;
    int level;
    
};

#endif /* defined(__BaseDefender__GameObject__) */
