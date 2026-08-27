//#define GLFW_INCLUDE_NONE
#include <ctime>
#include <GLFW/glfw3.h>

#include "openglErrorReporting.h"
#include "../include/Shader.h"
#include "math3d.h"


#define  STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "imgui.h"

#define PRINT_ERR(s) (fprintf(stderr ,"\nThere is an error: %s\n", s))
#define PRINT_LINE (fprintf(stdout, "On line: %d", __LINE__))


//Tutorial Triangle

// float triangleData[] = {
//   //positions  colors
//   //x, y,  z   r, g, b
//     0, 1, 0,   1, 0, 0, //vertex 1
//     -1, -1, 0, 0, 1, 0, //vertex 2
//     1, -1, 0,  0, 0, 1 //vertex 3
// };


//Tutorial Rectangle

// float triangleData[] = {
//     //positions  colors
//     //x, y,  z           r, g, b    texCoord
//       0.5, 0.5,  0.0,     1, 0, 0,    //1., 1.,              //vertex 1
//       0.5, -0.5, 0.0,     0, 1, 0,    //1., 0.,              //vertex 2
//       -0.5, -0.5, 0.0,    0., 0, 1,   //0., 1.               //vertex 3
//       -0.5, 0.5, 0.0,    0., 0, 1,   //0., 1.               //vertex 4
// };

float triangleData[] = {
    //positions  colors
    //x, y,  z            r, g, b     texCoord
      0.5, 0.5,  0.0,     1, 0, 0,    1., 1.,              //vertex 1
      0.5, -0.5, 0.0,     0, 1, 0,    1., 0.,              //vertex 2
      -0.5, -0.5, 0.0,    0, 0, 1,    0., 0.,              //vertex 3
      -0.5, 0.5, 0.0,     0, 0, 1,    0., 1.               //vertex 4
};


//Triangle Data for filled background 2 triangles

// float triangleData[] = {
//     //positions  colors
//     //x, y,  z   r, g, b
//     -1, 1, 0,   1, 0, 0, //vertex 1
//     -1, -1, 0, 0, 1, 0, //vertex 2
//     1, -1, 0,  0, 0, 1, //vertex 3
//     1, 1, 0,  0, 0, 1 //vertex 4
// };

// float triangleData[] = {
//     //positions  colors
//     //x, y,  z   r, g, b
//     -1.0, 1.0, 0.0,   1, 0, 0, //vertex 1
//     -1.0, -1.0, 0.0, 0, 1, 0, //vertex 2
//     1.0, -1.0, 0.0,  0, 0, 1, //vertex 3
//     1.0, 1.0, 0.0,  0, 0, 1 //vertex 4
// };

// float triangleData[] = {
//     //positions  colors
//     //x, y,  z   r, g, b
//     0.5, 0.5, 0,   1, 0, 0, //vertex 1
//     -0.5, 0.5, 0, 0, 1, 0, //vertex 2
//     -0.5, -0.5, 0,  0, 0, 1, //vertex 3
//     //second triangle
//     0.5, -0.5, 0,  0, 0, 1,
//     //Third triangle
//     0.7, 0.5, 0,    0, 1, 0,
//     0.7, 0.7, 0,     0, 0, 1,
//     //Fourth triangle
//     -0.7, -0.5, 0,    0, 1, 0,
//     -0.7, -0.7, 0,     0, 0, 1
//
// };

// float triangleData[] = {
//     //positions  colors
//     //x, y,  z   r, g, b
//     //second triangle
//     0.5, -0.5, 0, 0, 0, 1,
//     0.5, 0.5, 0,   1, 0, 0, //vertex 1
//     -0.5, 0.5, 0, 0, 1, 0, //vertex 2
//     -0.5, -0.5, 0,  0, 0, 1 //vertex 3
//
// };

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


float texCoords[] = {

    0. , 0. , //low-left corner
    1. , 0. , //low-right corner
    0.5 , 1.  //top-center corner

};


unsigned short indices[] = {

    0, 1, 2, //first triangle
    0, 2, 3,  //second triangle
    // 0, 4, 5, // third triangle
    // 2, 7, 6  // fourth triangle

};



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

#pragma region vao

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

#pragma endregion


#pragma region buffer

    GLuint buffer = 0;
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, 0); //8 was 6 bfr texture

    //define attrib reprs color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (void *)(sizeof(float)*3));

    //texture part
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float)*8, (void *)(sizeof(float)*6));


#pragma endregion


#pragma region index buffer

    GLuint iBuffer = 0;
    glGenBuffers(1, &iBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

#pragma endregion


    // glad_glEnable(GL_CULL_FACE);
    // glad_glFrontFace(GL_CW);
    // glad_glCullFace(GL_BACK);

    //unbind the vao after the buffers are done
    glBindVertexArray(0);

#pragma region loadShader

    Shader shader;

    loadShaderProgramFromFile(&shader, RESOURCES_PATH "myshader.vert", RESOURCES_PATH "myshader.frag");

    bind(&shader);

    GLint gWorldLocation = uniformLocation(&shader, "gWorld");

    GLint u_time = uniformLocation(&shader, "u_time");

    GLint u_resolution = uniformLocation(&shader, "u_resolution");

    GLint u_mouse = uniformLocation(&shader, "u_mouse");

#pragma endregion


#pragma region loadTexture

    unsigned int texture1 = 0, texture2 = 0;
    glGenTextures(1, &texture1);
    glGenTextures(1, &texture2);

    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    int width = 0, height = 0, nrChannels = 0;

    //unsigned char *data = stbi_load(RESOURCES_PATH "rockbrow.jpg", &width, &height, &nrChannels, 0);
    unsigned char *data1 = stbi_load(RESOURCES_PATH "container.jpg", &width, &height, &nrChannels, 0);
    //unsigned char *data = stbi_load(RESOURCES_PATH "pig.png", &width, &height, &nrChannels, 0);

    if (data1) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
            GL_UNSIGNED_BYTE, data1);

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        fprintf(stderr, "Failed to load texture1");
    }

    //Texture2

    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char *data2 = stbi_load(RESOURCES_PATH "rockbrow.jpg", &width, &height, &nrChannels, 0);

    if (data2) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
            GL_UNSIGNED_BYTE, data2);

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        fprintf(stderr, "Failed to load texture2");
    }

    stbi_image_free(data1);
    stbi_image_free(data2);

#pragma endregion


    int choice=0;

    float scale = 0.0; //animation variable for gWorldLocation

    while (!glfwWindowShouldClose(window))
    {

        //window size and init color
        int w=0, h=0;
        glfwGetWindowSize(window, &w, &h);
        glViewport(0, 0, w, h);

        glClear(GL_COLOR_BUFFER_BIT);

        //get Mouse

        double mouseX = 0, mouseY = 0;
        glfwGetCursorPos(window,&mouseX, &mouseY);

        float glslMouseY = 0;
        glslMouseY = h - mouseY;

        //Mouse Normal

        float normalMouseX=0, normalMouseY=0;

        normalMouseX = (mouseX/w) * 2. - 1.;
        normalMouseY = (glslMouseY/h) * 2. - 1.;

        //gWorld area

        scale += 0.01;


        Matrix4f world;
        //matrix4f_init_translation(&world, sinf(scale), 0.0 ,0.0);
        matrix4f_init_translation(&world, normalMouseX, normalMouseY ,0.0);

        // uniforms
        bind(&shader);
        glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &world.m[0][0]);
        glUniform1f(u_time, (float)glfwGetTime());
        glUniform2f(u_resolution, (float)w, (float)h);
        glUniform2f(u_mouse, (float)mouseX, glslMouseY);

        glUniform1i(glGetUniformLocation(shader.id, "texture1"), 0);
        glUniform1i(glGetUniformLocation(shader.id, "texture2"), 1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glBindVertexArray(vao);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
