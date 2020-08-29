#ifndef PERSPECTIVE_CAMERA_3D_H
#define PERSPECTIVE_CAMERA_3D_H

#include <3D/entities/camera_3d.h>
#include <3D/math/perspective_projection.h>

namespace undicht {


    class PerspectiveCamera3D : public Camera3D, public PerspectiveProjection {

        public:

            virtual const glm::mat4& getCameraProjectionMatrix();

            PerspectiveCamera3D();
            virtual ~PerspectiveCamera3D();

    };


} // undicht

#endif // PERSPECTIVE_CAMERA_3D_H
