//#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <openglErrorReporting.h>


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#pragma region Shader

typedef struct {
    GLuint id;
} Shader;

bool loadShaderProgramFromFile(Shader *shader, const char *vertexShaderPath, const char *fragmentShaderPath);
bool loadShaderProgramFromData(Shader *shader, const char *vertexShaderData, const char *fragmentShaderData);

void bind(Shader *shader);
void clear(Shader *shader);

#pragma endregion


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
        printf("\n%s\n", message);
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

        printf("Couldn't read either vertexData or fragmentData");
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
                printf("%s:\n%s\n", data, message);
                free(message);
            }
        }
        else {
            printf("%s\nunknown error\n", data);
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
        printf("Couldn't open %s", filename);
        return NULL;
    }

    fseek(infile, 0, SEEK_END);
    flenght = ftell(infile);
    rewind(infile);

    text = (char *)malloc((flenght+1) * sizeof(char));

    size_t flRead = fread(text, sizeof(char) ,flenght ,infile);
    text[flRead]='\0';
    if (flRead != flenght) {
        printf("Couldn't read whole file");
    }

    return text;
}


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
        fprintf(stdout, "Couldn't initialize glfw.\n");
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
        fprintf(stdout, "Failed creating window.\n");
        exit(1);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stdout, "Couldn't load opengl after setting context.\n");
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


    while (!glfwWindowShouldClose(window))
    {


        glClear(GL_COLOR_BUFFER_BIT);

        // //legacy code part
        //
        // glBegin(GL_TRIANGLES);
        // glVertex2f(0,1);
        // glColor3f(1,0,0);
        //
        // glVertex2f(-1,-1);
        // glColor3f(0,1,0);
        //
        // glVertex2f(1,-1);
        // glColor3f(0,0,1);
        //
        // glEnd();
        // //and here ends the legacy part

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}