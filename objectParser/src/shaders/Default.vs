#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 textureUV;
layout (location = 2) in vec3 normals;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 textureCoord;
out vec3 Normals;
out vec3 FragPos;

void main()
{
    FragPos = vec3(model * vec4(pos, 1.0));
    Normals = mat3(transpose(inverse(model))) * normals;  
    
    gl_Position = projection * view * model * vec4(pos, 1.0);
}