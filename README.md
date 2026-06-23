# Theory

-Opengl has instructions to be implemented and the gpu runs these commands, we need an ogl loader in order to work with these commands such as (GLAD, GLEW etc.) 

-Old opengl models where you don't have much flexibility(fixed functions pipeline) are called deprecation models (check)models before 3.0, these are models are also legacy opengl

_Pipeline: Series of actions applied to some input to get an output_

Firstly we will want to 
-[]Get a model
-[]Put it on the screen
-[]Fill in the triangles

_Vertex: A point in 3D space with various attributes such as position and color_

_Fragment: Individual pixels that make up the triangle when we connect the three vertices to from a triangle_

Coordinate system in opengl has bounds, $0 < x < 1$ and $0 < y < 1$ (this far into the tutorial we ignore the z)

## Colors

Opengl's color scheme is also RGB like many other things. 

In RGB each color usually ranges from 0 to 255, which we can represent as an unsigned integer. However since we use float values between 0 and 1 to store colors  we need a way to convert one value to the other. 

To convert color value in float to a color value in bytes (between 0 and 255), we can multiply the values with 255. We can divide by 255 to get it the other way around!

## Buffer Idea 

