#ifndef ORIENTATION_H
#define ORIENTATION_H

#include <glm/glm/glm.hpp>
#include <glm/glm/gtx/quaternion.hpp>


namespace undicht {


    class Orientation3D {
        /** a class that has functions to rotate and translate an Object */

        protected:
            // members to store the orientation

            Orientation3D* m_relative_orientation = 0;

            glm::vec3 m_position;
            glm::quat m_rotation;
            glm::vec3 m_scale;

            // whether the matrices representing the transformations need to be updated
            bool m_update_pos = true;
            bool m_update_rot = true;
            bool m_update_transf = true;

            glm::mat4 m_transl_mat;
            glm::mat4 m_rot_mat;
            glm::mat4 m_transf_mat; // transformation relative to relative_orientation


        protected:
            // functions to update matrices
            // can be reimplemented by other classes to also update their matrices (i.e. view matrix)

            /** called whenever the translation matrix needs to be updated */
            virtual void updatePosition();

            virtual void updateRotation();

            virtual void updateTransf();

        public:
            // translation

            void setPosition(const glm::vec3& position);

            // the position in relation to the relative orientation
            const glm::vec3& getPosition();
            /** @return a matrix, that multiplied with a 4D vector (x,y,z,1) will result in a 3D vector (x + pos.x, y + pos.y, z + pos.z, 1) */
            const glm::mat4& getTranslMat();

            // the absolute position in the world
            glm::vec3 getWorldPosition();
            glm::mat4 getWorldTranslMat();

            /** moves the object */
            void addTranslation(const glm::vec3& v);


        public:
            // rotation

            // rotation around the orientations world position
            void setRotation(const glm::quat& rot);

            const glm::quat& getRotation();
            const glm::mat4& getRotMat();

            // the absolute rotation relative to the world
            glm::quat getWorldRot();
            glm::mat4 getWorldRotMat();

        public:
            // scaling

            /** scaling the translation of child elements + can be used to scale the model */
            void setScale(const glm::vec3& scale);

            const glm::vec3& getScale();

            // scale multiplied by the scale of the orientations parents
            glm::vec3 getWorldScale();

        public:
            // transformation (translation + rotation combined)

            const glm::mat4& getTransfMat();

            // the absolute transformation relative to the world
            glm::mat4 getWorldTransfMat();

            /** sets this orientations transformation (position + rotation) to be relative to the orientation passed
            * @param : if 0 is passed, the transformation will be relative to the world */
            void setTransfRelTo(Orientation3D* rel_transf);

        public:

            Orientation3D();
            virtual ~Orientation3D();

    };


} // undicht

#endif // ORIENTATION_H
