#ifndef BOUNDING_BOX_FS_H
#define BOUNDING_BOX_FS_H

namespace mini_creator {
namespace graphics {
namespace shader {

static const char *bounding_box_fs = R"(
    #version 330 core

    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0, 0.0, 0.0, 1.0); 
    }
)";

} // namespace shader
} // namespace graphics
} // namespace mini_creator

#endif // BOUNDING_BOX_FS_H