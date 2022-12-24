#pragma once
#include "Object.h"

#include <vector>
#include <memory>

using std::make_shared;
using std::shared_ptr;

class ObjectList: public Object
{
public:
    std::vector<shared_ptr<Object>> objects;

    ObjectList();
    ObjectList(shared_ptr<Object> obj) { add(obj); };
    ~ObjectList();

    void clear() { objects.clear(); };
    void add(shared_ptr<Object> obj) { objects.push_back(obj); };

    virtual bool hit(const Ray& ray, double t_min, double t_max, HitInfo& info) const override;
};
