#ifndef PLANEHITBOX_H
#define PLANEHITBOX_H

#include <3D/math/plane.h>
#include <3D/physics/hitboxes/primitives/line_hitbox.h>
#include <3D/physics/hitboxes/hitbox.h>


namespace undicht {


    class PlaneHitbox : public Plane, public Hitbox {
        /** a class representing a plane in 3D space that can be used for collision detection */

        public:

            /** precalculated dot product between the normal and point */
            float m_norm_dot_point = 0;

        public:
            // getting the defining attributes of the plane with the Orientation3D applied

            /** @return the normal of the plane (in world space)*/
            glm::vec3 getWorldNormal() const;

            /** @return a point on the plane (in world space)*/
            glm::vec3 getWorldPoint() const;

        public:
            // functions to test for intersections with other hitboxes

            bool intersection(const LineHitbox& line, glm::vec3& point_of_intersection);

            bool intersection(const LineHitbox& line, float& dir_factor);


        public:

            virtual int getType() const;

            PlaneHitbox();
            virtual ~PlaneHitbox();

    };


} // undicht

#endif // PLANEHITBOX_H
