//#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "openglErrorReporting.h"
#include "../include/Shader.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PRINT_ERR(s) (fprintf(stderr ,"\nThere is an error: %s\n", s))
#define PRINT_LINE (fprintf(stdout, "On line: %d", __LINE__))



float triangleData[] = {
  //positions  colors
  //x, y,  z   r, g, b
    0, 1, 0,   1, 0, 0, //vertex 1
    -1, -1, 0, 0, 1, 0, //vertex 2
    1, -1, 0,  0, 0, 1 //vertex 3
};


// // different approach example 1
// float triangleData[] = {
//     //positions
//     //x, y,  z
//     0, 1, 0,
//     -1, -1, 0,
//     1, -1, 0,
//
//     //colors
//     //r, g, b
//     1, 0, 0,
//     0, 1, 0,
//     0, 0, 1
// };





int main()
{


    if (!glfwInit())
    {
        PRINT_ERR("Couldn't initialize glfw.");
        exit(1);
    }

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#endif

    GLFWwindow *window = glfwCreateWindow(640, 480, "Ex", NULL, NULL);

    if (!window)
    {
        fprintf(stderr, "Failed creating window.\n");
        exit(1);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "Couldn't load opengl after setting context.\n");
        exit(1);
    }

    enableReportGlErrors();

    GLuint buffer = 0;


#pragma region buffer
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);


    // // different approach example 1
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, 0);
    //
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void *)(sizeof(float)*9));

    //define attrib reprs positon
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, 0);

    //define attrib reprs color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void *)(sizeof(float)*3));

#pragma endregion



#pragma region loadShader

    Shader shader;

    loadShaderProgramFromFile(&shader, RESOURCES_PATH "myshader.vert", RESOURCES_PATH "myshader.frag");

    bind(&shader);

#pragma endregion


    while (!glfwWindowShouldClose(window))
    {


        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
