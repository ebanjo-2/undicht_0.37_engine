#include "line_hitbox.h"
#include <3D/math/plane.h>
#include <3D/math/relations.h>
#include <3D/math/math_tools.h>
#include <iostream>

#include <core/event_logger.h>

namespace undicht {

    using namespace core;

    LineHitbox::LineHitbox() {
        //ctor
    }

    LineHitbox::LineHitbox(const glm::vec3& point_1, const glm::vec3& point_2) {

        def2P(point_1, point_2);
    }

    LineHitbox::~LineHitbox() {
        //dtor
    }

    int LineHitbox::getType() const {

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

    bool LineHitbox::intersection(const LineHitbox& line, glm::vec3& point) const {
        /** @return whether there is an intersection between the lines */

        float f1, f2;

        bool intersec = intersection(line, f1, f2);

        if(!intersec) {

            return false;
        }

        if((f1 < 0) || (f1 > 1) || (f2 < 0) || (f2 > 1)) {
            // the point of intersection is outside of the lines range

            return false;
        }

        point = getWorldPoint() + f1 * getWorldDir();

        return true;
    }


    bool LineHitbox::intersection(const LineHitbox& line, float& dir_factor_this, float& dir_factor_line) const {
        /** @param dir_factor_this: the factor with which to multiply this lines direction vector to get to the intersection
        * @param dir_factor_this: the factor with which to multiply the other lines direction vector to get to the intersection
        * @return will also return true if the rays on which the lines are collide at some point outside the lines range
        * in which case at least one of the dir_factors is outside the range of [0,1] */

        Plane p;
        p.defW2D(getWorldPoint(), getWorldDir(), line.getWorldDir());

        if(!pointOnPlane(line.getWorldPoint(), p)) {
            // the lines dont form a plane, there cant be an intersection
            return false;
        }

        return intersecOnPlane(line, dir_factor_this, dir_factor_line);
    }


    bool LineHitbox::intersecOnPlane(const LineHitbox& line, glm::vec3& point) const {
        /** @return whether there is an intersection between the lines
        * the lines have to form a plane, otherwise this function wont produce anything usefull */

        float f1, f2;

        bool intersec = intersecOnPlane(line, f1, f2);

        if(!intersec) {

            return false;
        }

        if((f1 < 0) || (f1 > 1) || (f2 < 0) || (f2 > 1)) {
            // the point of intersection is outside of the lines range

            return false;
        }

        point = getWorldPoint() + f1 * getWorldDir();

        return true;
    }


    bool LineHitbox::intersecOnPlane(const LineHitbox& line, float& dir_factor_this, float& dir_factor_line) const {
        /** @param dir_factor_this: the factor with which to multiply this lines direction vector to get to the intersection
        * @param dir_factor_this: the factor with which to multiply the other lines direction vector to get to the intersection
        * @return will also return true if the rays on which the lines are collide at some point outside the lines range
        * in which case at least one of the dir_factors is outside the range of [0,1] */

        // they have to be on the same plane for this to work

        glm::vec3 d1 = getWorldDir();
        glm::vec3 d2 = line.getWorldDir();

        if((d1.x / d2.x) ==  (d1.y / d2.y) == (d1.z / d2.z)) {
            // they are parallel, so they dont intersect (maybe they are identical, but they dont intersect)
            std::cout << "line is parallel to this one" << "\n";
            return false;
        }

        glm::vec3 p1 = getWorldPoint();
        glm::vec3 p2 = line.getWorldPoint();

        // we know that the lines are on the same plane and that they are not parallel, so they must intersect at sime point
        // | p1.x + f1 * d1.x = p2.x + f2 * d2.x |
        // | p1.y + f1 * d1.y = p2.y + f2 * d2.y |
        // | p1.z + f1 * d1.z = p2.z + f2 * d2.z |

        // there are 3 equasitions to calculate the 2 factors, so we only need two
        // however, not every combination of equations may work
        // solving this with an ti voyage 200 brings me to here
        // f1 = (d2x * (p1y - p2y) - d2y * (p1x - p2x)) / (d1x * d2y - d1y * d2x)
        // f2 = (d1x * (p1y - p2y) - d1y * (p1x - p2x)) / (d1x * d2y - d1y * d2x)
        // you can see how this could go wrong: if (d1x * d2y - d1y * d2x) equals 0

        float dividor = d1.x * d2.y - d1.y * d2.x;

        if(dividor != 0) {
            // proceed with calculation
            dir_factor_this = (d2.x * (p1.y - p2.y) - d2.y * (p1.x - p2.x)) / dividor;
            dir_factor_line = (d1.x * (p1.y - p2.y) - d1.y * (p1.x - p2.x)) / dividor;
        } else {
            // try different set of equations (x and z)
            dividor = d1.x * d2.z - d1.z * d2.x;

            if(dividor != 0) {
                // proceed with calculation
                dir_factor_this = (d2.x * (p1.z - p2.z) - d2.z * (p1.x - p2.x)) / dividor;
                dir_factor_line = (d1.x * (p1.z - p2.z) - d1.z * (p1.x - p2.x)) / dividor;
            } else {
                // try different set of equations (x and z)
                dividor = d1.y * d2.z - d1.z * d2.y;

                if(dividor != 0) {
                    // proceed with calculation
                    dir_factor_this = (d2.y * (p1.z - p2.z) - d2.z * (p1.y - p2.y)) / dividor;
                    dir_factor_line = (d1.y * (p1.z - p2.z) - d1.z * (p1.y - p2.y)) / dividor;
                } else {
                    // this should never happen
                    EventLogger::storeNote(Note(UND_ERROR, "LINE HITBOX: somethings wrong, i can feel it", UND_CODE_ORIGIN));
                    return false;
                }
            }
        }


        return true;
    }

} // undicht
