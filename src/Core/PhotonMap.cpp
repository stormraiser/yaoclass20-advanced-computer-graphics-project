#include "Core/PhotonMap.h"
#include "Utility/func.h"
#include <algorithm>
#include <sys/time.h>

#include <cstdio>

#define MINIMUM_LEAF_SIZE 10

using namespace std;

long long photonGatherTime = 0;
long long photonAddTime = 0;
long long photonSearchTime = 0;
timeval startTime1, finishTime1, startTime2, finishTime2;

bool photonCompX(const Photon &a, const Photon &b){
    return a.x < b.x;
}

bool photonCompY(const Photon &a, const Photon &b){
    return a.y < b.y;
}

bool photonCompZ(const Photon &a, const Photon &b){
    return a.z < b.z;
}

void PhotonMap::insert(Point pos, Vector dir, RGBColor color){
    //printf("%f %f %f %f %f %f\n", pos.x, pos.y, pos.z, color.r, color.g, color.b);
    photonList.push_back(Photon(pos, dir, color));
}

void PhotonMap::replace(Point pos, Vector dir, RGBColor color){
    if (!photonList.empty())
        photonList[rand() % photonList.size()] = Photon(pos, dir, color);
}

void PhotonMap::calcVariance(int l, int r, double &vx, double &vy, double &vz){
    double sx = 0, sy = 0, sz = 0;
    int i;
    for (i = l; i < r; i++){
        sx += photonList[i].x;
        sy += photonList[i].y;
        sz += photonList[i].z;
    }
    sx /= (r - l);
    sy /= (r - l);
    sz /= (r - l);
    vx = vy = vz = 0;
    for (i = l; i < r; i++){
        vx += sqr(photonList[i].x - sx);
        vy += sqr(photonList[i].y - sy);
        vz += sqr(photonList[i].z - sz);
    }
    vx /= (r - l);
    vy /= (r - l);
    vz /= (r - l);
}

void PhotonMap::buildPhotonMap(){
    //printf("%d\n", photonList.size());
    //
    /*
    sort(photonList.begin(), photonList.end(), photonCompZ);
    double ht = 1000;
    int a = 0, b = 0;
    for (int i = 0; i < photonList.size(); i++){
        printf("%f %f %f\n", photonList[i].x, photonList[i].y, photonList[i].z);
        if (photonList[i].z < ht)
            ht = photonList[i].z;
        if (photonList[i].z > 0)
            a++;
        else
            b++;
    }
    //printf("%d %d %f\n", a, b, ht);
    */
    maxDepth = 0;
    int t = photonList.size();
    while (t != 0){
        maxDepth++;
        t >>= 1;
    }

    if (photonList.size() >= 2)
        buildTree(0, photonList.size());
}

void PhotonMap::buildTree(int l, int r){
    if (r - l <= MINIMUM_LEAF_SIZE)
        return;
    double vx, vy, vz;
    int m = (l + r) / 2;
    calcVariance(l, r, vx, vy, vz);
    if ((vx > vy) && (vx > vz)){
        sort(photonList.begin() + l, photonList.begin() + r, photonCompX);
        photonList[m].flag = 0;
    }
    else if ((vy > vx) && (vy > vz)){
        sort(photonList.begin() + l, photonList.begin() + r, photonCompY);
        photonList[m].flag = 1;
    }
    else{
        sort(photonList.begin() + l, photonList.begin() + r, photonCompZ);
        photonList[m].flag = 2;
    }
    buildTree(l, m);
    buildTree(m + 1, r);
}

void PhotonMap::surfaceGather(const Point &p, const Normal &normal, double maxRadius, double maxHeight, int maxNum){
    gatheredPhoton.clear();
    gatherPos = p;
    gatherNormal = normal;
    currentRadius = maxRadius;
    currentRadiusSqr = maxRadius * maxRadius;
    gatherHeight = maxHeight;
    gatherNumber = maxNum;
    if (photonList.size() > 0)
        findSurfacePhoton(0, photonList.size());
    currentRadius = sqrt(currentRadiusSqr);
}

void PhotonMap::volumeGather(const Point &p, double maxRadius, int maxNum){
    //
    gettimeofday(&startTime1, 0);
    //
    //visitCount = 0;

    gatheredPhoton.clear();
    if (photonList.size() == 0)
        return;

    int gl[maxDepth], gr[maxDepth], gk[maxDepth];
    int l, r, m, z = 0;
    double t;
    gatherPos = p;
    currentRadius = maxRadius;
    currentRadiusSqr = maxRadius * maxRadius;
    gatherNumber = maxNum;

    if (photonList.size() > 0)
        findVolumePhoton(0, photonList.size());

    currentRadius = sqrt(currentRadiusSqr);
    //
    gettimeofday(&finishTime1, 0);
    photonGatherTime += (finishTime1.tv_sec - startTime1.tv_sec) * 1000000 + (finishTime1.tv_usec - startTime1.tv_usec);
}

void PhotonMap::addGatherPhoton(double t, int k){
    //
    gettimeofday(&startTime2, 0);

    int m = gatheredPhoton.size();
    int p;
    if (m == gatherNumber){
        gatheredPhoton[0] = pair<double, int>(t, k);
        p = 0;
        while (p * 2 + 2 < m)
            if ((gatheredPhoton[p * 2 + 1].first > gatheredPhoton[p * 2 + 2].first) && (gatheredPhoton[p * 2 + 1].first > t)){
                gatheredPhoton[p].swap(gatheredPhoton[p * 2 + 1]);
                p = p * 2 + 1;
            }
            else if ((gatheredPhoton[p * 2 + 2].first > gatheredPhoton[p * 2 + 1].first) && (gatheredPhoton[p * 2 + 2].first > t)){
                gatheredPhoton[p].swap(gatheredPhoton[p * 2 + 2]);
                p = p * 2 + 2;
            }
            else break;
        if (p * 2 + 2 == m)
            if (gatheredPhoton[p * 2 + 1].first > t)
                gatheredPhoton[p].swap(gatheredPhoton[p * 2 + 1]);
        currentRadiusSqr = gatheredPhoton[0].first;
        currentRadius = sqrt(currentRadiusSqr);
    }
    else{
        gatheredPhoton.emplace_back(t, k);
        p = m;
        while (p > 0)
            if (t > gatheredPhoton[(p - 1) / 2].first){
                gatheredPhoton[p].swap(gatheredPhoton[(p - 1) / 2]);
                p = (p - 1) / 2;
            }
            else
                break;
        m++;
        if (m == gatherNumber){
            currentRadiusSqr = gatheredPhoton[0].first;
            currentRadius = sqrt(currentRadiusSqr);
        }
    }
    //
    gettimeofday(&finishTime2, 0);
    photonAddTime += (finishTime2.tv_sec - startTime2.tv_sec) * 1000000 + (finishTime2.tv_usec - startTime2.tv_usec);
}

void PhotonMap::findSurfacePhoton(int l, int r){
    int m;
    Point p;
    Vector v;
    double t;

    if (r - l <= MINIMUM_LEAF_SIZE){
        for (int i = l; i < r; i++){
            p = photonList[i].pos();
            v = p - gatherPos;
            t = v * gatherNormal / v.norm();
            if (fabs(t) <= gatherHeight){
                v -= gatherNormal * t;
                t = v.squaredNorm();
                if (t < currentRadiusSqr)
                    addGatherPhoton(t, i);
            }
        }
        return;
    }

    m = (l + r) / 2;
    p = photonList[m].pos();
    v = p - gatherPos;
    t = v * gatherNormal / v.norm();
    if (fabs(t) <= gatherHeight){
        v -= gatherNormal * t;
        t = v.squaredNorm();
        if (t < currentRadiusSqr)
            addGatherPhoton(t, m);
    }

    if (photonList[m].flag == 0){
        if (gatherPos.x < photonList[m].x){
            if (l < m)
                findSurfacePhoton(l, m);
            if ((photonList[m].x - gatherPos.x < currentRadius) && (m + 1 < r))
                findSurfacePhoton(m + 1, r);
        }
        else{
            if (m + 1 < r)
                findSurfacePhoton(m + 1, r);
            if ((gatherPos.x - photonList[m].x < currentRadius) && (l < m))
                findSurfacePhoton(l, m);
        }
    }
    else if (photonList[m].flag == 1){
        if (gatherPos.y < photonList[m].y){
            if (l < m)
                findSurfacePhoton(l, m);
            if ((photonList[m].y - gatherPos.y < currentRadius) && (m + 1 < r))
                findSurfacePhoton(m + 1, r);
        }
        else{
            if (m + 1 < r)
                findSurfacePhoton(m + 1, r);
            if ((gatherPos.y - photonList[m].y < currentRadius) && (l < m))
                findSurfacePhoton(l, m);
        }
    }
    else {
        if (gatherPos.z < photonList[m].z){
            if (l < m)
                findSurfacePhoton(l, m);
            if ((photonList[m].z - gatherPos.z < currentRadius) && (m + 1 < r))
                findSurfacePhoton(m + 1, r);
        }
        else{
            if (m + 1 < r)
                findSurfacePhoton(m + 1, r);
            if ((gatherPos.z - photonList[m].z < currentRadius) && (l < m))
                findSurfacePhoton(l, m);
        }
    }
}

void PhotonMap::findVolumePhoton(int l, int r){
    //
    //visitCount++;
    //printf("%d %d %d\n", l, r, visitCount);

    //printf("%d %d\n", l, r);
    double t;
    if (r - l <= MINIMUM_LEAF_SIZE){
        for (int i = l; i < r; i++){
            //t = (photonList[i].pos() - gatherPos).squaredNorm();
            t = sqr(photonList[i].x - gatherPos.x) + sqr(photonList[i].y - gatherPos.y) + sqr(photonList[i].z - gatherPos.z);
            if (t < currentRadiusSqr)
                addGatherPhoton(t, i);
        }
        return;
    }

    int m = (l + r) / 2;
    //t = (photonList[m].pos() - gatherPos).squaredNorm();
    t = sqr(photonList[m].x - gatherPos.x) + sqr(photonList[m].y - gatherPos.y) + sqr(photonList[m].z - gatherPos.z);
    if (t < currentRadiusSqr)
        addGatherPhoton(t, m);

    if (photonList[m].flag == 0){
        if (gatherPos.x < photonList[m].x){
            findVolumePhoton(l, m);
            if (photonList[m].x - gatherPos.x < currentRadius)
                findVolumePhoton(m + 1, r);
        }
        else{
            findVolumePhoton(m + 1, r);
            if (gatherPos.x - photonList[m].x < currentRadius)
                findVolumePhoton(l, m);
        }
    }
    else if (photonList[m].flag == 1){
        if (gatherPos.y < photonList[m].y){
            findVolumePhoton(l, m);
            if (photonList[m].y - gatherPos.y < currentRadius)
                findVolumePhoton(m + 1, r);
        }
        else{
            findVolumePhoton(m + 1, r);
            if (gatherPos.y - photonList[m].y < currentRadius)
                findVolumePhoton(l, m);
        }
    }
    else {
        if (gatherPos.z < photonList[m].z){
            findVolumePhoton(l, m);
            if (photonList[m].z - gatherPos.z < currentRadius)
                findVolumePhoton(m + 1, r);
        }
        else{
            findVolumePhoton(m + 1, r);
            if (gatherPos.z - photonList[m].z < currentRadius)
                findVolumePhoton(l, m);
        }
    }
}

void PhotonMap::save(FILE *fout){
    int i;
    fprintf(fout, "%d\n", photonList.size());
    for (i = 0; i < photonList.size(); i++){
        Photon &p = photonList[i];
        fprintf(fout, "%f,%f,%f,%hhu,%hhu,%hhu,%hhd,%hhu,%hhu,%hhu\n",
                p.x, p.y, p.z, p.r, p.g, p.b, p.e, p.theta, p.phi, p.flag);
    }
}

void PhotonMap::load(FILE *fin){
    int n, i;
    fscanf(fin, "%d\n", &n);
    photonList.resize(n);
    for (i = 0; i < n; i++){
        Photon &p = photonList[i];
        fscanf(fin, "%f,%f,%f,%hhu,%hhu,%hhu,%hhd,%hhu,%hhu,%hhu\n",
                &(p.x), &(p.y), &(p.z), &(p.r), &(p.g), &(p.b), &(p.e), &(p.theta), &(p.phi), &(p.flag));
    }
    maxDepth = 0;
    int t = photonList.size();
    while (t != 0){
        maxDepth++;
        t >>= 1;
    }
}
