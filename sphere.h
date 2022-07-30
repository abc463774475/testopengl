//
// Created by hxd on 2022/7/24.
//

#ifndef TEST1_SPHERE_H
#define TEST1_SPHERE_H

#define SHPERE_RADIUS 1.0f
#define SHPERE_SLICES 32
#define SHPERE_STACKS 32

#include <vector>
#include <iostream>
#include "glm/glm.hpp"

using namespace std;

class sphere {
private:
    int slices, stacks;
    float radius;
    vector<vector<glm::vec3>> vertices;

public:
    void init();

    void generateVec3();

    sphere();

    ~sphere();

    vector<float> getVerticesPostion(vector<float> &vText);
};

#define M_PI 3.14159265358979323846


#endif //TEST1_SPHERE_H
