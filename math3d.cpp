#include <cmath>
#include <math3d.h>

// void matrix4f_init(Matrix4f *mt) {
//
//     mt->m[0][0] = 1.0; mt->m[0][1] = 0.0; mt->m[0][2] = 0.0; mt->m[0][3] = 0.0;
//     mt->m[1][0] = 0.0; mt->m[1][1] = 1.0; mt->m[1][2] = 0.0; mt->m[1][3] = 0.0;
//     mt->m[2][0] = 0.0; mt->m[2][1] = 0.0; mt->m[2][2] = 1.0; mt->m[2][3] = 0.0;
//     mt->m[3][0] = 0.0; mt->m[3][1] = 0.0; mt->m[3][2] = 0.0; mt->m[3][3] = 1.0;
//
// }

Matrix4f mult_matrix4f(Matrix4f *mt1, Matrix4f *mt2) {

    Matrix4f res;

    float sum;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            sum=0;
            for (int k = 0; k < 4; ++k) {
                sum += mt1->m[i][k] * mt2->m[k][j];
            }
            res.m[i][j]= sum;
        }
    }

    return res;
}

void matrix4f_init_translation(Matrix4f *mt, float x, float y, float z) {

    mt->m[0][0] = 1.0; mt->m[0][1] = 0.0; mt->m[0][2] = 0.0; mt->m[0][3] = x;
    mt->m[1][0] = 0.0; mt->m[1][1] = 1.0; mt->m[1][2] = 0.0; mt->m[1][3] = y;
    mt->m[2][0] = 0.0; mt->m[2][1] = 0.0; mt->m[2][2] = 1.0; mt->m[2][3] = z;
    mt->m[3][0] = 0.0; mt->m[3][1] = 0.0; mt->m[3][2] = 0.0; mt->m[3][3] = 1.0;

}

// rotation around x axis

void matrix4f_init_rot_x(Matrix4f *mt, float t) {

    mt->m[0][0] = 1.0; mt->m[0][1] = 0.0; mt->m[0][2] = 0.0; mt->m[0][3] = 0.;
    mt->m[1][0] = 0.0; mt->m[1][1] = cos(t); mt->m[1][2] = sin(t); mt->m[1][3] = 0.;
    mt->m[2][0] = 0.0; mt->m[2][1] = -sin(t); mt->m[2][2] = cos(t); mt->m[2][3] = 0.;
    mt->m[3][0] = 0.0; mt->m[3][1] = 0.0; mt->m[3][2] = 0.0; mt->m[3][3] = 1.0;

}


//Rotation around y axis

void matrix4f_init_rot_y(Matrix4f *mt ,float t) {

    mt->m[0][0] = cos(t); mt->m[0][1] = 0.0; mt->m[0][2] = sin(t); mt->m[0][3] = 0.;
    mt->m[1][0] = 0.0; mt->m[1][1] = 1.0; mt->m[1][2] = 0.0; mt->m[1][3] = 0.;
    mt->m[2][0] = -sin(t); mt->m[2][1] = 0.0; mt->m[2][2] = cos(t); mt->m[2][3] = 0.;
    mt->m[3][0] = 0.0; mt->m[3][1] = 0.0; mt->m[3][2] = 0.0; mt->m[3][3] = 1.0;

}


//rotation around z axis

void matrix4f_init_rot_z(Matrix4f *mt ,float t) {

    mt->m[0][0] = cos(t); mt->m[0][1] = sin(t); mt->m[0][2] = 0.0; mt->m[0][3] = 0.;
    mt->m[1][0] = -sin(t); mt->m[1][1] = cos(t); mt->m[1][2] = 0.0; mt->m[1][3] = 0.;
    mt->m[2][0] = 0.0; mt->m[2][1] = 0.0; mt->m[2][2] = 1.0; mt->m[2][3] = 0.;
    mt->m[3][0] = 0.0; mt->m[3][1] = 0.0; mt->m[3][2] = 0.0; mt->m[3][3] = 1.0;

}

void matrix4f_init_rot(Matrix4f *mt, float t) {

    mt->m[0][0] = cos(t); mt->m[0][1] = sin(t); mt->m[0][2] = 0.0; mt->m[0][3] = 0.;
    mt->m[1][0] = -sin(t); mt->m[1][1] = cos(t); mt->m[1][2] = 0.0; mt->m[1][3] = 0.;
    mt->m[2][0] = 0.0; mt->m[2][1] = 0.0; mt->m[2][2] = 1.0; mt->m[2][3] = 0.;
    mt->m[3][0] = 0.0; mt->m[3][1] = 0.0; mt->m[3][2] = 0.0; mt->m[3][3] = 1.0;

}

// void mult_matrix4f(Matrix4f *mt1, Matrix4f *mt2, Matrix4f *res, int rows, int columns)
// {
//
//     int sum;
//     for (int i = 0; i < rows; ++i) {
//         for (int j = 0; j < columns; ++j) {
//             sum=0;
//             for (int k = 0; k < columns; ++k) {
//                 sum += mt1->m[i][k] * mt2->m[k][j];
//             }
//             res->m[i][j]= sum;
//         }
//     }
//
//
// }

void mult_matrix4f(const Matrix4f *mt1, const Matrix4f *mt2, Matrix4f *res)
{
    Matrix4f temp;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            float sum = 0.0f;
            for (int k = 0; k < 4; ++k) {
                sum += mt1->m[i][k] * mt2->m[k][j];
            }
            temp.m[i][j] = sum;
        }
    }

    *res = temp; // Safe against in-place calls (res == mt1 or res == mt2)
}

void matrix4f_init_usc(Matrix4f *mt, float coeff) {

    mt->m[0][0] = coeff * 1.0; mt->m[0][1] = 0.0; mt->m[0][2] = 0.0; mt->m[0][3] = 0.0;
    mt->m[1][0] = 0.0; mt->m[1][1] = coeff * 1.0; mt->m[1][2] = 0.0; mt->m[1][3] = 0.0;
    mt->m[2][0] = 0.0; mt->m[2][1] = 0.0; mt->m[2][2] = coeff * 1.0; mt->m[2][3] = 0.0;
    mt->m[3][0] = 0.0; mt->m[3][1] = 0.0; mt->m[3][2] = 0.0; mt->m[3][3] = 1.0;

}


void matrix4f_init_nusc(Matrix4f *mt, float x, float y, float z) {

    mt->m[0][0] = x * 1.0; mt->m[0][1] = 0.0; mt->m[0][2] = 0.0; mt->m[0][3] = 0.0;
    mt->m[1][0] = 0.0; mt->m[1][1] = y * 1.0; mt->m[1][2] = 0.0; mt->m[1][3] = 0.0;
    mt->m[2][0] = 0.0; mt->m[2][1] = 0.0; mt->m[2][2] = z * 1.0; mt->m[2][3] = 0.0;
    mt->m[3][0] = 0.0; mt->m[3][1] = 0.0; mt->m[3][2] = 0.0; mt->m[3][3] = 1.0;

}
