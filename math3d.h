#pragma once

typedef struct {

    float x, y, z;

} Vector3f;

typedef struct {

    float m[4][4];

} Matrix4f;

void matrix4f_init_translation(Matrix4f *mt, float x, float y, float z);
