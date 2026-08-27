#version 330 core

layout (location = 0) out vec4 out_color;

in vec3 v_color;
in vec3 v_position;
in vec2 TexCoord;

out vec4 FragColor;

uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {

    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec2 m = u_mouse.xy/u_resolution.xy;

    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.4);

    //vec4(st.x, st.y, sin(u_time), 1.)
    //FragColor = vec4(v_color , 1);


    //out_color = vec4((sin(u_time + v_position+1)/2), 1);

}
