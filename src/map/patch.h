#ifndef PATCH_H
#define PATCH_H

#include "vector.h"
#include <cstddef>

struct LMPatch {
    int texture_idx = 0;
    vec3 *control_point_vertices = NULL;
    vec2 *control_point_uvs = NULL;
    int width;
    int height;
};

#endif // PATCH_H
