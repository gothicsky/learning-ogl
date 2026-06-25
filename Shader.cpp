#include "../include/Shader.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef PRINT_LINE
#define PRINT_LINE (fprintf(stdout, "On line: %d", __LINE__))
#endif

#ifndef  PRINT_ERR
#define PRINT_ERR(s) (fprintf(stderr ,"\nThere is an error: %s\n", (s)))
#endif


char *readEntireFile(const char *);
GLint createShaderFromData(const char*, GLenum);

bool loadShaderProgramFromData(Shader *shader, const char *vertexShaderData, const char *fragmentShaderData) {

                                                                                                        //--
    //compile shader
    GLuint vertexId = createShaderFromData(vertexShaderData, GL_VERTEX_SHADER);

    if (vertexId==0) { //Check ==0 instead of ==NULL because createSFD returns a GLint
        return 0;
    }
                                                                                                        //compile two shaders, return 0 if there is an error
    //compile shader
    GLuint fragmentId = createShaderFromData(fragmentShaderData, GL_FRAGMENT_SHADER);

    if (fragmentId==0) {
        return 0;
    }

                                                                                                        //--
    //if all is good, create a program
    shader->id = glCreateProgram();

    //attach the shaders
    glAttachShader(shader->id, vertexId);
    glAttachShader(shader->id, fragmentId);

    //link the shaders
    glLinkProgram(shader->id);

    //delete the shaders we created after linking them

    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);

    //check for errors again, identical to error check in createShaderFromData except we check for GL_LINK_STATUS instead of GL_COMPILE_STATUS
    GLint result = 0;
    glGetProgramiv(shader->id, GL_LINK_STATUS, &result); //program not shader

    if (!result) {
        char *message;
        int l =0;
        glGetProgramiv(shader->id, GL_INFO_LOG_LENGTH, &l); //program not shader

        message = (char *)malloc(sizeof(char) * l);

        glGetProgramInfoLog(shader->id, l, &l, message); //program not shader
        fprintf(stderr ,"\n%s\n", message);
        free(message);

        glDeleteProgram(shader->id); //if there is an error delete program instead of shader
        shader->id = 0;
        return 0;
    }

    //if everything is ok
    glValidateProgram(shader->id);

    return true;
}

bool loadShaderProgramFromFile(Shader *shader, const char *vertexShaderPath, const char *fragmentShaderPath) {

    char *vertexData = readEntireFile(vertexShaderPath);
    char *fragmentData = readEntireFile(fragmentShaderPath);

    if (vertexData == NULL || fragmentData == NULL) {

        free(vertexData);
        free(fragmentData);

        fprintf(stderr ,"Couldn't read either vertexData or fragmentData");
        return false;
    }

    bool rez = loadShaderProgramFromData(shader, vertexData, fragmentData);

    free(vertexData);
    free(fragmentData);

    return rez;

}

GLint createShaderFromData(const char *data, GLenum shaderType) {

    GLuint shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &data, NULL);
    glCompileShader(shaderId);

    GLint result = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

    if (!result) {

        char *message;
        int l=0;

        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &l);

        if (l) {
            message = (char *)malloc(sizeof(char) * l);

            if (message != NULL) {
                glGetShaderInfoLog(shaderId, l, &l, message);

                //message[l - 1] = '\0'; // glGetShaderInfoLog does this automatically
                fprintf(stderr ,"%s:\n%s\n", data, message);
                free(message);
            }
        }
        else {
            fprintf(stderr , "%s\nunknown error\n", data);
        }

        glDeleteShader(shaderId);

        shaderId = 0;
        return shaderId;
    }

    return shaderId;
}


char * readEntireFile(const char *filename) {

    char *text;
    int flenght=0, count=0, numLines=0;

    FILE *infile = fopen(filename, "r");

    if (infile == NULL) {
        fprintf(stderr ,"Couldn't open %s", filename);
        return NULL;
    }

    fseek(infile, 0, SEEK_END);
    flenght = ftell(infile);
    rewind(infile);

    text = (char *)malloc((flenght+1) * sizeof(char));

    size_t flRead = fread(text, sizeof(char) ,flenght ,infile);
    text[flRead]='\0';
    if (flRead != flenght) {
        PRINT_ERR("Couldn't read whole file");
    }

    return text;
}
