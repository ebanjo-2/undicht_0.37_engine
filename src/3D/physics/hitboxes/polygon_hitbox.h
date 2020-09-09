#ifndef POLYGON_HITBOX_H
#define POLYGON_HITBOX_H

#include <vector>
#include <3D/physics/hitboxes/simple_polygon_hitbox.h>
#include <3D/physics/hitboxes/hitbox.h>

namespace undicht {


    class PolygonHitbox : public Hitbox {
        /** a class combining multiple simple polygon hitboxes to form complex forms */

        public:

            /** please only add the to the hitbox via the functions provided below */
            std::vector<SimplePolygonHitbox> m_hitboxes;

        public:

            int getType();

            int getHitboxCount();

            SimplePolygonHitbox& addHitbox();
            int addHitbox(const SimplePolygonHitbox& h);

            SimplePolygonHitbox& getHitbox(int id);

            PolygonHitbox();
            virtual ~PolygonHitbox();

    };


} // undicht

#endif // POLYGON_HITBOX_H
