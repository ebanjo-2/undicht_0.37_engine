#include "hitbox_polygon.h"
#include <3D/math/relations.h>
#include <core/event_logger.h>
#include <3D/physics/collision_detection.h>
#include <3D/math/math_tools.h>


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


    int HitboxPolygon::getType() const{

        return UND_HITBOX_POLYGON;
    }

    /////////////////////////////////////////// setting / getting data ///////////////////////////////////////////


    void HitboxPolygon::setVertices(const std::vector<glm::vec3>& vertices) {
        /** the vertices all have to be on the same plane
        * and they have to be defined in clockwise order when viewed from outside the model */

        if(vertices.size() < 3) {

            EventLogger::storeNote(Note(UND_ERROR, "failed to init hitbox polygon, not enough vertices", UND_CODE_ORIGIN));
            return;
        }

        m_plane.def(vertices[0], vertices[1], vertices[2]);

        m_vertices = vertices;

        // setting the edges
        m_edges.clear();
        int polygon_count = vertices.size();
        for(int i = 0; i < polygon_count; i++) {

            LineHitbox lh;
            lh.def2P(vertices[i%polygon_count], vertices[(i + 1)%polygon_count]);
            m_edges.push_back(lh);
            m_edges.back().setTransfRelTo(this);

        }

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
    //////////////////////////// getting the edges of the polygon ////////////////////////////

    const LineHitbox& HitboxPolygon::getEdge(int id) const {

        return m_edges.at(id);
    }

    const std::vector<LineHitbox>& HitboxPolygon::getEdges() const {

        return m_edges;
    }

    //////////////////////////// basic collision detection functions ////////////////////////////


    bool HitboxPolygon::insideModel(const glm::vec3& point) const {
        /** @return false if the point is excluded from the model by this polygon */

        return (distancePointPlane(point, m_plane) <= 0);
    }

    bool HitboxPolygon::edgeIntersection(const LineHitbox& line, glm::vec3& point1, glm::vec3& point2) const{
        /** calculates the 2 intersections of the line with the edges of the polygon
        * the line has to be on the same plane as the polygon
        * @return false, if the line does never intersect with any of the edges */

        float dir_f1, dir_f2;

        if(!edgeIntersection(line, dir_f1, dir_f2)) {

            return false;
        }

        point1 = line.getWorldPoint() + dir_f1 * line.getWorldDir();
        point2 = line.getWorldPoint() + dir_f2 * line.getWorldDir();

        return true;
    }

    bool HitboxPolygon::edgeIntersection(const LineHitbox& line, float& dir_factor1, float& dir_factor2) const{
        /** @param dir_factor: the factor with which the lines direction vector has to be multiplied
        * to get to the intersections with the polygons edges
        * the line has to be on the same plane as the polygon */

        float f1, f2;
        bool intersec = false;

        for(const LineHitbox& edge : m_edges) {

            if(edge.intersecOnPlane(line, f1, f2)) {
                std::cout << "intersection with edge line at " << f1 << " " << f2 << "\n";
                if((f1 >= 0) && (f1 <= 1)) {
                    // intersection with edge


                    if(!intersec) {
                        // first intersection with an edge has been found

                        dir_factor1 = f2;
                        intersec = true;

                    } else {
                        // second intersection with an edge has been found

                        std::cout << "second intersection with edge" << "\n";

                        dir_factor2 = f2;

                        return true;
                    }

                }

            }

        }

        return false;
    }

    bool HitboxPolygon::intersection(const HitboxPolygon& polygon) const{
        /** @return true if the polygon intersects with this one
        * does not work if the polygons are parallel (which shouldnt be a problem,
        * since there should be other polygons in the hitbox to intersect with */

        // testing if the line between the polygons planes intersects with the polygons in the same range

        glm::vec3 shared_point, intersec_dir;
        if(!intersecPlanePlane(m_plane.getWorldPoint(), m_plane.getWorldNormal(), polygon.m_plane.getWorldPoint(), polygon.m_plane.getWorldNormal(), shared_point, intersec_dir)) {
            std::cout << "they dont intersect" << "\n";
            return false;
        }

        LineHitbox shared_line; // the line that is on both planes
        shared_line.def(shared_point, intersec_dir);

        std::cout << "shared line: " << shared_point << "     /     " << intersec_dir << "\n";

        float f1, f2, f3, f4;

        if(!edgeIntersection(shared_line, f1, f2)) {
            // this polygon does not "collide" with the shared line, so it cant "collide" with the other polygon
            std::cout << "polygon does not collide with shared line" << "\n";
            return false;
        }

        if(!polygon.edgeIntersection(shared_line, f3, f4)) {
            // the polygon does not "collide" with the shared line, so it cant "collide" with the this polygon
            std::cout << "other polygon does not collide with shared line" << "\n";
            return false;
        }

        std::cout << "got here, almost there" << "\n";
        std::cout << f1 << " " << f2 << " " << f3 << " " <<  f4 << "\n";

        if(MathTools::overlappingRanges(f1, f2, f3, f4)) {
            // the polygons intersect with the shared line in the same range, so they are intersecting

            return true;
        }

        return false;
    }


} // undicht
