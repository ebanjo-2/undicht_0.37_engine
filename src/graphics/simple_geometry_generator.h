#ifndef SIMPLE_GEOMETRY_H
#define SIMPLE_GEOMETRY_H

#include <vector>
#include "model_loader.h"

namespace undicht {


    class SimpleGeometryGenerator : public ModelLoader {
            /** a class that can generate simple geometrical forms such as a cube, a sphere, ... */
        public:
            // 3D

            // works with backface culling
            virtual void genCube(std::vector<float>& loadTo, float size = 1);

            // works with backface culling
            /** @param resolution: number of vertices per circle around the sphere  */
            virtual void genSphere(std::vector<float>& loadTo, int resolution = 16 , float radius = 1);

            // works with backface culling
            /** generates a cylinder that is open at both ends */
            virtual void genCylinder(std::vector<float>& loadTo, int resolution = 16, bool close_ends = true, float radius = 1, float length = 1);

            SimpleGeometryGenerator();
            virtual ~SimpleGeometryGenerator();

    };

} // undicht

#endif // SIMPLE_GEOMETRY_H
