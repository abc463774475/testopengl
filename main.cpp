//
// Created by hxd on 2022/7/30.
//
#include "Sphere.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "utils.h"
#include "Sphere.h"
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Torus.h"

using namespace std;

#define numVAOs 1
#define numVBOs 4

float cameraX, cameraY, cameraZ;
float sphereLocX, sphereLocY, sphereLocZ;

GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

GLuint cizhuan = 0;


GLuint mvLoc, projLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat;


Torus myTorus(48, 0.5f, 0.2f);

void setupVertices() {
    auto ind = myTorus.getIndices();
    auto ver = myTorus.getVertices();
    auto nor = myTorus.getNormals();
    auto tex = myTorus.getTexCoords();

    vector<float> pvalues;
    vector<float> nvalues;
    vector<float> tvalues;

    auto numIndices = myTorus.getNumIndices();
    for (int i = 0; i < numIndices; i++) {
        pvalues.push_back(ver[ind[i]].x);
        pvalues.push_back(ver[ind[i]].y);
        pvalues.push_back(ver[ind[i]].z);

        nvalues.push_back(nor[ind[i]].x);
        nvalues.push_back(nor[ind[i]].y);
        nvalues.push_back(nor[ind[i]].z);

        tvalues.push_back(tex[ind[i]].s);
        tvalues.push_back(tex[ind[i]].t);
    }

    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, pvalues.size() * sizeof(float), &pvalues[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, tvalues.size() * sizeof(float), &tvalues[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, nvalues.size() * sizeof(float), &nvalues[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
    glBufferData(GL_ARRAY_BUFFER, ind.size() * sizeof(float), &ind[0], GL_STATIC_DRAW);
}

void init(GLFWwindow *wwindow) {
    renderingProgram = createShaderProgram();
    setupVertices();
    cameraX = 0.0f;
    cameraY = 0.0f;
    cameraZ = 5.0f;

    sphereLocX = 0.0f;
    sphereLocY = 0.0f;
    sphereLocZ = 0.0f;

    cizhuan = loadTexture("cizhuan.png");
}

void display(GLFWwindow *window, double currentTime) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(renderingProgram);

    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float) width / (float) height;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));

    {
        mMat = glm::translate(glm::mat4(1.0f), glm::vec3(sphereLocX, sphereLocY, sphereLocZ));
        mMat *= glm::rotate(glm::mat4(1.0f), (float)((currentTime * 2)), glm::vec3(1.0, 1.0, 1.0));

        mvMat = vMat * mMat;

        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glBindBuffer (GL_ARRAY_BUFFER, vbo[1]);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture (GL_TEXTURE_2D, cizhuan);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
        glDrawElements(GL_TRIANGLES, myTorus.getNumIndices(), GL_UNSIGNED_INT, 0);
    }
}

int main() {
    if (!glfwInit()) {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow *window = glfwCreateWindow(1600, 1600, "Sphere", NULL, NULL);
    if (window == NULL) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        cout << "Failed to initialize GLEW" << endl;
        return -1;
    }

    glfwSwapInterval(1);

    init(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}