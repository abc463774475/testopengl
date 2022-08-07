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

using namespace std;

#define numVAOs 1
#define numVBOs 3

float cameraX, cameraY, cameraZ;
float sphereLocX, sphereLocY, sphereLocZ;

GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

GLuint cizhuan = 0;
GLuint cizhuan2 = 0;



GLuint mvLoc, projLoc,nLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat, invTrMat;

Sphere mySphere(48);

GLuint globalAmbLoc, ambLoc, diffLoc, specLoc, posLoc, mAmbLoc, mDiffLoc, mSpecLoc, mShinLoc;

glm::vec3 currentLightPos, lightPosV; // 在模型何视觉空间中的位置

float lightPos[3];
glm::vec3 initLightPosLoc = glm::vec3(5.0f, 5.0f, 5.0f);

// 白光特型
float globalAmbient[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
float lightAmbient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
float lightDiffuse[4] = {1,1,1,1};
float lightSpecular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

auto matAmb = jadeAmbient();
auto matDiff = jadeDiffuse();
auto matSpec = jadeSpecular();
float matShininess = jadeShininess();

void setupVertices() {
    auto ind = mySphere.getIndices();
    auto ver = mySphere.getVertices();
    auto nor = mySphere.getNormals();
    auto tex = mySphere.getTexCoords();

    vector<float> pvalues;
    vector<float> nvalues;
    vector<float> tvalues;

    auto numIndices = mySphere.getNumIndices();
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

}

void init(GLFWwindow *wwindow) {
    renderingProgram = createShaderProgram();
    setupVertices();
    cameraX = 1.0f;
    cameraY = 1.0f;
    cameraZ = 5.0f;

    sphereLocX = 1.0f;
    sphereLocY = 1.0f;
    sphereLocZ = 1.0f;


    cizhuan2 = loadTexture("../cizhuan.png");

    cizhuan = loadTexture("../cizhuan.jpg");

}


void installLights(glm::mat4 vMatrix) {
    lightPosV = glm::vec3(vMatrix * glm::vec4(currentLightPos, 1.0f));

    lightPos[0] = lightPosV.x;
    lightPos[1] = lightPosV.y;
    lightPos[2] = lightPosV.z;

    globalAmbLoc = glGetUniformLocation (renderingProgram, "globalAmbient");
    ambLoc = glGetUniformLocation (renderingProgram, "light.ambient");
    diffLoc = glGetUniformLocation (renderingProgram, "light.diffuse");
    specLoc = glGetUniformLocation (renderingProgram, "light.specular");
    posLoc = glGetUniformLocation (renderingProgram, "light.position");
    mAmbLoc = glGetUniformLocation (renderingProgram, "material.ambient");
    mDiffLoc = glGetUniformLocation (renderingProgram, "material.diffuse");
    mSpecLoc = glGetUniformLocation (renderingProgram, "material.specular");
    mShinLoc = glGetUniformLocation (renderingProgram, "material.shininess");

    glProgramUniform4fv(renderingProgram, globalAmbLoc, 1, globalAmbient);
    glProgramUniform4fv(renderingProgram, ambLoc, 1, lightAmbient);
    glProgramUniform4fv(renderingProgram, diffLoc, 1, lightDiffuse);
    glProgramUniform4fv(renderingProgram, specLoc, 1, lightSpecular);
    glProgramUniform3fv(renderingProgram, posLoc, 1, lightPos);
    glProgramUniform4fv(renderingProgram, mAmbLoc, 1, matAmb);
    glProgramUniform4fv(renderingProgram, mDiffLoc, 1, matDiff);
    glProgramUniform4fv(renderingProgram, mSpecLoc, 1, matSpec);
    glProgramUniform1f(renderingProgram, mShinLoc, matShininess);
}

void display(GLFWwindow *window, double currentTime) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(renderingProgram);

    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
    nLoc = glGetUniformLocation(renderingProgram, "normal_matrix");

    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float) width / (float) height;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));

    {
        mMat = glm::translate(glm::mat4(1.0f), glm::vec3(sphereLocX, sphereLocY, sphereLocZ));
        mMat *= glm::rotate(glm::mat4(1.0f), (float)((currentTime * 2)), glm::vec3(1.0, 1.0, 1.0));

        mvMat = vMat * mMat;

        currentLightPos = glm::vec3(initLightPosLoc.x, initLightPosLoc.y, initLightPosLoc.z);
        installLights (vMat);

        invTrMat = glm::transpose(glm::inverse(mvMat));

        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
        glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        {
            glBindBuffer (GL_ARRAY_BUFFER, vbo[2]);
            glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0);
            glEnableVertexAttribArray(1);
        }

        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_TRIANGLES, 0, mySphere.getNumIndices());
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