#version 330 core //version

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;
layout(location = 2) in vec2 aTexCoord;

out vec3 v_color;
out vec3 v_position;
out vec2 TexCoord;

uniform float u_time;
uniform mat4 gWorld;
uniform vec2 u_resolution;
uniform vec2 u_mouse;

void main() {

    vec2 mN = (u_mouse.xy/u_resolution.xy) * 2.0 - 1.0;
    mN.y = -mN.y;


    gl_Position = gWorld * vec4(in_position, 1); // gWorld * vec4

    v_color = in_color;
    v_position = in_position;
    TexCoord = aTexCoord;


}
