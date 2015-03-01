/*
 * main.cpp
 *
 *  Created on: 18 okt. 2014
 *      Author: bertbosch
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <libpng16/png.h>
#include <GLUT/glut.h>
#include <string>

#include "controls.h"
#include "Level.h"
#include "GameState.h"

GLFWwindow* window;
Camera camera;
Level level;
GameState gamestate;
int width = 1100;
int height = 700;
int camPosX = 0;
int camPosY = 0;
float camPosZ = 0.1;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void initGL(int widthR, int heightR)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, (GLsizei)widthR, (GLsizei)heightR);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1 * (GLfloat) height / (GLfloat) width, (GLfloat) height/ (GLfloat) width, -100, 100);
    // ----- OpenGL settings -----
    glfwSwapInterval(1); 		// Lock to vertical sync of monitor (normally 60Hz, so 60fps)
    
    glEnable(GL_SMOOTH);		// Enable (gouraud) shading
    
    glDisable(GL_DEPTH_TEST); 	// Disable depth testing
    
    glEnable(GL_BLEND);		// Enable blending (used for alpha) and blending function to use
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glLineWidth(1.0f);		// Set a 'chunky' line width
    
    glEnable(GL_LINE_SMOOTH);	// Enable anti-aliasing on lines
    
    glPointSize(1.0f);		// Set a 'chunky' point size
    
    glEnable(GL_POINT_SMOOTH);
}

void initGame(){
    level = Level(0);
    gamestate.setGameState(1);
}

void drawLevel(){
    level.updateLevel();
    level.drawLevel();
}

void drawScene(){
    // Clear the screen
    glClearColor(0.0, 0.0, 0.0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Reset the matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //double a = width / height;
    glOrtho(-1, 1, -1 * (GLfloat) height / (GLfloat) width, (GLfloat) height/ (GLfloat) width, -100, 100);
    
    glScaled(camera.getPosition().z, camera.getPosition().z, 1);
    glTranslatef(camera.getPosition().x, camera.getPosition().y, 0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    drawLevel();
    
    glfwSwapBuffers(window);
    glfwPollEvents();
}


int main(void)
{
    camera.setPosition(glm::vec3(camPosX,camPosY,camPosZ));
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow(width, height, "Simple example", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }
    initGL(width,height);
    
    initGame();
    
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetErrorCallback(error_callback);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    
    while (!glfwWindowShouldClose(window))
    {
        camera.computeInputs(window, &level, &gamestate);
        camera.computeInputsMouse(window, &level, &gamestate);
        drawScene();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
