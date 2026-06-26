# Theory

-Opengl has instructions to be implemented and the gpu runs these commands, we need an ogl loader in order to work with these commands such as (GLAD, GLEW etc.) 

-Old opengl models where you don't have much flexibility(fixed functions pipeline) are called deprecation models (check)models before 3.0, these are models are also legacy opengl

_Pipeline: Series of actions applied to some input to get an output_

Firstly we will want to 
- [ ]Get a model
- [ ]Put it on the screen
- [ ]Fill in the triangles

_Vertex: A point in 3D space with various attributes such as position and color_

_Fragment: Individual pixels that make up the triangle when we connect the three vertices to from a triangle_

Coordinate system in opengl has bounds, $0 < x < 1$ and $0 < y < 1$ (this far into the tutorial we ignore the z)

## Colors

Opengl's color scheme is also RGB like many other things. 

In RGB each color usually ranges from 0 to 255, which we can represent as an unsigned integer. However since we use float values between 0 and 1 to store colors  we need a way to convert one value to the other. 

To convert color value in float to a color value in bytes (between 0 and 255), we can multiply the values with 255. We can divide by 255 to get it the other way around!

## Buffer Idea 

Since we want to display a 3D object on our screen, we will need to access it occasionnaly. Since we normally store the objects in RAM, we will have to send it to the GPU(which is quite some distance away) from there and it will be redundant. 

_Buffer: a block of memory, similar to an array_

Instead we will send the object to buffer which is inside gpu's vram (video memory), store it there with a bufferId and easily access it from there when we need it!

Additionally there is no specific requirement for the way which we pass data to the gpu in ogl. We can structure it however we like but some ways are more practical than others.


# How it all works together (Coding Part)

### a. Directives
include Glad //ogl
include Glfw //screen

include standart libraries you need

include openglErrorReporting.h //Comes with the llgd's ogl setup

### b. Main function

1. Ascension 
Note: Can't load ogl before setting context
- Initialize glfw with an error check
- (Optional) Add glfwWindowHint so it works on Apple devices


2. Create a window
Functions used: glfwCreateWindow()
- Declare and define a variable of GLFWwindow type then check if it has been successful.

3. Set Context for window
Context: Current state of every ogl setting and resources associated to a window or a rendering surface
Functions used: glfwMakeContextCurrent()
- Run the ogl function for setting context for the window we created.

4. Load ogl to the window
Functions used: gladLoadGLLoader(), glfwGetProcAddress() 
- Run gladLoadGLLoader with glfwGetProcAddress type converted to (GLADloadproc) as it's argument and do an error check for it.

5. Enable ogl error reported
Functions used: enableReportGlErrors()
- enable error report for ogl errors using the function 

6. Window loop 
Functions used: glClear(), glfwWindowShouldClose(), glfwSwapBuffers(), glfwPollEvents()
Macros used: GL_COLOR_BUFFER_BIT
- Create a loop with ShouldClose function returning true for our window as it's condition 
- First clear the screen *$^1$
















### Appendix
