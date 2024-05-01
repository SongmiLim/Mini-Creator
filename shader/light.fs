#version 330 core

in VS_OUT {
    vec3 normal;
    vec2 texCoord;
    vec3 position;
} fs_in;

out vec4 fragColor;

uniform vec3 viewPos;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;
 
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;

void main() {
    vec3 texColor = texture2D(material.diffuse, fs_in.texCoord).xyz;
    vec3 ambient = texColor * light.ambient;

    vec3 lightDir = normalize(light.position - fs_in.position);
    vec3 pixelNorm = normalize(fs_in.normal);
    float diff = max(dot(pixelNorm, lightDir), 0.0);
    vec3 diffuse = diff * texColor * light.diffuse;

    vec3 specColor = texture2D(material.specular, fs_in.texCoord).xyz;
    vec3 viewDir = normalize(viewPos - fs_in.position);
    vec3 reflectDir = reflect(-lightDir, pixelNorm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spec * specColor * light.specular;

    vec3 result = ambient + diffuse + specular;

    fragColor = vec4(result, 1.0);
}