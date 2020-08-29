#ifndef PLANE_H
#define PLANE_H

#include <glm/glm/glm.hpp>

namespace undicht {

    class Plane {
        /** a class representing an infinite plane in 3D space */
        protected:
            // members defining the plane

            glm::vec3 m_point; // a point on the plane
            glm::vec3 m_normal; // the normal of the plane

        public:
            // functions to define the plane

            /** defined by a point on the plane + a normal vector */
            void def(const glm::vec3& point, const glm::vec3& normal);

            /** defined by 3 points on the plane */
            void def(const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3);

            /** defined by a point on the plane + 2 vectors pointing in two directions on the plane */
            void defW2D(const glm::vec3& point, const glm::vec3& dir1, const glm::vec3& dir2);

        public:
            // getting the defining attributes of the plane

            /** @return the normal of the plane */
            const glm::vec3& getNormal() const;

            /** @return a point on the plane */
            const glm::vec3& getPoint() const;

        public:
            // testing whether the plane is properly defined

            operator bool();


        public:

            Plane();
            Plane(const glm::vec3& point, const glm::vec3& normal);
            virtual ~Plane();

    };


} // undicht

#endif // PLANE_H
