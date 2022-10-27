#include "obj.hpp"

//Functions
std::queue<string> Obj::splitLine(string s, string delimiter)
{
    size_t pos = 0;
    std::queue<string> tokens;
    do {
        pos = s.find(delimiter);
        tokens.push(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());    
    } while (pos != std::string::npos);

    return tokens;
}

Obj::Obj(string filename) {
    //reader
    string line;
    std::ifstream inf(filename);
    while (!inf.eof()) {
        getline(inf, line);
        
        std::queue<string> qLine = splitLine(line, " ");

        string prefix = qLine.front();
        qLine.pop();

        if (prefix == "v") {
            std::vector<float> vertex = {};
            while (!qLine.empty()) {
                vertex.push_back(stof(qLine.front()));
                qLine.pop();
            }
            vertexes.push_back(vertex);
            continue;
        }
        if (prefix == "vt") {
            std::vector<float> textureCoord = {};
            while (!qLine.empty()) {
                textureCoord.push_back(stof(qLine.front()));
                qLine.pop();
            }
            textureCoords.push_back(textureCoord);
            continue;
        }
        if (prefix == "vn") {
            std::vector<float> normal = {};
            while (!qLine.empty()) {
                normal.push_back(stof(qLine.front()));
                qLine.pop();
            }
            normals.push_back(normal);
            continue;
        }
        if (prefix == "f") {
            std::vector<std::vector<int>> faces;
            while (!qLine.empty()) {
                std::queue<string> qface = splitLine(qLine.front(), "/");
                std::vector<int> face = {};
                while (qface.size()) {
                    face.push_back(stoi(qface.front()));
                    qface.pop();
                }
                faces.push_back(face);
                qLine.pop();
            }
            this->faces.push_back(faces);
            continue;
        }

    }
}

Obj::fvector2 Obj::getVertexes () { return vertexes; }

Obj::fvector2 Obj::getTextCoords () { return textureCoords; }

Obj::fvector2 Obj::getNormals () { return normals; }

Obj::ivector3 Obj::getFaces () { return faces; }
