#ifndef LINE_HITBOX_H
#define LINE_HITBOX_H

#include <3D/math/ray.h>
#include <3D/physics/hitboxes/hitbox.h>

namespace undicht {


    class LineHitbox : public Ray, public Hitbox {
        /** an object that can be used to test for intersections with other hitboxes
        * it starts at point_1 and ends at point_2, its direction vector is point_2 - point_1 */
        public:
            // getting the defining attributes of the line with the Orientation3D applied

            glm::vec3 getWorldPoint() const;

            glm::vec3 getWorldDir() const;

        public:
            // basic collision detection functions

            /** @return whether there is an intersection between the lines */
            virtual bool intersection(const LineHitbox& line, glm::vec3& point) const;

            /** @param dir_factor_this: the factor with which to multiply this lines direction vector to get to the intersection
            * @param dir_factor_line: the factor with which to multiply the other lines direction vector to get to the intersection
            * @return will also return true if the rays on which the lines are collide at some point outside the lines range
            * in which case at least one of the dir_factors is outside the range of [0,1] */
            virtual bool intersection(const LineHitbox& line, float& dir_factor_this, float& dir_factor_line) const;

            /** @return whether there is an intersection between the lines
            * the lines have to form a plane, otherwise this function wont produce anything usefull */
            virtual bool intersecOnPlane(const LineHitbox& line, glm::vec3& point) const;

            /** @param dir_factor_this: the factor with which to multiply this lines direction vector to get to the intersection
            * @param dir_factor_this: the factor with which to multiply the other lines direction vector to get to the intersection
            * @return will also return true if the rays on which the lines are collide at some point outside the lines range
            * in which case at least one of the dir_factors is outside the range of [0,1] */
            virtual bool intersecOnPlane(const LineHitbox& line, float& dir_factor_this, float& dir_factor_line) const;


        public:

            virtual int getType() const;

            LineHitbox();
            LineHitbox(const glm::vec3& point_1, const glm::vec3& point_2);
            virtual ~LineHitbox();

    };

} // undicht

#endif // LINE_HITBOX_H
