#version 430
in vec4 varyingColor;
out vec4 fragColor;

struct PositionalLight
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec3 position;
};

struct Material
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

uniform vec4 globalAmbient;
uniform PositionalLight light;
uniform Material material;
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform mat4 norm_matrix;

in vec2 tc;

layout (binding = 0) uniform sampler2D samp;

void main(void){
    fragColor = 0.5*varyingColor + 0.5* texture(samp, tc);
}