//
//  controls.cpp
//  opengl
//
//  Created by Bert Bosch on 13-10-14.
//  Copyright (c) 2014 BoschIt. All rights reserved.
//

#include "controls.h"
float translateSpeed = 2.5f;
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

void Camera::computeInputs(GLFWwindow* window,Level *level,GameState* gamestate){
    // glfwGetTime is called only once, the first time this function is called
    switch (gamestate->getGameState()) {
        case MENU:
            computeInputsMenu(window, level, gamestate);
            break;
        case GAME:
            computeInputsGame(window, level, gamestate);
            break;
        default:
            break;
    }
}

void Camera::computeInputsMouse(GLFWwindow* window,Level *level,GameState* gamestate){
    switch (gamestate->getGameState()) {
        case MENU:
            computeInputsMenuMouse(window, level, gamestate);
            break;
        case GAME:
            computeInputsGameMouse(window, level, gamestate);
            break;
        default:
            break;
    }
}

void Camera::computeInputsGame(GLFWwindow* window,Level *level,GameState* gamestate){
    static double lastTime = glfwGetTime();
    
    // Compute time difference between current and last frame
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);
    Player *player = level->getPlayer(0);
    float newXPos = player->getXPos();
    float newYPos = player->getYPos();
    
    // Move forward
    if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
        newYPos += 1 * deltaTime * translateSpeed;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_S ) == GLFW_PRESS){
        newYPos -= 1 * deltaTime * translateSpeed;
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_A ) == GLFW_PRESS){
        newXPos -= 1 * deltaTime * translateSpeed;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_D ) == GLFW_PRESS){
        newXPos += 1 * deltaTime * translateSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE ) == GLFW_PRESS){
            level->pauseGame();
    }
    
    
    player->setNewPos(newXPos, newYPos);
    
    /*
     if (glfwGetKey(window, GLFW_KEY_Q ) == GLFW_PRESS) {
     if(_position.z >_minZoom){
     _position.z -= 1 * deltaTime * zoomSpeed;
     }
     }
     if (glfwGetKey(window, GLFW_KEY_E ) == GLFW_PRESS) {
     if(_position.z < _maxZoom)
     _position.z += 1 * deltaTime * zoomSpeed;
     }
     */
    lastTime = currentTime;
    
}
void Camera::computeInputsGameMouse(GLFWwindow* window,Level *level,GameState* gamestate){
    Player *player = level->getPlayer(0);
    
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS){
        glm::vec3 worldPos = getMouseWorldPos(window);
        player->shootPrimary(worldPos[0], worldPos[1]);
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS){
        glm::vec3 worldPos = getMouseWorldPos(window);
        player->shootSecondary(worldPos[0], worldPos[1]);
    }
    glm::vec3 worldPos = getMouseWorldPos(window);
    player->updateAngleMousePos(worldPos[0],worldPos[1]);
}

void Camera::computeInputsMenu(GLFWwindow* window,Level *level,GameState* gamestate){
    
}
void Camera::computeInputsMenuMouse(GLFWwindow* window,Level *level,GameState* gamestate){
    
}

glm::vec3 Camera::getMouseWorldPos(GLFWwindow* window){
    GLfloat winX, winY, winZ;
    double mouseXPos, mouseYPos;
    glfwGetCursorPos(window, &mouseXPos, &mouseYPos);
    GLint viewportL[4];
    glGetIntegerv( GL_VIEWPORT, viewportL );
    
    winX = (float)mouseXPos;
    winY = (float)viewportL[3] - (float)mouseYPos;
    winZ = 0;
    glm::vec4 viewport = glm::vec4(viewportL[0], viewportL[1], viewportL[2], viewportL[3]);
    glm::mat4 viewMatrix = glm::mat4(1.0f); //View matrix is translated 5 units back.
    viewMatrix = glm::scale(viewMatrix, glm::vec3(_position.z, _position.z, 1));
    viewMatrix = glm::translate(viewMatrix,glm::vec3(_position.x, _position.y, 0));
    glm::mat4 projectionMatrix = glm::ortho<float>(-1, 1, -1 * (GLfloat) height / (GLfloat) width, (GLfloat) height/ (GLfloat) width, -1, 1);
    
    glm::vec3 win = glm::vec3(winX,winY,winZ);
    glm::vec3 v = glm::unProject(win, viewMatrix, projectionMatrix, viewport);
    return v;
}



