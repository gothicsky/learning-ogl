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

## Displaying things

Every time we draw something, we draw it into an internal buffer. In order to display that thing we draw onto the buffer we need to swap that buffer with the window. 

So first draw on internal buffer then swap it with the one on the screen 

## Passing attribute data to gpu

#### Creating and filling a buffer

Opengl is a State Machine
_State Machine: Has a lot of global variables and uses the same things until you change them_

In order to pass data into CPU, after defining that data, we should: 
- first create a buffer 
- then use that buffer (dictate we will work on that buffer)
- lastly draw on that buffer

To draw on another buffer we should switch from using previous buffer to using the current buffer. 

_Binding: using a buffer_
_Bound Buffer: the buffer that is being used_

#### Infastructure for passing the buffer to GPU

We've created a buffer and placed data into it in the previous part, but that buffer hasn't been passed anywere yet nor has it been defined. 
Every GPU currently available has a minimum of sixteen attributes, which are indexed from zero ([0]->[15])
So we can assign 0 as the vertex attribute and 1 as color(fragment) then we should tell opengl how to read this data, finally defining it. 

## Loading Shaders 

A shader has two components _fragment shader_ and _vertex shader_ their combination is called a program in ogl terms. 

Since we will write shaders in .frag and .vert files we want to first read them, afterwards we will load and combile and link them together. 

We will have four main functions: LoadShaderProgramFromFile for reading and loading shader content from file
                                  LoadShaderProgramFromData for compiling and linking 
                                  bind for telling ogl to use the shader
                                  clear for deleting the shaders 



# How it all works together (Coding Part)

### a. Directives
include Glad //ogl
include Glfw //screen

include standart libraries you need

include openglErrorReporting.h //Comes with the llgd's ogl setup


### c. Data we will be passing

Define a global (preferably float) array for the attributes we want to pass to the gpu 



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

5. Enable ogl error reporting
Functions used: enableReportGlErrors()
- enable error report for ogl errors using the function 

8. Generating buffer we will use to pass our data to gpu 
Functions used: glGenBuffers(), glBindBuffer() ,glBufferData() 
- First declare, define then initialize the buffer to 0. $^2$
- Secondly generate an ID for that buffer 
- Then bind the buffer you want to use 
- Lastly fill that buffer with data that we want to pass  

9. Defining how we want to pass our data to GPU
Functions used: glEnableVertexArray(), glVertexAttribPointer()
- Enable attribute for position
- Tell how you want this data to be processed$^3$ 
- Repeat for other attributes such as color, that are in the buffer you are using

6. Window loop 
Functions used: glfwWindowShouldClose(), glClear(), glfwSwapBuffers(), glfwPollEvents(), glDrawArrays()
Macros used: GL_COLOR_BUFFER_BIT
- Create a loop with ShouldClose function returning true for our window as it's condition 
- Clear the screen $^1$

- (After defining data for the buffer and loading shaders and writing shaders) Draw Triangle 

- Swap buffer to display things on the screen after rending them
- Check for events 

7. Cleansing 
Functions used: glfwDestroyWindow(), glfwTerminate()
- Before terminating the main loop, destroy the window 
- Terminate glfw


### d. Loading Shaders 

#### a. Shaders.h 
1. Create a struct for id and then write function prototypes for loading shaders using the shader->id 

#### b. Shaders.cpp 

##### readEntireFile()
return type: char *
arguments: char *filename

##### createShaderFromData()
return type: GLint
arguments: const char *data, GLenum shaderType
Functions used: glCreateShader(), glShaderSource(), glCompileShader() //for the main body
                glGetShaderiv(), glGetShaderInfoLog(), glDeleteShader() //for the error check

1. Variable with type GLuint gets shaderId 
2. Give data to shader. (via the shaderId)
3. Compile the shader. (via the shaderId)

//Checking for errors 

1. Initialize some variable result, of type GLint to 0 
2. Ask opengl for any errors(GL_COMPILE_STATUS), if there is save that to result
3. The function will return 0 if no errors check for that, if there is an error:
4. Initialize some string, message and int l to 0
5. Ask opengl for the error message's lenght (GL_INFO_LOG_LENGHT), save that to l 
6. Check if the lenght is greater than 0, otherwise there is an unknown error 
7. If there is an error message, allocate memory to message at the lenght of the error log 
8. Get info log and save it to message using the function
9. Print the message as an error, end of if
10. delete the shader, return 0

//if no errors

4. Return shaderId 

##### loadShaderProgramFromData()
return type: bool
arguments: Shader *shader, const char *vertexShaderData, const char *fragmentShaderData
Functions used: createShaderFromData(), glCreateProgram(), glAttachShader(), glLinkProgram(), glDeteShader(), glValidateProgram()
                glGetProgramiv(), glGetProgramInfoLog(), glDeleteProgram() //for the error check

1. Compile vertex shader by creating a some variable, vertexId and assigning it the shaderId from createShader function with vertexShaderData and shader type as it's arguments 
2. Check if vertexId = 0, if so return 0 
3. Same step for fragmentId with fragmentShaderData as it's argument (also check id) 
4. Id in shader struct gets an id from glCreateProgram
5. Attach both fragment shader and vertex shader using their id's to programs id 
6. Link the id in struct shader 
7. Delete the vertex and fragment shader since we linked them and don't need them seperately anymore 

//Check for error 

1. Initialize some variable result, of type GLint to 0 
2. Ask opengl for any errors(GL_LINK_STATUS), if there is save that to result
3. The function will return 0 if no errors check for that, if there is an error:
4. Initialize some string, message and int l to 0
5. Ask opengl for the error message's lenght (GL_INFO_LOG_LENGHT), save that to l 
6. Allocate memory to message at the lenght of the error log 
7. Get info log and save it to message using the function
8. Print the message as an error, free the message
9. Delete the program via the id in the shader struct (where we saved the program id to)
10. return 0 

8. Validate program 
9. return true 

##### loadShaderProgramFromFile()
return type: bool
arguments: Shader *shader, const char *vertexShaderPath, const char *fragmentShaderPath
Functions used: readEntireFile(), loadShaderProgramFromData() 

1. read file for vertex shader to a string (for example vertexData), do the same for fragment shader file 
2. Check if any of the strings are NULL, if so free them 
3. declare a variable of bool type as the result from loadShaderProgramFromFile() with the data we just got as it's arguments
4. free the Data we read previously
5. return the result 




### Notes
$^1$ glClear automatically clears to black color, in order to reset to a different color, run glClearColor before glClear. glClearColor takes effect only when glClear is run. 

$^2$ Can also declare an array of buffers, in that case glGenBuffers(n, buffer) where n is is num of entries and buffer is the begging address to the array. When binding an array of buffers bind one by one buffer[0] etc. 
Easy to miss: Every time we call bufferData it rewrites buffer with newData, glBufferSubData to rewrite only a part of it instead  

glBufferData vs glBufferSubData

glBufferData(   GL_ARRAY_BUFFER, sizeof(Data), data,       GL_STATIC_DRAW)
                 buffer type       size        data           usage 

glBufferSubData(GL_ARRAY_BUFFER,    0,      sizeof(data),  &data )
                 buffer type      offset    number of     source data
                                          bytes to copy


$^3$ in glVertexAttribData(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)\*6, (void *)(sizeof(float)\*3)) for the pointer (void \*) type conversion is neccessary

$^4$ arg2 is how many strings we have in the data we are passing(arg3)

### Resources

- Useful website for finding ogl functions *https://docs.g*_
