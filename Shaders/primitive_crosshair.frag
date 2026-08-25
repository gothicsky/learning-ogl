#version 330 core

layout (location = 0) out vec4 out_color;

in vec3 v_color;
in vec3 v_position;

out vec4 FragColor;

uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;

void main() {

    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec2 m = u_mouse.xy/u_resolution.xy;


    out_color = vec4(1., 1., 1. , 1.);
    if ((int(u_mouse.x) == int(gl_FragCoord.x) ) || int(u_mouse.y) == int(gl_FragCoord.y)){
        out_color = vec4(0. , 0. , 0. , 1.0);
    }

    //out_color = vec4(sin(u_time), v_color.gb , 1);
    //out_color = vec4((sin(u_time + v_position+1)/2), 1);

}
