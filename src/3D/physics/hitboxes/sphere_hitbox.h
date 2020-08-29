#ifndef SPHERE_HITBOX_H
#define SPHERE_HITBOX_H


#include <3D/physics/hitboxes/hitbox.h>


namespace undicht {

    class SphereHitbox : public Hitbox {
        /** a sphere, with its diameter determined by its scales x component*/
        public:

            void setRadius(float radius);
            float getRadius();

            SphereHitbox();
            virtual ~SphereHitbox();

    };


} // undicht

#endif // SPHERE_HITBOX_H
