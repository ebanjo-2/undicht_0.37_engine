#ifndef LINE_H
#define LINE_H

#include <glm/glm/glm.hpp>


namespace undicht {

    class Line {
            /** a class representing an infinite straight line */

        protected:
            // members defining the line

            glm::vec3 m_point;
            glm::vec3 m_direction;

        public:
            // defining the line

            /** defined by a point on the line + the positive direction of the line */
            void def(const glm::vec3& point, const glm::vec3& dir);

        public:
            // getting the defining attributes of the line

            /// you get the point
            const glm::vec3& getPoint() const;

            /** @return the positive direction of the line */
            const glm::vec3& getDir() const;

        public:
            // testing whether the line is properly defined

            operator bool();

        public:

            Line();
            Line(const glm::vec3& point, const glm::vec3& dir);
            virtual ~Line();

    };

} // undicht

#endif // LINE_H
