//
// Created by hxd on 2022/8/1.
//

#ifndef TEST1_IMPORTEDMODEL_H
#define TEST1_IMPORTEDMODEL_H
#include <vector>
#include <glm/glm.hpp>
#include <string>

class ImportedModel {
private:
    int numVertices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;

public:
    ImportedModel(std::string path);
    ~ImportedModel(){

    }

    int getNumVertices(){
        return numVertices;
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


class ModelImporter {
private:
    std::vector<float> vertVals;
    std::vector<float> normVals;
    std::vector<float> stVals;

    std::vector<float> triangleVerts;
    std::vector<float> normals;
    std::vector<float> texCoords;

public:
    ModelImporter();
    void parseOBJ(std::string path);

    int getNumVertices(){
        return triangleVerts.size()/3;
    }

    std::vector<float> getVertices(){
        return triangleVerts;
    }
    std::vector<float> getNormals(){
        return normals;
    }
    std::vector<float> getTexCoords(){
        return texCoords;
    }
};

#endif //TEST1_IMPORTEDMODEL_H
