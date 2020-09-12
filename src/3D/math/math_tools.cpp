#include "math_tools.h"

#include <glm/glm/glm.hpp>

namespace undicht {

    std::ostream& operator<< (std::ostream& out, const glm::vec3& v) {

        out << v.x << " " << v.y << " " << v.z;

        return out;
    }

    bool MathTools::overlappingRanges(float range_1_start, float range_1_end, float range_2_start, float range_2_end) {

        // making sure the start of the range is before the end
        float s1 = glm::min(range_1_start, range_1_end);
        float e1 = glm::max(range_1_start, range_1_end);

        float s2 = glm::min(range_2_start, range_2_end);
        float e2 = glm::max(range_2_start, range_2_end);

        // cases in which the ranges do not overlap (is it really that easy ?)
        if((e1 < s2) || (e2 < s1)) {

            return false;
        }

        return true;
    }

} // undicht
