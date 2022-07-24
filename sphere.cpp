//
// Created by hxd on 2022/7/24.
//

#include "sphere.h"

#include <math.h>

void sphere::init() {
    stacks = 30;
    slices = 30;
    radius = 1.0f;
}


sphere::sphere() {
    init();
}

sphere::~sphere() {

}


// 先建立一个半圆，
void sphere::generateVec3() {
    for (int i = 0; i < stacks + 1 ; i++) {
        vector<glm::vec3> v0;
        for (int j = 0; j < slices; j++) {
            auto y0 = radius * i / (stacks);
            auto r0 = sqrt(radius * radius - y0 * y0);
            auto x0 = r0 * cos(2 * M_PI * j / slices);
            auto z0 = r0 * sin(2 * M_PI * j / slices);

            v0.push_back(glm::vec3(x0, y0, z0));
        }
        vertices.push_back(v0);
    }


//    {
//        // the last, 还是size设置味 slice
//        vector<glm::vec3> v0 ;
//        v0.push_back(glm::vec3(0, radius, 0));
//        vertices.push_back(v0);
//    }


   /* {
        vector<glm::vec3> v0;
        auto v3 = glm::vec3 (0,radius,0);
        for (int i = 0; i < slices; i++){
            v0.push_back(v3);
        }
        vertices.push_back(v0);
    }*/
}


vector<float> sphere::getVerticesPostion() {
    generateVec3();
    int i = 0;
    auto trangle_num = slices * (stacks) + 2;
    auto size = trangle_num * 3;
    vector<float> vertices_position;
    for (int j = 0; j < stacks ; j++) {
        for (int k = 0; k < slices -1; k++) {
            auto p1 = vertices[j][k];
            auto p2 = vertices[j][k+1];
            auto p3 = vertices[j+1][k];
            auto p4 = vertices[j+1][k+1];
			
            vertices_position.push_back(p1.x);
            vertices_position.push_back(p1.y);
            vertices_position.push_back(p1.z);
            vertices_position.push_back(p2.x);
            vertices_position.push_back(p2.y);
            vertices_position.push_back(p2.z);
            vertices_position.push_back(p3.x);
            vertices_position.push_back(p3.y);
            vertices_position.push_back(p3.z);


            vertices_position.push_back(p4.x);
            vertices_position.push_back(p4.y);
            vertices_position.push_back(p4.z);
            vertices_position.push_back(p3.x);
            vertices_position.push_back(p3.y);
            vertices_position.push_back(p3.z);
            vertices_position.push_back(p2.x);
            vertices_position.push_back(p2.y);
            vertices_position.push_back(p2.z);
        }


        auto p1 = vertices[j][slices - 1];
        auto p2 = vertices[j][0];
        auto p3 = vertices[j+1][slices - 1];
        auto p4 = vertices[j+1][0];
        vertices_position.push_back(p1.x);
        vertices_position.push_back(p1.y);
        vertices_position.push_back(p1.z);
        vertices_position.push_back(p2.x);
        vertices_position.push_back(p2.y);
        vertices_position.push_back(p2.z);
        vertices_position.push_back(p3.x);
        vertices_position.push_back(p3.y);
        vertices_position.push_back(p3.z);


        vertices_position.push_back(p4.x);
        vertices_position.push_back(p4.y);
        vertices_position.push_back(p4.z);
        vertices_position.push_back(p3.x);
        vertices_position.push_back(p3.y);
        vertices_position.push_back(p3.z);
        vertices_position.push_back(p2.x);
        vertices_position.push_back(p2.y);
        vertices_position.push_back(p2.z);
    }

    return vertices_position;
}