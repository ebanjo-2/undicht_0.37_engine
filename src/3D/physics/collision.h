#ifndef COLLISION_H
#define COLLISION_H


#include <glm/glm/glm.hpp>


namespace undicht {


    class Collision {
        public:

            bool m_collision_inbound = false;
            glm::vec3 m_normal;


        public:
            // functions for setting / getting information about the collision

            void setCollision(bool b);
            operator bool();

            /** the normal of the surface a moving object collides with */
            void setNormal(const glm::vec3& normal);
            glm::vec3 getNormal();

            Collision();
            Collision(bool b);
            Collision(bool b, const glm::vec3& normal);
            virtual ~Collision();

    };


} // undicht

#endif // COLLISION_H
