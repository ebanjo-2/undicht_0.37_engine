#ifndef RAY_H
#define RAY_H

#include <glm/glm/glm.hpp>

namespace undicht {

    class Ray {
            /** a class representing an infinite straight line */

        protected:
            // members defining the line

            glm::vec3 m_point = glm::vec3(0,0,0);
            glm::vec3 m_direction = glm::vec3(0,0,0);

        public:
            // defining the Ray

            /** defined by a point on the line + the positive direction of the line */
            void def(const glm::vec3& point, const glm::vec3& dir);

            /** defined by 2 points on the line */
            void def2P(const glm::vec3& point1, const glm::vec3& point2);

        public:
            // getting the defining attributes of the line

            /// you get the point
            const glm::vec3& getPoint() const;

            /** @return the positive direction of the line */
            const glm::vec3& getDir() const;



        public:
            // testing whether the ray is properly defined

            operator bool();

        public:

            Ray();
            Ray(const glm::vec3& point, const glm::vec3& dir);
            virtual ~Ray();

    };

} // undicht

#endif // RAY_H
