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
#include <time.h>

#include "imgui.h"

#define PI 3.141592653589

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

// float triangleData[] = {
//     //positions  colors
//     //x, y,  z            r, g, b     texCoord
//       0.5, 0.5,  0.0,     1, 0, 0,    1., 1.,              //vertex 1
//       0.5, -0.5, 0.0,     0, 1, 0,    1., 0.,              //vertex 2
//       -0.5, -0.5, 0.0,    0, 0, 1,    0., 0.,              //vertex 3
//       -0.5, 0.5, 0.0,     0, 0, 1,    0., 1.               //vertex 4
// };

float triangleData[] = {
    //positions  colors
    //x, y,  z            r, g, b     texCoord
    0.5, 0.5,  0.0,     1, 0, 0,    1., 1.,              //vertex 1
    0.5, -0.5, 0.0,     0, 1, 0,    1., 0.,              //vertex 2
    -0.5, -0.5, 0.0,    0, 0, 1,    0., 0.,              //vertex 3
    -0.5, 0.5, 0.0,     0, 0, 1,    0., 1.               //vertex 4
};

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

    GLuint buffer = 0; //actually vbo (vertex buffer object)
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

    GLuint iBuffer = 0; //actually ebo (element buffer object)
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

    GLint u_shift = uniformLocation(&shader, "u_shift");

#pragma endregion


#pragma region loadTexture

    GLuint texture[2];
    texture[0] = load_texture2d_rep(RESOURCES_PATH "container.jpg");
    texture[1] = load_texture2d_rep(RESOURCES_PATH "smiley3.jpg");

#pragma endregion


    int choice=0;

    float scale = 0.0; //animation variable for gWorldLocation
    float delta = 0.01; //scale change
    float scaling = 0.5; //scale for scaling

    float texOp = 0.0;

    // xyz for saving movement - might delete or rebrand later
    float x=0,y=0,z=0;

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

        scale += delta;

        if ((scale >= PI/4) || (scale <= -PI/4)) {
            delta *= -1.0;
        }

        Matrix4f world, m1, m2, m3;
        //matrix4f_init_translation(&world, sinf(scale), 0.0 ,0.0);
        //matrix4f_init_translation(&world, normalMouseX, normalMouseY ,0.0);

        matrix4f_init_rot_z(&m1, scale);
        matrix4f_init_translation(&m2, x, y, 0.0);
        matrix4f_init_usc(&m3, scaling);

        mult_matrix4f(&m2, &m3, &world);
        mult_matrix4f(&world, &m1, &m3);

        world = m3;

        //move and place

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

            //printf("Up key pressed \n");

            matrix4f_init_translation(&m1, normalMouseX, normalMouseY, 0.0);
            matrix4f_init_usc(&m2, scaling);

            mult_matrix4f(&m1, &m2, &world);

            x = normalMouseX;
            y = normalMouseY;

        }

        //adjust scaling

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {

            //printf("Up key pressed \n");

            if (scaling >= 0.5 && scaling <= 1.5) {
                scaling += 0.01;
            }
            else if (scaling > 1.5){
                scaling = 1.5;
            }
            else {
                scaling = 0.5;
            }

        }

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {

            //printf("Down key pressed \n");

            if (scaling >= 0.5 && scaling <= 1.5) {
                scaling -= 0.01;
            }
            else if (scaling > 1.5){
                scaling = 1.5;
            }
            else {
                scaling = 0.5;
            }

        }


        //u_shift arrow input

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {

            //printf("Up key pressed \n");

            if (texOp >= 0.0 && texOp <= 1.0) {
                texOp += 0.01;
                //printf("texOp is increased: %f \n", texOp);
            }
            else if (texOp > 1.0){
                texOp = 1.0;
            }
            else {
                texOp = 0.0;
            }

        }

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {

            //printf("Down key pressed \n");

            if (texOp >= 0.0 && texOp <= 1.0) {
                texOp -= 0.01;
                //printf("texOp is decreased: %f \n", texOp);
            }
            else if (texOp > 1.0){
                texOp = 1.0;
            }
            else {
                texOp = 0.0;
            }

        }

        // uniforms
        bind(&shader);
        glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &world.m[0][0]);
        glUniform1f(u_time, (float)glfwGetTime());
        glUniform2f(u_resolution, (float)w, (float)h);
        glUniform2f(u_mouse, (float)mouseX, glslMouseY);
        glUniform1f(u_shift, texOp);

        glUniform1i(glGetUniformLocation(shader.id, "texture1"), 0);
        glUniform1i(glGetUniformLocation(shader.id, "texture2"), 1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture[1]);

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
