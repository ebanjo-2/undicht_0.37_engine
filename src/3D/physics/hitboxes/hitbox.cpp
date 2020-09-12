#include "hitbox.h"


namespace undicht {

    // types of hitboxes
    int UND_CUBOID_HITBOX = 1;
    int UND_SIMPLE_POLYGON_HITBOX = 2;
    int UND_SPHERE_HITBOX = 3;
    int UND_HITBOX_POLYGON = 4;
    int UND_POLYGON_HITBOX = 5;
    int UND_LINE_HITBOX = 6;
    int UND_PLANE_HITBOX = 7;

    Hitbox::Hitbox() {
        //ctor
    }

    Hitbox::~Hitbox() {
        //dtor
    }

} // undicht

