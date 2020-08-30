#ifndef HITBOX_POLYGON_H
#define HITBOX_POLYGON_H


#include <vector>
#include "3D/math/plane.h"
#include "3D/math/line.h"
#include "3D/math/orientation_3d.h"

#include <glm/glm/glm.hpp>


namespace undicht {


    class HitboxPolygon : public Orientation3D {

        public:

            std::vector<glm::vec3> m_vertices;
            Plane m_plane; // the plane on which all the vertices are

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
            // basic collision detection functions

            /** @return false if the point is excluded from the model by this polygon*/
            virtual bool insideModel(const glm::vec3& point) const;

            /** @param dir_factor: the factor with which the direction vector of the line has to be multiplied
            * to get from the lines base point to the intersection whith the polygons plane
            * @param dir: true, if the part of the line with bigger dir_factors is inside the model
            * false, if the part of the line with bigger dir_factors is inside the model
            * -1, if the line and polygon are parallel */
            virtual bool insideModel(const Line& l, float& dir_factor, char& dir) const;


            void operator= (const HitboxPolygon& p);

            HitboxPolygon();
            HitboxPolygon(const HitboxPolygon& p);
            HitboxPolygon(const std::vector<glm::vec3>& vertices);
            virtual ~HitboxPolygon();

    };


} // undicht

#endif // HITBOX_POLYGON_H
