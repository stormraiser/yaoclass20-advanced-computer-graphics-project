#include "Primitives/MeshObject.h"
#include <fstream>
#include <cstdio>

#define LEAF_SIZE_LIMIT 10
#define DEPTH_LIMIT 10

using namespace std;

int subtreeXorMask[8] = {0, 1, 2, 4, 3, 5, 6, 7};

void MeshObject::loadOBJ(char *filename){
    ifstream fin(filename);
    char ch;
    int p, q, r, i;
    Point pos;
    Vector normal, v1, v2;
    double wp, wq, wr;

    bbox = BoundingBox();
    while (!fin.eof()){
        fin >> ch;
        if (fin.eof())
            break;
        if (ch == 'v'){
            fin >> pos.x >> pos.y >> pos.z;
            vertices.push_back(pos);
            bbox.extend(pos);
        }
        else if (ch == 'f'){
            fin >> p >> q >> r;
            p--;
            q--;
            r--;
            faces.emplace_back(p, q, r);
        }
        fin.ignore(10000, '\n');
    }
    fin.close();

    vNum = vertices.size();
    fNum = faces.size();
    vertexNormals.assign(vNum, Vector(0, 0, 0));
    faceNormals.assign(fNum, Vector(0, 0, 0));
    weights.assign(vNum, 0);
    areas.assign(fNum, 0);
    for (i = 0; i < fNum; i++){
        tie(p, q, r) = faces[i];
        v1 = vertices[q] - vertices[p];
        v2 = vertices[r] - vertices[p];
        normal = (v1 ^ v2);
        areas[i] = normal.norm();
        normal /= areas[i];
        faceNormals[i] = normal;
        wp = acos(v1 * v2 / v1.norm() / v2.norm());
        wq = acos(v1 * (v1 - v2) / v1.norm() / (v1 - v2).norm());
        wr = acos(v2 * (v2 - v1) / v2.norm() / (v2 - v1).norm());
        vertexNormals[p] += wp * normal;
        vertexNormals[q] += wq * normal;
        vertexNormals[r] += wr * normal;
        weights[p] += wp;
        weights[q] += wq;
        weights[r] += wr;
    }
    for (i = 0; i < vNum; i++)
        vertexNormals[i] /= weights[i];

    tree.resize(1);
    tree[0].faceList.resize(fNum);
    for (i = 0; i < fNum; i++)
        tree[0].faceList[i] = i;

    makeTree(0, 0, bbox);
}

void MeshObject::makeTree(int k, int depth, BoundingBox box){
    if ((tree[k].faceList.size() <= LEAF_SIZE_LIMIT) || (depth >= DEPTH_LIMIT))
        return;
    int i, j, p;
    BoundingBox bt;
    tree[k].isLeaf = false;
    vector<int> tmp;
    for (i = 0; i < 8; i++){
        tmp.clear();
        bt = box.octant(i);
        for (j = 0; j < tree[k].faceList.size(); j++){
            if (faceCubeIntersect(tree[k].faceList[j], bt))
                tmp.push_back(tree[k].faceList[j]);
        }
        if (!tmp.empty()){
            //printf("!\n");
            p = tree.size();
            tree.resize(p + 1);
            tree[k].children[i] = p;
            tree[p].faceList = tmp;
            makeTree(p, depth + 1, bt);
        }
    }
    tree[k].faceList.clear();
}

bool MeshObject::hitFace(const Ray &ray, int k, double &t){
    int p, q, r;
    std::tie(p, q, r) = faces[k];
    t = ((vertices[p] - ray.o) * faceNormals[k]) / (ray.d * faceNormals[k]);
    if ((t < ray.tMin) || (t > ray.tMax))
        return false;
    Point h = ray.o + t * ray.d;
    double s1 = ((h - vertices[p]) ^ (vertices[r] - vertices[p])) * faceNormals[k] / areas[k];
    double s2 = ((vertices[q] - vertices[p]) ^ (h - vertices[p])) * faceNormals[k] / areas[k];
    return (s1 > 0) && (s2 > 0) && (s1 + s2 < 1);
}

bool MeshObject::faceCubeIntersect(int k, const BoundingBox &box){
    int i;
    int c = 0;
    int p, q, r;
    BoundingBox bt;
    std::tie(p, q, r) = faces[k];
    for (i = 0; i < 8; i++)
        c += ((box.vertex(i) - vertices[p]) * faceNormals[k] > 0);
    if ((c == 0) || (c == 8))
        return false;
    bt.extend(vertices[p]).extend(vertices[q]).extend(vertices[r]);
    return !(box.disjoint(bt));
}

int MeshObject::hitOctree(const Ray &ray, int k, const BoundingBox &box, double &t){
    double tMin2, tMax2, t2;
    box.intersectionInterval(tMin2, tMax2);
    if (tMin2 > tMax2)
        return -1;
    t = INF;
    int ret = -1, i, j;
    if (tree[k].isLeaf){
        for (i = 0; i < tree[k].faceList.size(); i++)
            if (hitFace(ray, tree[k].faceList[i], t2))
                if (t2 < t){
                    t = t2;
                    ret = tree[k].faceList[i];
                }
        if (t < tMax2)
            return ret;
        else
            return -1;
    }
    else{
        for (i = 0; i < 8; i++){
            j = rayDir ^ subtreeXorMask[i];
            if (tree[k].children[j] != -1){
                ret = hitOctree(ray, tree[k].children[j], box.octant(subtreeXorMask[i]), t);
                if (ret != -1)
                    return ret;
            }
        }
    }
    return ret;
}

bool MeshObject::hit(Ray ray){
    HIT_ROUTINE
    double t;
    rayDir = dirRevIndex(ray.d.x, ray.d.y, ray.d.z);
    return (hitOctree(ray, 0, bbox.rayIntersection(ray), t) != -1);
}

bool MeshObject::hit(Ray ray, HitPoint &hitPoint){
    HIT_ROUTINE
    double t;
    rayDir = dirRevIndex(ray.d.x, ray.d.y, ray.d.z);
    int k = hitOctree(ray, 0, bbox.rayIntersection(ray), t);
    if (k == -1)
        return false;
    if (ray.d * faceNormals[k] < 0)
        hitPoint.set(t, k, HitPoint::HitIn, this);
    else
        hitPoint.set(t, k, HitPoint::HitOut, this);
    return true;
}

bool MeshObject::hit(Ray ray, vector<HitPoint> &hitList){
    HIT_ROUTINE
    return false;
}

void MeshObject::getHitInfo(HitInfo &info){
    info.hitPoint = info.ray.o + info.ray.d * info.t;
    info.localPoint = inverse.operatedPoint(info.hitPoint);
    int k = info.tag;
    int p, q, r;
    Vector normal;
    std::tie(p, q, r) = faces[k];
    double s1 = ((info.localPoint - vertices[p]) ^ (vertices[r] - vertices[p])) * faceNormals[k] / areas[k];
    double s2 = ((vertices[q] - vertices[p]) ^ (info.localPoint - vertices[p])) * faceNormals[k] / areas[k];
    normal = ((1 - s1 - s2) * vertexNormals[p] + s1 * vertexNormals[q] + s2 * vertexNormals[r]).normalized();
    info.face = k;
    info.u = s1;
    info.v = s2;
    info.du = vertices[q] - vertices[p];
    info.dv = vertices[r] - vertices[p];
    if (info.hitType == HitPoint::HitIn){
        info.normal = faceNormals[k];
        info.shadeNormal = normalBlend ? normal : info.normal;
    }
    else{
        info.normal = -faceNormals[k];
        info.shadeNormal = normalBlend ? -normal : info.normal;
    }
    inverse.operateNormal(info.normal);
    inverse.operateNormal(info.shadeNormal);
    inverse.operateVector(info.du);
    inverse.operateVector(info.dv);
}

int MeshObject::checkBoundingBox(const BoundingBox &box){
    CHECK_ROUTINE
    if (bbox.disjoint(box))
        return Outside;
    else
        return OnBorder;
}
