#version 430

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;
out vec2 tc;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

// 顶点着色器的 binding 看不懂. 不知道怎么来的？也不知道怎么走的？
layout (binding = 0) uniform sampler2D samp;

// gl_Position 表示顶点的位置
void main(void){
    gl_Position = proj_matrix * mv_matrix * vec4(pos, 1.0);

    tc = texCoord;
}