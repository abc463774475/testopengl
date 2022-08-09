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

// 金
float * goldAmbient ();
float * goldDiffuse ();
float * goldSpecular ();
float  goldShininess ();

// 银
float * silverAmbient ();
float * silverDiffuse ();
float * silverSpecular ();
float  silverShininess ();

// 青铜
float * bronzeAmbient ();
float * bronzeDiffuse ();
float * bronzeSpecular ();
float  bronzeShininess ();

// 翡翠
float * jadeAmbient ();
float * jadeDiffuse ();
float * jadeSpecular ();
float  jadeShininess ();

// 黑曜石
float * obsidianAmbient ();
float * obsidianDiffuse ();
float * obsidianSpecular ();
float  obsidianShininess ();

// 珍珠
float * pearlAmbient ();
float * pearlDiffuse ();
float * pearlSpecular ();
float  pearlShininess ();

// 绿宝石
float * emeraldAmbient ();
float * emeraldDiffuse ();
float * emeraldSpecular ();
float  emeraldShininess ();

// 铬合金
float * chromeAmbient ();
float * chromeDiffuse ();
float * chromeSpecular ();
float  chromeShininess ();

// 玻璃
float * glassAmbient ();
float * glassDiffuse ();
float * glassSpecular ();
float  glassShininess ();

#endif //TEST1_UTILS_H
