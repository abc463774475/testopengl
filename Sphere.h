//
// Created by hxd on 2022/7/30.
//

#ifndef TEST1_SPHERE_H
#define TEST1_SPHERE_H
#include <cmath>
#include <vector>
#include <glm/glm.hpp>

#define M_PI 3.14152926f

class Sphere {
private:
    int numVertices;
    int numIndices;
    std::vector<int> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;

    void init(int );
    float toRadians(float degrees);

public:
    Sphere();
    Sphere(int prec);
    ~Sphere(){}

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

};


#endif //TEST1_SPHERE_H
