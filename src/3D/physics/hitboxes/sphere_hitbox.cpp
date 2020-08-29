#include "sphere_hitbox.h"

namespace undicht {

    SphereHitbox::SphereHitbox() {
        //ctor
    }

    SphereHitbox::~SphereHitbox() {
        //dtor
    }

    void SphereHitbox::setRadius(float radius) {

        setScale(glm::vec3(radius));
    }


    float SphereHitbox::getRadius() {

        return getScale().x;
    }


} // undicht
