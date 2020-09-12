#ifndef PHYSICS_H
#define PHYSICS_H


#include <glm/glm/glm.hpp>
#include <3D/physics/hitboxes/hitbox.h>
#include <3D/physics/hitboxes/cuboid_hitbox.h>
#include <3D/physics/hitboxes/sphere_hitbox.h>
#include <3D/physics/hitboxes/polygon_hitbox.h>


namespace undicht {


    class Physics {


        public:
            /** functions to test for the collision between stationary hitboxes */

            static bool collision(Hitbox& h1, Hitbox& h2);

        public:


            Physics();
            virtual ~Physics();

    };



} // undicht

#endif // PHYSICS_H
