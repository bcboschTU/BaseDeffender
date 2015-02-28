//
//  controls.cpp
//  opengl
//
//  Created by Bert Bosch on 13-10-14.
//  Copyright (c) 2014 BoschIt. All rights reserved.
//

#include "controls.h"
float translateSpeed = 6.0f;
float zoomSpeed = .2f;

Camera::Camera() :
    _position(0.0f, 0.0f, 1.0f),
    _minZoom(0.05),
    _maxZoom(4)
{}

const glm::vec3& Camera::getPosition() const {
    return _position;
}

void Camera::setPosition(const glm::vec3& position) {
    _position = position;
}

void Camera::computeInputs(GLFWwindow* window){
    // glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();
    
	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	// Move forward
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		_position.y -= 1 * deltaTime * translateSpeed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		_position.y += 1 * deltaTime * translateSpeed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		_position.x -= 1 * deltaTime * translateSpeed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		_position.x += 1 * deltaTime * translateSpeed;
	}
    if (glfwGetKey(window, GLFW_KEY_Q ) == GLFW_PRESS) {
        if(_position.z >_minZoom){
            _position.z -= 1 * deltaTime * zoomSpeed;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_E ) == GLFW_PRESS) {
        if(_position.z < _maxZoom)
        _position.z += 1 * deltaTime * zoomSpeed;
    }
    
	lastTime = currentTime;
}