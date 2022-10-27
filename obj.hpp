#ifndef GLOBJ_H
#define GLOBJ_H

#include <cmath>
#include <cstddef>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <array>
#include <math.h>

using std::string;

class Obj {
    using fvector2 = std::vector<std::vector<float>>;
    using ivector3 = std::vector<std::vector<std::vector<int>>>;

    private:
    fvector2 vertexes;
    fvector2 textureCoords;
    fvector2 normals;
    ivector3 faces;

    //Aux Functions
    std::queue<string> splitLine(string s, string delimiter);

    public:
    //Functions
    Obj(string filename);

    fvector2 getVertexes ();

    fvector2 getTextCoords ();

    fvector2 getNormals ();

    ivector3 getFaces (); 
};

#endif
