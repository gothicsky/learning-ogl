#include <math3d.h>

void matrix4f_init_translation(Matrix4f *mt, float x, float y, float z) {

    mt->m[0][0] = 1.0; mt->m[0][1] = 0.0; mt->m[0][2] = 0.0; mt->m[0][3] = x;
    mt->m[1][0] = 0.0; mt->m[1][1] = 1.0; mt->m[1][2] = 0.0; mt->m[1][3] = y;
    mt->m[2][0] = 0.0; mt->m[2][1] = 0.0; mt->m[2][2] = 1.0; mt->m[2][3] = z;
    mt->m[3][0] = 0.0; mt->m[3][1] = 0.0; mt->m[3][2] = 0.0; mt->m[3][3] = 1.0;

}

