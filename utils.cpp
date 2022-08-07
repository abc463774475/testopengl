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
	char line[256];
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
    glShaderSource(fSharder, 1, &s2, NULL);

    glCompileShader(vSharder);
    glCompileShader(fSharder);

    checkOpenGLError();

    printShaderLog(vSharder);
    printShaderLog(fSharder);

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