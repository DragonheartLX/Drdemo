#include "ObjectList.h"

ObjectList::ObjectList(){

}

ObjectList::~ObjectList(){
    
}

bool ObjectList::hit(const Ray& ray, double t_min, double t_max, HitInfo& info) const {
    HitInfo temp_info;
    bool hit_anything = false;
    double closest_so_far = t_max;
    
    for(const shared_ptr<Object>& obj: objects){
        if (obj->hit(ray, t_min, closest_so_far, temp_info))
        {
            hit_anything = true;
            closest_so_far = temp_info.t;
            info = temp_info;
        }
        
    }
    return hit_anything;
}