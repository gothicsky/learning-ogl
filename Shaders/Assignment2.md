We pass the values for position instead of color which just changes the  value and not the idea for what's happening. The interesting thing in this question is the different outcomes we get when we have 0 and negative values. Since passing in position only changes the value of color I will talk about the color values. If we have 0(which corresponds to black) for colors at a vertex, that region is still invaded by the other colors in the vertexes when interpolated. If we have a negative value for a color in a vertex then the region of color from that vertex is filtered from the color with the negative value. Increasing the magnitude of the negative value leads to a larger region for filtering.





Another interesting example comparison



float triangleData[] = {

    //positions  colors

    //x, y,  z   r, g, b

    0, 1, 0,   1, 1, 0, //vertex 1

    -1, -1, 0, 0, 0, 0, //vertex 2

    1, -1, 0,  0, 1, 1 //vertex 3

};





float triangleData[] = {

    //positions  colors

    //x, y,  z   r, g, b

    0, 1, 0,   1, 1, 0, //vertex 1

    -1, -1, 0, 0, -1, 0, //vertex 2

    1, -1, 0,  0, 1, 1 //vertex 3

};



Question 2.

Main:

float triangleData[] = {
    //positions  colors
    //x, y,  z   r, g, b
    0, 1, 0.7,   0.7, 0.8, 0.7, //vertex 1
    -1, -1, 1, 0.1, 0.4, 0.6, //vertex 2
    1, -1, 0.6,  0.9, 0.4, 0.6 //vertex 3
};
Vertex Shader:

#version 330 core //version
 
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;
 
out vec3 v_color;
out vec3 v_position;
 
void main() {
 
    gl_Position = vec4(in_position, 1);
 
    v_color = in_color;
    v_position = in_position;
 
    if (v_position.x<0) {
        v_position.x *= 0;
        v_position.x += 0.2;
    }
    if (v_position.x==0){
        v_position.x += 0.6;
    }
 
 
    if (v_position.y<0) {
        v_position.y *= 0;
        v_position.y += 0.3;
    }
}

Note: The actual solution is much easier but a bit harder to realize I guess...
