#ifndef POLYGON_HITBOX_H
#define POLYGON_HITBOX_H

#include <vector>
#include <3D/physics/hitboxes/primitives/hitbox_polygon.h>
#include <3D/physics/hitboxes/hitbox.h>

namespace undicht {


    class PolygonHitbox : public Hitbox {
        /** a class combining multiple simple polygon hitboxes to form complex forms */

        public:

            std::vector<HitboxPolygon> m_polygons;

        public:
            // managing the polygons of the hitbox

            void setPolygons(const std::vector<HitboxPolygon>& polygons);

            void addPolygon(const HitboxPolygon& polygon);

            void setPolygon(const HitboxPolygon& polygon, int id);

            const HitboxPolygon& getPolygon(int id) const;

        public:
            // collision detection functions

            /** @return true if the hitboxes have overlapping volumes */
            virtual bool collision(const PolygonHitbox& hitbox) const;

        public:

            virtual int getType() const;

            PolygonHitbox();
            virtual ~PolygonHitbox();

    };


} // undicht

#endif // POLYGON_HITBOX_H
