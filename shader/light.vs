#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 transform;
uniform mat4 modelTransform;

out VS_OUT {
    vec3 normal;
    vec2 texCoord;
    vec3 position;
} vs_out;

void main() {
    gl_Position = transform * vec4(aPos, 1.0);
    vs_out.normal = (transpose(inverse(modelTransform)) * vec4(aNormal, 0.0)).xyz;
    vs_out.texCoord = aTexCoord;
    vs_out.position = (modelTransform * vec4(aPos, 1.0)).xyz;
}