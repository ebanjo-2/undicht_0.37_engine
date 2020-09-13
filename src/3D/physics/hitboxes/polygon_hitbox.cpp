#include "polygon_hitbox.h"
#include <iostream>

namespace undicht {

    PolygonHitbox::PolygonHitbox() {
        //ctor
    }

    PolygonHitbox::~PolygonHitbox() {
        //dtor
    }

    int PolygonHitbox::getType() const{

        return UND_POLYGON_HITBOX;
    }


    //////////////////////////////////// managing the polygons of the hitbox ///////////////////////////////////

    void PolygonHitbox::setPolygons(const std::vector<HitboxPolygon>& polygons) {

        m_polygons = polygons;
    }

    void PolygonHitbox::addPolygon(const HitboxPolygon& polygon) {

        m_polygons.push_back(polygon);
        m_polygons.back().setTransfRelTo(this);
    }

    void PolygonHitbox::setPolygon(const HitboxPolygon& polygon, int id) {

        m_polygons.at(id) = polygon;
        m_polygons.at(id).setTransfRelTo(this);

    }

    const HitboxPolygon& PolygonHitbox::getPolygon(int id) const{

        return m_polygons.at(id);
    }

    //////////////////////////////////// collision detection functions ////////////////////////////////////

    bool PolygonHitbox::collision(const PolygonHitbox& hitbox) const{
        /** @return true if the hitboxes have overlapping volumes */

        // testing if the polygons of this hitbox intersect with any polygons of the other hitbox

        for(const HitboxPolygon& this_polygon : m_polygons) {

            for(const HitboxPolygon& hitb_polygon : hitbox.m_polygons) {

                if(this_polygon.intersection(hitb_polygon)) {
                    std::cout << "here" << "\n";
                    return true;
                }

            }
        }

        // there may be the case where the one hitbox is included entirely and no polygons intersect,
        // but thats none of my business

        return false;
    }

} // undicht
