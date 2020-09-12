#ifndef MATH_TOOLS_H
#define MATH_TOOLS_H

#include <iostream>
#include <glm/glm/glm.hpp>

namespace undicht {


    std::ostream& operator<< (std::ostream& out, const glm::vec3& v);


    class MathTools {
        /** a class with general purpose math functions */
        public:

            static bool overlappingRanges(float range_1_start, float range_1_end, float range_2_start, float range_2_end);


    };

} // undicht

#endif // MATH_TOOLS_H
