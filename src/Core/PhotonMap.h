#pragma once
#include "Utility/Arrays.h"
#include "Utility/Photon.h"
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

class PhotonMap{
private:
    Point gatherPos;
    Normal gatherNormal;
    double gatherHeight;
    double currentRadiusSqr;
    int gatherNumber;
    int maxDepth;

    //
    int visitCount;

    void calcVariance(int l, int r, double &vx, double &vy, double &vz);
    void findSurfacePhoton(int l, int r);
    void findVolumePhoton(int l, int r);
    void addGatherPhoton(double t, int k);

public:
    double currentRadius;
    vector<Photon> photonList;
    vector<pair<double, int> > gatheredPhoton;

    void insert(Point pos, Vector dir, RGBColor color);
    void replace(Point pos, Vector dir, RGBColor color);
    void buildPhotonMap();
    void buildTree(int l, int r);
    void surfaceGather(const Point &p, const Normal &normal, double maxRadius, double maxHeight, int maxNum);
    void volumeGather(const Point &p, double maxRadius, int maxNum);

    void save(FILE *fout);
    void load(FILE *fin);
};

extern long long photonGatherTime;
extern long long photonAddTime;
extern long long photonSearchTime;
