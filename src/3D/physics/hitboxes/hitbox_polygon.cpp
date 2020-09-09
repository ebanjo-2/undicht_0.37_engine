#include "hitbox_polygon.h"
#include <3D/math/relations.h>
#include <core/event_logger.h>
#include <3D/physics/collision_detection.h>


namespace undicht {

    using namespace core;

    HitboxPolygon::HitboxPolygon() {
        //ctor

        m_plane.setTransfRelTo(this);

    }

    HitboxPolygon::HitboxPolygon(const std::vector<glm::vec3>& vertices) {

        setVertices(vertices);
        m_plane.setTransfRelTo(this);

    }

    HitboxPolygon::~HitboxPolygon() {
        //dtor
    }


    void HitboxPolygon::setVertices(const std::vector<glm::vec3>& vertices) {
        /** the vertices all have to be on the same plane
        * and they have to be defined in clockwise order when viewed from outside the model */

        if(vertices.size() < 3) {

            EventLogger::storeNote(Note(UND_ERROR, "failed to init hitbox polygon, not enough vertices", UND_CODE_ORIGIN));
            return;
        }

        m_plane.def(vertices[0], vertices[1], vertices[2]);

        m_vertices = vertices;

    }


    //////////////////////////// getting the world positions of the vertices ////////////////////////////////////

    glm::vec3 HitboxPolygon::getWorldVertex(int id) const {

        return glm::rotate(getWorldRot(), m_vertices.at(id)) * getWorldScale() + getWorldPosition();
    }


    std::vector<glm::vec3> HitboxPolygon::getWorldVertices() const {
        /** @return all vertices transformed into world space */

        std::vector<glm::vec3> world_vertices;

        for(int i = 0; i < m_vertices.size(); i++) {

            world_vertices.push_back(getWorldVertex(i));
        }

        return world_vertices;
    }


    //////////////////////////// basic collision detection functions ////////////////////////////


    bool HitboxPolygon::insideModel(const glm::vec3& point) const {
        /** @return false if the point is excluded from the model by this polygon */

        return (distancePointPlane(point, m_plane) <= 0);
    }


    bool HitboxPolygon::insideModel(const Line& l, float& dir_factor, char& dir) const {
        /** @param dir_factor: the factor with which the direction vector of the line has to be multiplied
        * to get from the lines base point to the intersection whith the polygons plane
        * @param dir: true, if the part of the line with bigger dir_factors is inside the model
        * false, if the part of the line with bigger dir_factors is inside the model */

        bool intersect = intersecPlaneLine(m_plane, l, dir_factor);

        if(intersect) {
            // plane and line intersect
            dir = insideModel(l.getWorldPoint() + l.getWorldDir() * (dir_factor + 1));

            return true;
        } else {
            // plane and line are parallel
            dir = -1;

            return insideModel(l.getWorldPoint());
        }

    }


} // undicht
