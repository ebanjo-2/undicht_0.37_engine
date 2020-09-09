#include "polygon_hitbox.h"

namespace undicht {

    PolygonHitbox::PolygonHitbox() {
        //ctor
    }

    PolygonHitbox::~PolygonHitbox() {
        //dtor
    }

    int PolygonHitbox::getType() {

        return UND_POLYGON_HITBOX;
    }

    int PolygonHitbox::getHitboxCount() {

        return m_hitboxes.size();
    }

    SimplePolygonHitbox& PolygonHitbox::addHitbox() {

        m_hitboxes.emplace_back(SimplePolygonHitbox());
        m_hitboxes.back().setTransfRelTo(this);

        return m_hitboxes.back();
    }

    int PolygonHitbox::addHitbox(const SimplePolygonHitbox& h) {

        m_hitboxes.push_back(h);
        m_hitboxes.back().setTransfRelTo(this);

        return m_hitboxes.size() - 1;
    }


    SimplePolygonHitbox& PolygonHitbox::getHitbox(int id) {

        return m_hitboxes.at(id);
    }

} // undicht
