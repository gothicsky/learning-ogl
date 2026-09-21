#pragma once

typedef struct {

    float x, y, z;

} Vector3f;

typedef struct {

    float m[4][4];

} Matrix4f;


void matrix4f_init_usc(Matrix4f *mt, float coeff);
void matrix4f_init_nusc(Matrix4f *mt, float x, float y, float z);


//translation
void matrix4f_init_translation(Matrix4f *mt, float x, float y, float z);

//rotation
void matrix4f_init_rot_x(Matrix4f *mt, float t);
void matrix4f_init_rot_y(Matrix4f *mt, float t);
void matrix4f_init_rot_z(Matrix4f *mt, float t);

//Multiplication
void mult_matrix4f(const Matrix4f *mt1, const Matrix4f *mt2, Matrix4f *res);
