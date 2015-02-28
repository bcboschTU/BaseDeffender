//
//  controls.h
//  opengl
//
//  Created by Bert Bosch on 13-10-14.
//  Copyright (c) 2014 BoschIt. All rights reserved.
//

#ifndef __opengl__controls__
#define __opengl__controls__

#include <iostream>
#include <GLFW/glfw3.h>
#include "glm.hpp"

class Camera {
public:
    Camera();
    const glm::vec3& getPosition() const;
    void setPosition(const glm::vec3& position);
    void lookAt(glm::vec3 position);
    void computeInputs(GLFWwindow* window);
    
private:
    glm::vec3 _position;
    float _minZoom;
    float _maxZoom;
};

#endif /* defined(__opengl__controls__) */
