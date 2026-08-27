#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>


#include "stb_image/stb_image.h"

typedef struct {
    GLuint id;
} Shader;

bool loadShaderProgramFromFile(Shader *shader, const char *vertexShaderPath, const char *fragmentShaderPath);
bool loadShaderProgramFromData(Shader *shader, const char *vertexShaderData, const char *fragmentShaderData);

void bind(Shader *shader);
void clear(Shader *shader);

GLint uniformLocation(Shader *shader, const char *name);

GLuint load_texture2d_rep(const char *filename);

#endif
