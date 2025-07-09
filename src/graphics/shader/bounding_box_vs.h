#ifndef BOUNDING_BOX_VS_H
#define BOUNDING_BOX_VS_H

namespace mini_creator {
namespace graphics {
namespace shader {

static const char *bounding_box_vs = R"(
#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0);
}
)";

} // namespace shader
} // namespace graphics
} // namespace mini_creator

#endif // BOUNDING_BOX_VS_H