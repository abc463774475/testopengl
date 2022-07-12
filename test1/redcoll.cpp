//
// Created by hxd on 2022/7/10.
//

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm\glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../utils.h"


#define numVAOs 1
#define numVBOs 2

float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;

GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

GLuint mvLoc, projLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat;

void setupVertices (void){
    float vertexPositions[108] = {
            -1.0f,1.0f,-1.0f,-1,-1,-1,1,-1,-1,
            1.0f,-1.0f,-1.0f,1,1,-1,1,1,-1,
            1.0f,-1.0f,-1.0f,1,-1,1,1,1,-1,
			
            1.0f,-1.0f,1.0f,1,1,1,1,1,-1,
            
            1.0f,-1.0f,1.0f,-1,-1,1,1,1,1,

			
            -1.0f,-1.0f,1.0f,-1,-1,1,1,1,1,
			
            -1.0f,-1.0f,1.0f,-1,-1,-1,-1,1,1,
			
			
            -1.0f,-1.0f,-1.0f,-1,1,-1,-1,1,1,

			
            -1.0f,-1.0f,1.0f,1,-1,1,1,-1,-1,

			
            1.0f,-1.0f,-1.0f,-1,-1,-1,1,-1,1,

			
            -1.0f,1.0f,-1.0f,1,1,-1,1,1,1,
			
            1.0f,1.0f,1.0f,-1,1,1,-1,1,-1,
    };

    glGenVertexArrays(1, vao);

    glBindVertexArray(vao[0]);

    glGenBuffers(numVBOs, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
}


void init(GLFWwindow* window) {
    /*renderingProgram = */
    renderingProgram = createShaderProgram();
    cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f;
    cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f;
    setupVertices();
}

void display(GLFWwindow *window, double currentTime){
    glClear(GL_DEPTH_BUFFER_BIT);
    glUseProgram (renderingProgram) ;

    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

    glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, - cameraY, - cameraZ)); 
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX,cubeLocY, cubeLocZ));
    mvMat = vMat* mMat;

    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 0 ,0 );
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

int main(int argn,char **argv) {
    auto str = readShaderSource("vertShader.glsl");
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	GLFWwindow *window = glfwCreateWindow(600, 600, "Hello World", NULL, NULL);


    glfwMakeContextCurrent(window);
	
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

    glfwSwapInterval(1);
	
    init(window);
	
    while (!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
    }
    glfwDestroyWindow(window);
	glfwTerminate();
}