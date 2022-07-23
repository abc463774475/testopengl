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
#define numVBOs 4

float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;
float pyrLocX, pyrLocY, pyrLocZ;

float lineLocX, lineLocY, lineLocZ;
float pointLocX, pointLocY, pointLocZ;

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

            1.0f,-1.0f,-1.0f,1,1,-1,-1,1,-1,

            1.0f,-1.0f,-1.0f,1,-1,1,1,1,-1,
			
            1.0f,-1.0f,1.0f,1,1,1,1,1,-1,
            
            1.0f,-1.0f,1.0f,-1,-1,1,1,1,1,

            -1.0f,-1.0f,1.0f,-1,1,1,1,1,1,
			
            -1.0f,-1.0f,1.0f,-1,-1,-1,-1,1,1,
			
            -1.0f,-1.0f,-1.0f,-1,1,-1,-1,1,1,

            -1.0f,-1.0f,1.0f,1,-1,1,1,-1,-1,

            1.0f,-1.0f,-1.0f,-1,-1,-1,-1,-1,1,
	
            -1.0f,1.0f,-1.0f,1,1,-1,1,1,1,
			
            1.0f,1.0f,1.0f,-1,1,1,-1,1,-1,
    };

    float pyramidPostions[54] = {
        -1,-1,1,1,-1,1,0,1,0,
        1,-1,1,1,-1,-1,0,1,0,
        1,-1,-1,-1,-1,-1,0,1,0,
        -1,-1,-1,-1,-1,1,0,1,0,
        -1,-1,-1,1,-1,1,-1,-1,1,
        1,-1,1,-1,-1,-1,1,-1,-1,
    };


    float linePosition[] = {
        -3,0,0,
		3,0,0,
    };

    float pointPosition[] = {
        1,1,0,
        -1,1,0,
        0,1,0,
    };
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidPostions), pyramidPostions, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(linePosition), linePosition, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pointPosition), pointPosition, GL_STATIC_DRAW);
}


void init(GLFWwindow* window) {
    renderingProgram = createShaderProgram();
    cameraX = 0.0f; cameraY = 0.0f; cameraZ = 16;
    cubeLocX = 0.0f; cubeLocY = -3.5f; cubeLocZ = 0.0f;
    pyrLocX = 0, pyrLocY = 2; pyrLocZ = 0;
	lineLocX = 0, lineLocY = 0, lineLocZ = 0;
	pointLocX = 0, pointLocY = 0, pointLocZ = 0;
    setupVertices();
}

void display(GLFWwindow *window, double currentTime){
    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram (renderingProgram) ;

    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

    glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	
    for (int i = 0; i < 24; i++) {
        mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX + 2*cos(i), cubeLocY + 2*sin(i), cubeLocZ + sin(i)));

        mvMat = vMat * mMat;

        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    {
        mMat = glm::translate(glm::mat4(1.0f), glm::vec3(lineLocX, lineLocY, lineLocZ));

        mvMat = vMat * mMat;

        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

        glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_LINES, 0, 2);
    }
	
    {
        mMat = glm::translate(glm::mat4(1.0f), glm::vec3(pointLocX, pointLocY, pointLocZ));

        mvMat = vMat * mMat;
		
        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

        glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_POINTS, 0, 3);
    }


    {
        mMat = glm::translate(glm::mat4(1.0f), glm::vec3(pyrLocX, pyrLocY, pyrLocZ));
        //mMat *= glm::translate(glm::mat4(1.0f), glm::vec3(sin(currentTime*2.0), cos(currentTime * 2.0),0.0 ));
        mMat *= glm::translate(glm::mat4(1.0f), glm::vec3(0, -4, 0));

        mMat *= glm::rotate(glm::mat4(1.0f), (float)((currentTime)), glm::vec3(0.0, 0.0, 1.0));

        mMat *= glm::translate(glm::mat4(1.0f), glm::vec3(0, 4, 0));

		
        mvMat = vMat* mMat;

        //mvMat *= glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
		
        // mvMat *= glm::rotate(glm::mat4(1), (float)(currentTime), glm::vec3(0.0,0.0, 1.0));

		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_TRIANGLES, 0, 18);
    }

}

int main(int argn,char **argv) {
    auto str = readShaderSource("vertShader.glsl");
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	GLFWwindow *window = glfwCreateWindow(1600, 1600, "Hello World", NULL, NULL);


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