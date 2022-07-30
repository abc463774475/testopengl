//
// Created by hxd on 2022/7/30.
//

#include "Sphere.h"
#include <iostream>

using namespace std;

Sphere::Sphere() {
    init(48);
}

Sphere::Sphere(int prec) {
    init(prec);
}

float Sphere::toRadians(float degrees) {
    return degrees * M_PI / 180;
}

void Sphere::init(int prec) {
    numVertices = (prec + 1) * (prec + 1);
    numIndices = prec * prec * 6;

    indices.resize(numIndices);
    vertices.resize(numVertices);
    normals.resize(numVertices);
    texCoords.resize(numVertices);

    for (int i = 0; i <= prec; i++) {
        for (int j = 0; j <= prec; j++) {
            auto y = cos(toRadians(180.0f - i * 180.0f / prec));

            auto x = -cos(toRadians(j * 360.0f / prec))* abs(cos(asin(y))) ;

            auto z = sin(toRadians(j * 360.0f / prec))* abs(cos(asin(y)));
            vertices[i * (prec + 1) + j] = glm::vec3(x, y, z);
            normals[i * (prec + 1) + j] = glm::vec3(x, y, z);

            texCoords[i * (prec + 1) + j] = glm::vec2((float )j/prec, (float )i/prec);
        }
    }

    // 计算三角形索引
    for (int i = 0; i < prec; i++) {
        for (int j = 0; j < prec; j++) {
            indices[i * prec * 6 + j * 6 + 0] = i * (prec + 1) + j;
            indices[i * prec * 6 + j * 6 + 1] = i * (prec + 1) + j + 1;
            indices[i * prec * 6 + j * 6 + 2] = (i + 1) * (prec + 1) + j;

            indices[i * prec * 6 + j * 6 + 3] = (i) * (prec + 1) + j + 1;
            indices[i * prec * 6 + j * 6 + 4] = (i + 1) * (prec + 1) + j + 1;
            indices[i * prec * 6 + j * 6 + 5] = (i + 1) * (prec + 1) + j;
        }
    }
}