#ifndef SIMPLEPOLYGONHITBOX_H
#define SIMPLEPOLYGONHITBOX_H


#include "hitbox.h"
#include "hitbox_polygon.h"

namespace undicht {

    class SimplePolygonHitbox : public Hitbox {
    /** a hitbox that can have the shape of any object made of polygons with no particular number of vertices
    * that from where ever it is seen has no more then 2 surfaces  */
        public:

            std::vector<HitboxPolygon> m_polygons;

        public:
            // collision detection with simple objects

            /** testing whether the point is inside the hitbox or not */
            virtual bool collision(const glm::vec3& point) const;

            /** testing whether any part of the line is in the hitbox or not */
            virtual bool collision(const glm::vec3& line_start, const glm::vec3& line_end) const;


        public:
            // managing the polygons

            /** @return the id with which to access the polygon */
            int addPolygon(const HitboxPolygon& polygon);

            HitboxPolygon& getPolygon(int id);

        public:

            SimplePolygonHitbox();
            virtual ~SimplePolygonHitbox();

    };


} // undicht

#endif // SIMPLEPOLYGONHITBOX_H
