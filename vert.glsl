#version 430

// 两个输入参数，1. 第一个是输入的顶点位置，2. 第二个是输入的顶点法线
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 a_normal;

// 输出参数
out vec4 varyingColor;

out vec2 tc;

// 顶点着色器的 binding 看不懂. 不知道怎么来的？也不知道怎么走的？
layout (binding = 0) uniform sampler2D samp;

// 考虑这是点光源还是啥？？光源真的很重要
struct PositionalLight {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec3 position;
};

// 材质的属性
struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    // 材质的高光强度
    float shininess;
};

// 这是全局环境光
uniform vec4 globalAmbient;

// 这是点光源
uniform PositionalLight  light;
// 这是材质
uniform Material material;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform mat4 normal_matrix;

void main(){
    // 计算顶点的位置
    vec4 position = mv_matrix * vec4(a_position, 1.0);
    // 计算顶点的法线
    vec3 normal = (normal_matrix * vec4(a_normal, 1.0)).xyz;
    // 计算光线方向
    // light.position c++层计算好的相对位置
    // position.xyz c++层计算好的顶点位置
    vec3 lightDirection = normalize(light.position - position.xyz);
    // 计算光线与法线的点积
    float nDotL = max(dot(normal, lightDirection), 0.0);
    // 计算光线与摄像机的方向
    vec3 eyeDirection = normalize(-position.xyz);
    // 计算反射
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    // 计算高光强度
    float sDot = pow(max(dot(reflectionDirection, eyeDirection), 0.0), material.shininess);
    // 计算环境光
    vec4 ambient = material.ambient * globalAmbient + light.ambient * material.ambient;
    // 计算漫反射光
    vec4 diffuse = material.diffuse * light.diffuse * nDotL;
    // 计算高光
    vec4 specular1 = material.specular * light.specular * sDot;
    // 计算颜色
    varyingColor = ambient + diffuse + specular1;
    //varyingColor = vec4((ambient.xyz + diffuse.xyz + specular1.xyz),0.5);
    // 计算深度值
    gl_Position = proj_matrix * position;

    tc = texCoord;
}
