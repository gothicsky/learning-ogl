#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

typedef struct {
    GLuint id;
} Shader;

bool loadShaderProgramFromFile(Shader *shader, const char *vertexShaderPath, const char *fragmentShaderPath);
bool loadShaderProgramFromData(Shader *shader, const char *vertexShaderData, const char *fragmentShaderData);

void bind(Shader *shader);
void clear(Shader *shader);


#endif
