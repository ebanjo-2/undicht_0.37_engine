#include "simple_polygon_hitbox.h"
#include <3D/physics/collision_detection.h>


namespace undicht {

    SimplePolygonHitbox::SimplePolygonHitbox() {
        //ctor
    }

    SimplePolygonHitbox::SimplePolygonHitbox(const SimplePolygonHitbox& h) {

        *this = h;
    }

    SimplePolygonHitbox::~SimplePolygonHitbox() {
        //dtor
    }

    void SimplePolygonHitbox::operator= (const SimplePolygonHitbox& h) {

        m_polygons = h.m_polygons;

        for(HitboxPolygon& p : m_polygons) {

            p.setTransfRelTo(this);
        }

    }


    int SimplePolygonHitbox::getType() {

        return UND_SIMPLE_POLYGON_HITBOX;
    }


    bool SimplePolygonHitbox::collision(const glm::vec3& point) const {
        /** testing whether the point is inside the hitbox or not */

        for(const HitboxPolygon& p : m_polygons) {

            if(!p.insideModel(point)) {
                // the point is excluded by the polygon
                return false;
            }

        }

        // from the perspective of all polygons the point is inside the model
        return true;
    }

    bool SimplePolygonHitbox::collision(const glm::vec3& line_start, const glm::vec3& line_end) const{
        /** testing whether any part of the line is in the hitbox or not */

        std::cout << "collision test simple hitbox x line" << "\n";

        float line_dir_min = 0;
        float line_dir_max = 1;

        Line l(line_start, line_end - line_start);

        float dir_factor;
        char cutof_direction; // true if the min gets bigger, false if the max gets smaller

        // "cutting" of parts of the line excluded by the polygons
        for(const HitboxPolygon& p : m_polygons) {


            if(!p.insideModel(l, dir_factor, cutof_direction)) {
                // the line is entirely excluded by the polygon (line is parallel to the polygons plane)

                return false;
            }

            if(cutof_direction == 0) {

                line_dir_max = std::min(line_dir_max, dir_factor);

            } else if(cutof_direction == 1) {

                line_dir_min = std::max(line_dir_min, dir_factor);

            }  else {
                std::cout << "Simple: line worldpoint: " << l.getWorldPoint() << "\n";
                std::cout << "Simple: plane normal / point: " << p.m_plane.getWorldNormal() << "  /  " << getWorldPosition() << "\n";
                std::cout << "Simple: inside Model: " << p.insideModel(l.getWorldPoint()) << "\n";
            }// else if(cutof_direction == -1): do nothing

            // testing whether there is any part of the line left not excluded
            if(line_dir_max < line_dir_min) {

                return false;
            }

        }

        std::cout << "collision: " << line_start << "    /    " << line_end << "\n";
        std::cout << "min: " << line_dir_min << " max: " << line_dir_max << "\n";

        // there is a part of the line not excluded from the hitbox by the polygons
        return true;
    }


    ///////////////////////////////////////// managing the polygons //////////////////////////////////////////

    int SimplePolygonHitbox::addPolygon(const HitboxPolygon& polygon) {

        m_polygons.push_back(polygon);
        m_polygons.back().setTransfRelTo(this);

        return m_polygons.size() - 1;
    }

    HitboxPolygon& SimplePolygonHitbox::getPolygon(int id) {

        return m_polygons.at(id);
    }

    void SimplePolygonHitbox::setPolygons(const std::vector<HitboxPolygon>& polygons) {

        m_polygons = polygons;

        for(HitboxPolygon& p : m_polygons) {

            p.setTransfRelTo(this);
        }
    }

    const std::vector<HitboxPolygon>& SimplePolygonHitbox::getPolygons() const{

        return m_polygons;
    }


} // undicht
