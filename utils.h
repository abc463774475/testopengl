//
// Created by hxd on 2022/7/11.
//

#ifndef TEST1_UTILS_H
#define TEST1_UTILS_H

#include <gl/glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm\glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace std;
string readShaderSource(const char* shaderFile);

GLuint createShaderProgram();

GLuint loadTexture (const char* filename);

float * goldAmbient ();
float * goldDiffuse ();
float * goldSpecular ();
float  goldShininess ();

float * silverAmbient ();
float * silverDiffuse ();
float * silverSpecular ();
float  silverShininess ();

float * bronzeAmbient ();
float * bronzeDiffuse ();
float * bronzeSpecular ();
float  bronzeShininess ();

#endif //TEST1_UTILS_H
