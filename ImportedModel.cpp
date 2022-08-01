//
// Created by hxd on 2022/8/1.
//

#include "ImportedModel.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

ImportedModel::ImportedModel(std::string path) {
    ModelImporter importer;
    importer.parseOBJ(path);

    numVertices = importer.getNumVertices();
    auto verts = importer.getVertices();
    auto norms = importer.getNormals();
    auto tcs = importer.getTexCoords();

    for (int i = 0; i < numVertices; i++) {
        vertices.push_back(glm::vec3(verts[i*3], verts[i*3+1], verts[i*3+2]));
        normals.push_back(glm::vec3(norms[i*3], norms[i*3+1], norms[i*3+2]));
        texCoords.push_back(glm::vec2(tcs[i*2], tcs[i*2+1]));
    }
}


ModelImporter::ModelImporter() {

}

void ModelImporter::parseOBJ(std::string path) {
    ifstream file(path);
    string line;
    while (getline(file, line)) {
        if (line.substr(0,2) == "v ") {
            stringstream ss(line);
            string s;
            vector<float> vals;
            while (getline(ss, s, ' ')) {
                vals.push_back(stof(s));
            }
            vertVals.push_back(vals[0]);
            vertVals.push_back(vals[1]);
            vertVals.push_back(vals[2]);
        } else if (line.substr(0,2) == "vn") {
            stringstream ss(line);
            string s;
            vector<float> vals;
            while (getline(ss, s, ' ')) {
                vals.push_back(stof(s));
            }
            normVals.push_back(vals[0]);
            normVals.push_back(vals[1]);
            normVals.push_back(vals[2]);
        } else if (line.substr(0,2) == "vt") {
            stringstream ss(line);
            string s;
            vector<float> vals;
            while (getline(ss, s, ' ')) {
                vals.push_back(stof(s));
            }
            stVals.push_back(vals[0]);
            stVals.push_back(vals[1]);
        } else if (line.substr(0,2) == "f ") {
            stringstream ss(line);
            string s;
            vector<float> vals;
            while (getline(ss, s, ' ')) {
                vals.push_back(stof(s));
            }
            triangleVerts.push_back(vals[0]);
            triangleVerts.push_back(vals[1]);
            triangleVerts.push_back(vals[2]);
        }
    }
    file.close();
}