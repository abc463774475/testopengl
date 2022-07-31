//
// Created by hxd on 2022/7/31.
//

#ifndef TEST1_TORUS_H
#define TEST1_TORUS_H

#include <cmath>
#include <vector>
#include <glm/glm.hpp>

#define M_PI 3.1415926f

class Torus {
private:
    int numVertices;
    int numIndices;
    int prec = 0;
    float inner;
    float outer;

    std::vector<int> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> sTangents;
    std::vector<glm::vec3> tTangents;

    void init();

    float toRadians(float degrees);

public:
    Torus();
    Torus(int prec, float inner, float outer);
    ~Torus(){}

    int getNumVertices(){
        return numVertices;
    }
    int getNumIndices(){
        return numIndices;
    }
    std::vector<int> getIndices(){
        return indices;
    }
    std::vector<glm::vec3> getVertices(){
        return vertices;
    }
    std::vector<glm::vec3> getNormals(){
        return normals;
    }
    std::vector<glm::vec2> getTexCoords(){
        return texCoords;
    }
    std::vector<glm::vec3> getSTangents(){
        return sTangents;
    }
    std::vector<glm::vec3> getTTangents(){
        return tTangents;
    }
};


#endif //TEST1_TORUS_H
