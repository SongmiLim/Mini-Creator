#ifndef LIGHT_CUBE_FS_H
#define LIGHT_CUBE_FS_H

namespace mini_creator {
namespace graphics {
namespace shader {

static const char *light_cube_fs = R"(
#version 330 core
out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 1.0, 0.0, 1.0);
}
)";

} // namespace shader
} // namespace graphics
} // namespace mini_creator

#endif // LIGHT_CUBE_FS_H