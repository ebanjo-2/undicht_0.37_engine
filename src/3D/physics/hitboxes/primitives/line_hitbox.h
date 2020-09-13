#ifndef LINE_HITBOX_H
#define LINE_HITBOX_H

#include <3D/math/line.h>
#include <3D/physics/hitboxes/hitbox.h>

namespace undicht {


    class LineHitbox : public Line, public Hitbox {

        public:
            // getting the defining attributes of the line with the Orientation3D applied

            glm::vec3 getWorldPoint() const;

            glm::vec3 getWorldDir() const;

        public:
            // basic collision detection functions

            /** @return whether there is an intersection between the lines */
            virtual bool intersection(const LineHitbox& line, glm::vec3& point) const;

            /** @param dir_factor_this: the factor with which to multiply this lines direction vector to get to the intersection
            * @param dir_factor_line: the factor with which to multiply the other lines direction vector to get to the intersection */
            virtual bool intersection(const LineHitbox& line, float& dir_factor_this, float& dir_factor_line) const;

            /** @return whether there is an intersection between the lines
            * the lines have to form a plane, otherwise this function wont produce anything usefull */
            virtual bool intersecOnPlane(const LineHitbox& line, glm::vec3& point) const;

            /** @param dir_factor_this: the factor with which to multiply this lines direction vector to get to the intersection
            * @param dir_factor_this: the factor with which to multiply the other lines direction vector to get to the intersection */
            virtual bool intersecOnPlane(const LineHitbox& line, float& dir_factor_this, float& dir_factor_line) const;


        public:

            virtual int getType() const;

            LineHitbox();
            virtual ~LineHitbox();

    };

} // undicht

#endif // LINE_HITBOX_H
