#pragma once

class Primitive;

struct HitPoint{
    enum HitType{HitIn, HitOut, HitInOut, HitOutIn};

    double t;
    int tag;
    HitType type;
    Primitive *obj;

    HitPoint(){}
    HitPoint(double _t, int _tag, HitType _type, Primitive *_obj = 0):
        t(_t), tag(_tag), type(_type), obj(_obj){}

    void set(double _t, int _tag, HitType _type, Primitive *_obj)
        {t = _t; tag = _tag; type = _type; obj = _obj;}
    inline bool objChanged(){return (type == HitIn) || (type == HitOut);}
    inline bool isInto(){return (type == HitIn) || (type == HitInOut);}
};

inline bool operator<(const HitPoint &a, const HitPoint &b){
    return a.t < b.t;
}
