#ifndef HITBOX_H
#define HITBOX_H

#include <3D/math/orientation_3d.h>


namespace undicht {

    // types of hitboxes
    extern int UND_CUBOID_HITBOX;
    extern int UND_SIMPLE_POLYGON_HITBOX;
    extern int UND_SPHERE_HITBOX;
    extern int UND_HITBOX_POLYGON;
    extern int UND_POLYGON_HITBOX;
    extern int UND_LINE_HITBOX;
    extern int UND_PLANE_HITBOX;


    class Hitbox : public Orientation3D {
        /** base class to all hitboxes
        * the hitboxes orientation should be seen relative to the object it covers */
        public:

            virtual int getType() const = 0;

            Hitbox();
            virtual ~Hitbox();


    };

} // undicht



#endif // HITBOX_H
