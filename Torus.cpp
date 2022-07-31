//
// Created by hxd on 2022/7/31.
//

#include "Torus.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

Torus::Torus() {
    prec = 48;
    inner = 0.5f;
    outer = 0.2f;
    init();
}

Torus::Torus(int prec, float inner, float outer) {
    this->prec = prec;
    this->inner = inner;
    this->outer = outer;
    init();
}

float Torus::toRadians(float degrees) {
    return degrees * M_PI / 180;
}

void Torus::init() {
    numVertices = (prec + 1) * (prec + 1);
    numIndices = prec * prec * 2 * 3;
    vertices.resize(numVertices);
    normals.resize(numVertices);
    texCoords.resize(numVertices);
    sTangents.resize(numVertices);
    tTangents.resize(numVertices);
    indices.resize(numIndices);

    for (int i = 0; i < prec + 1; i++) {
        auto amt = toRadians(i * 360.0 / prec);

        auto rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 0.0f, 1.0f));
        glm::vec3 initPos(rMat * glm::vec4(outer, 0.0f, 1.0f, 1.0f));

        vertices[i] = initPos + glm::vec3(inner, 0.0f, 0.0f);
        texCoords[i] = glm::vec2(0.0f, i / (float) prec);

        rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 0.0f, 1.0f));

        tTangents[i] = glm::vec3(rMat * glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));

        sTangents[i] = glm::vec3(glm::vec3(0, 0, -1));

        normals[i] = glm::cross(tTangents[i], sTangents[i]);
    }

    for (int ring =1; ring < prec +1; ring++){
        for (int vert = 0 ; vert < prec +1; vert++){
            auto i = vert;
            auto amt = toRadians(ring * 360.0 / prec);
            auto rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));

            vertices[ring*(prec+1) +i] = glm::vec3 (rMat * glm::vec4(vertices[i], 1.0f));

            texCoords[ring * (prec+1) + vert] = glm::vec2(ring*2.0f / (float) prec,texCoords[vert].t);
            if (texCoords[ring * (prec+1) + vert].s > 1.0f) {
                texCoords[ring * (prec+1) + vert].s -= 1.0f;
            }

            rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));

            sTangents[ring*(prec+1) +i] = glm::vec3(rMat* glm::vec4(sTangents[i], 1.0f));

            rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));

            tTangents[ring*(prec+1) +i] = glm::vec3(rMat* glm::vec4(tTangents[i], 1.0f));

            rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));

            normals[ring*(prec+1) +i] = glm::vec3(rMat* glm::vec4(normals[i], 1.0f));
        }
    }

    for (int ring = 0 ; ring < prec ; ring++){
        for (int vert = 0 ; vert < prec ; vert++){
            auto i = ring*(prec+1) + vert;
            indices[ring*prec*6 + vert*6 + 0] = i;
            indices[ring*prec*6 + vert*6 + 1] = i + 1;
            indices[ring*prec*6 + vert*6 + 2] = i + prec + 1;
            indices[ring*prec*6 + vert*6 + 3] = i + 1;
            indices[ring*prec*6 + vert*6 + 4] = i + prec + 1;
            indices[ring*prec*6 + vert*6 + 5] = i + prec + 2;
        }
    }
}