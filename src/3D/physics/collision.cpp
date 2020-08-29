#include "collision.h"

namespace undicht {

    Collision::Collision() {
        //ctor
    }

    Collision::Collision(bool b) {

        setCollision(b);
    }


    Collision::Collision(bool b, const glm::vec3& normal) {

        setCollision(b);
        setNormal(normal);
    }

    Collision::~Collision() {
        //dtor
    }

    void Collision::setCollision(bool b) {

        m_collision_inbound = b;
    }

    Collision::operator bool() {

        return m_collision_inbound;
    }


    void Collision::setNormal(const glm::vec3& normal) {

        m_normal = normal;
    }


    glm::vec3 Collision::getNormal() {

        return m_normal;
    }



} // undicht
