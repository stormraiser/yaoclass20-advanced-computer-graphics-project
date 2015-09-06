#pragma once

#include "Core/Primitive.h"
#include <vector>
#include <tuple>

using namespace std;

struct MeshOctreeNode{
    int children[8];
    vector<int> faceList;
    bool isLeaf;

    MeshOctreeNode()
        {for (int i = 0; i < 8; i++) children[i] = -1; isLeaf = true;}
};

class MeshObject: public Primitive{
private:
    vector<Point> vertices;
    vector<double> weights;
    vector<double> areas;
    vector<Vector> vertexNormals, faceNormals;
    vector<tuple<int, int, int> > faces;
    vector<MeshOctreeNode> tree;
    int vNum, fNum, rayDir;
    BoundingBox bbox;
    bool normalBlend;

    bool hitFace(const Ray &ray, int k, double &t);
    void makeTree(int k, int depth, BoundingBox box);
    bool faceCubeIntersect(int k, const BoundingBox &box);
    int hitOctree(const Ray &ray, int k, const BoundingBox &box, double &t);

public:
    MeshObject(char *filename, int _layer = 0, bool _normalBlend = true): Primitive(_layer), normalBlend(_normalBlend)
        {loadOBJ(filename);}
    void loadOBJ(char *filename);

    PRIMITIVE_FUNC

    BoundingBox baseBoundingBox()
        {return bbox;}
};
