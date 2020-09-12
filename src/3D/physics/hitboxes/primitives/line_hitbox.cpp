#include "line_hitbox.h"
#include <3D/math/plane.h>
#include <3D/math/relations.h>
#include <3D/math/math_tools.h>
#include <iostream>

namespace undicht {

    LineHitbox::LineHitbox() {
        //ctor
    }

    LineHitbox::~LineHitbox() {
        //dtor
    }

    int LineHitbox::getType() const{

        return UND_LINE_HITBOX;
    }


    ///////////////////// getting the defining attributes of the line with the Orientation3D applied ///////////////////////

    glm::vec3 LineHitbox::getWorldPoint() const {

        return getWorldPosition() + getPoint();
    }

    glm::vec3 LineHitbox::getWorldDir() const {

        return glm::rotate(getWorldRot(), getDir());
    }

                /////////////////////////////////////// basic collision detection functions ///////////////////////////////////////

    bool LineHitbox::intersection(const LineHitbox& line, glm::vec3& point) const{
        /** @return whether there is an intersection between the lines */

        float f1, f2;

        bool intersec = intersection(line, f1, f2);

        if(!intersec) {

            return false;
        }

        point = getWorldPoint() + f1 * getWorldDir();

        return true;
    }


    bool LineHitbox::intersection(const LineHitbox& line, float& dir_factor_this, float& dir_factor_line) const{
        /** @param dir_factor_this: the factor with which to multiply this lines direction vector to get to the intersection
        * @param dir_factor_this: the factor with which to multiply the other lines direction vector to get to the intersection */

        Plane p;
        p.defW2D(getWorldPoint(), getWorldDir(), line.getWorldDir());

        if(!pointOnPlane(line.getWorldPoint(), p)) {
            // the lines dont form a plane, there cant be an intersection
            return false;
        }

        return intersecOnPlane(line, dir_factor_this, dir_factor_line);
    }


    bool LineHitbox::intersecOnPlane(const LineHitbox& line, glm::vec3& point) const{
        /** @return whether there is an intersection between the lines
        * the lines have to form a plane, otherwise this function wont produce anything usefull */

        float f1, f2;

        bool intersec = intersecOnPlane(line, f1, f2);

        if(!intersec) {

            return false;
        }

        point = getWorldPoint() + f1 * getWorldDir();

        return true;
    }


    bool LineHitbox::intersecOnPlane(const LineHitbox& line, float& dir_factor_this, float& dir_factor_line) const{
        /** @param dir_factor_this: the factor with which to multiply this lines direction vector to get to the intersection
        * @param dir_factor_this: the factor with which to multiply the other lines direction vector to get to the intersection */

        // they have to be on the same plane for this to work

        glm::vec3 d1 = getWorldDir();
        glm::vec3 d2 = line.getWorldDir();

        if((d1.x / d2.x) ==  (d1.y / d2.y) == (d1.z / d2.z)) {
            // they are parallel, so they dont intersect (maybe they are identical, but they dont intersect)
            return false;
        }

        std::cout << line.getWorldPoint() << "\n";

        // setting the equasitions of the lines equal results in this:
        // p1 + f1 * d1.x = p2 + f2 * d2.x
        // which leads us to here (we know that the lines are on a plane, so we can save the .z part):
        // | d1.x * f1 - d2.x * f2 = p2.x - p1.x |
        // | d1.y * f1 - d2.y * f2 = p2.y - p1.y |
        // a little gauss later (done by ti voyage 200)
        // (i gave up doing it by hand once i realised that it wasnt that simple to shorten and a lot of writing):
        // f1 = d2x*(p1y-p2y)-d2y*(p1x-p2x)/(d1x*d2y-d1y*d2x)
        // f2 = d1x*(p1y-p2y)-d1y*(p1x-p2x)/(d1x*d2y-d1y*d2x)

        glm::vec3 p = getWorldPoint() - line.getWorldPoint();
        float dividor = (d1.x * d2.y - d1.y * d2.x); // (d1x*d2y-d1y*d2x)

        dir_factor_this = d2.x * p.y - d2.y * p.x / dividor; // it just works (i hope)
        dir_factor_line = d1.x * p.y - d1.y * p.x / dividor; // yeah, this doesnt really make sense to me

        return true;
    }

} // undicht
