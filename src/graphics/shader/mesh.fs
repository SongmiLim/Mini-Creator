#version 330 core

struct Material {
    vec3 diffuse;
    vec3 specular;
    vec3 ambient;
    float shininess;
};

uniform Material material;
uniform sampler2D textureMap;
uniform vec3 lightPos;
uniform vec3 cameraPos;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

void main() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(cameraPos - FragPos);

    vec3 ambient = material.ambient * texture(textureMap, TexCoords).rgb;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = material.diffuse * diff * texture(textureMap, TexCoords).rgb ;

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
