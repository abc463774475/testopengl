#version 430

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertNormal;

out vec4 varyingColor;

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
uniform mat4 normal_matrix;

void main(void){

    vec4 P = mv_matrix * vec4(vertPos, 1.0);
    vec4 N = normal_matrix * vec4(vertNormal, 1.0);
    //    vec4 N = normalize((norm_matrix * vec4(vertNormal, 1.0)).xyz);
    vec4 L = vec4(normalize(light.position - P.xyz),1.0);

    float nDoL = max(dot(N.xyz, L.xyz), 0.0);
    //
    vec3 V = normalize(-P.xyz);

    vec3 R = reflect(-L, N).xyz;

    float sDot = pow(max(dot(R, V), 0.0), material.shininess);

    vec3 ambient = ((globalAmbient * material.ambient) + (light.ambient * material.ambient)).xyz;
//    vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * max(dot(N, L), 0.0);
    vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * nDoL;

    vec3 specular = light.specular.xyz *material.specular.xyz * sDot;

    varyingColor = vec4((ambient + diffuse + specular), 0.5);

    gl_Position = proj_matrix * mv_matrix * vec4(vertPos, 1.0);
}