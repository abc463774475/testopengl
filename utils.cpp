//
// Created by hxd on 2022/7/11.
//

#include "utils.h"
#include <SOIL2/SOIL2.h>

#pragma warning(disable: 4996)

string readShaderSource(const char *shaderFile) {
    auto file = fopen(shaderFile, "r");
    if (file == nullptr) {
        throw runtime_error("unable to open file " + string(shaderFile));
    }
    string source;
    char line[2560];
    while (fgets(line, 256, file)) {
        source += string(line) + "\n";
    }
    fclose(file);
    return source;
}

void printProgramInfoLog(GLuint program) {
    int infoLogLen = 0;
    int charsWritten = 0;
    char *infoLog;

    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);

    if (infoLogLen > 0) {
        infoLog = new char[infoLogLen];
        glGetProgramInfoLog(program, infoLogLen, &charsWritten, infoLog);
        cout << infoLog << endl;
        delete[] infoLog;
    }
}

void printShaderLog(GLuint shader) {
    int len = 0;
    int chWrittn = 0;
    char *log;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);


    if (len > 0) {
        log = (char *) malloc(len);
        glGetShaderInfoLog(shader, len, &chWrittn, log);

        printf("getshader err log %s\n", log);
        free(log);
    } else {
        printf("no error\n");
    }
}


bool checkOpenGLError() {
    bool foundError = false;
    int glError = glGetError();
    while (glError != GL_NO_ERROR) {
        foundError = true;
        cout << "glError: " << glError << endl;
        glError = glGetError();
    }
    return foundError;
}

#define numVAOs 1

GLuint createShaderProgram() {
    auto vshaderSource = readShaderSource("../vertShader.glsl");
    auto fshaderSource = readShaderSource("../fragShader.glsl");

    auto vSharder = glCreateShader(GL_VERTEX_SHADER);
    auto fSharder = glCreateShader(GL_FRAGMENT_SHADER);
    auto s1 = vshaderSource.c_str();
    auto s2 = fshaderSource.c_str();

    glShaderSource(vSharder, 1, &s1, NULL);
    printShaderLog(vSharder);

    glCompileShader(vSharder);
    printShaderLog(vSharder);


    glShaderSource(fSharder, 1, &s2, NULL);
    printShaderLog(fSharder);


    glCompileShader(fSharder);
    printShaderLog(fSharder);

    checkOpenGLError();


    auto vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vSharder);
    glAttachShader(vfProgram, fSharder);
    glLinkProgram(vfProgram);

    return vfProgram;
}



GLuint loadTexture(const char *fileName) {
    auto txID = SOIL_load_OGL_texture(fileName, SOIL_LOAD_AUTO,
                                      SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    if (txID == 0) {
        throw runtime_error("unable to load texture " + string(fileName));
    }

    return txID;
}

float *goldAmbient() {
    static float ambient[] = { 0.24725f, 0.1995f, 0.0745f, 1.0f };
    return ambient;
}

float *goldDiffuse() {
    static float diffuse[] = { 0.75164f, 0.60648f, 0.22648f, 1.0f };
    return diffuse;
}

float *goldSpecular() {
    static float specular[] = { 0.628281f, 0.555802f, 0.366065f, 1.0f };
    return specular;
}

float goldShininess() {
    return 0.4f * 128.0f;
}

float *silverAmbient() {
    static float ambient[] = { 0.19225f, 0.19225f, 0.19225f, 1.0f };
    return ambient;
}

float *silverDiffuse() {
    static float diffuse[] = { 0.50754f, 0.50754f, 0.50754f, 1.0f };
    return diffuse;
}

float *silverSpecular() {
    static float specular[] = { 0.508273f, 0.508273f, 0.508273f, 1.0f };
    return specular;
}

float silverShininess() {
    return 0.4f * 128.0f;
}

float *bronzeAmbient() {
    static float ambient[] = { 0.2125f, 0.1275f, 0.054f, 1.0f };
    return ambient;
}

float *bronzeDiffuse() {
    static float diffuse[] = { 0.714f, 0.4284f, 0.18144f, 1.0f };
    return diffuse;
}

float *bronzeSpecular() {
    static float specular[] = { 0.393548f, 0.271906f, 0.166721f, 1.0f };
    return specular;
}

float bronzeShininess() {
    return 0.2f * 128.0f;
}

float *jadeAmbient() {
    static float ambient[] = { 0.135f, 0.2225f, 0.1575f, 0.95f };
    return ambient;
}

float *jadeDiffuse() {
    static float diffuse[] = { 0.5f, 0.5f, 0.5f, 0.95f };
    return diffuse;
}

float *jadeSpecular() {
    static float specular[] = { 0.316228f, 0.316228f, 0.316228f, 0.95f };
    return specular;
}

float jadeShininess() {
    return 0.1f * 128.0f;
}

