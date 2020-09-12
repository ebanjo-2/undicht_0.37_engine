#ifndef HITBOX_POLYGON_H
#define HITBOX_POLYGON_H


#include <vector>
#include "plane_hitbox.h"
#include "line_hitbox.h"

#include <glm/glm/glm.hpp>


namespace undicht {


    class HitboxPolygon : public Hitbox {
            /** a class representing an polygon of a hitbox
            * while it is not limited to 3 vertices, they do have to have other properties:
            * 1: they all have to be on the same plane
            * 2: the edges must be placed so that there is no way of a line passing through the polygon to have more then 2 intersections with the edges */
        public:

            std::vector<glm::vec3> m_vertices;
            std::vector<LineHitbox> m_edges; // the lines have their point set at one vertex, with their direction being the distance to the other vertex
            PlaneHitbox m_plane; // the plane on which all the vertices are

        public:
            // setting / getting data

            /** the vertices all have to be on the same plane
            * and they have to be defined in clockwise order when viewed from outside the model */
            virtual void setVertices(const std::vector<glm::vec3>& vertices);

        public:
            // getting the world positions of the vertices

            virtual glm::vec3 getWorldVertex(int id) const;

            /** @return all vertices transformed into world space */
            virtual std::vector<glm::vec3> getWorldVertices() const;

        public:
            // getting the edges of the polygon

            virtual const LineHitbox& getEdge(int id) const;

            virtual const std::vector<LineHitbox>& getEdges() const;

        public:
            // basic collision detection functions

            /** @return false if the point is excluded from the model by this polygon*/
            virtual bool insideModel(const glm::vec3& point) const;

            /** calculates the 2 intersections of the line with the edges of the polygon
            * the line has to be on the same plane as the polygon
            * @return false, if the line does never intersect with any of the edges */
            virtual bool edgeIntersection(const LineHitbox& line, glm::vec3& point1, glm::vec3& point2) const;

            /** @param dir_factor: the factor with which the lines direction vector has to be multiplied
            * to get to the intersections with the polygons edges
            * the line has to be on the same plane as the polygon */
            virtual bool edgeIntersection(const LineHitbox& line, float& dir_factor1, float& dir_factor2) const;

            /** @return true if the polygon intersects with this one
            * does not work if the polygons are parallel (which shouldnt be a problem,
            * since there should be other polygons in the hitbox to intersect with */
            virtual bool intersection(const HitboxPolygon& polygon) const;

        public:

            virtual int getType() const;

            HitboxPolygon();
            HitboxPolygon(const std::vector<glm::vec3>& vertices);
            virtual ~HitboxPolygon();

    };


} // undicht

#endif // HITBOX_POLYGON_H
