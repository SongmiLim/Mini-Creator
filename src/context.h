#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "shader.h"
#include "program.h"
#include "buffer.h"
#include "vertex_layout.h"
#include "texture.h"
#include "mesh.h"
#include "model.h"
#include "framebuffer.h"

CLASS_PTR(Context)
class Context {
public:
    static ContextUPtr Create();
    void Render();    
    void ProcessInput(GLFWwindow* window);
    void Reshape(int width, int height);
    void MouseMove(double x, double y);
    void MouseButton(int button, int action, double x, double y);
    void MouseScroll(double xoffset, double yoffset);

private:
    Context() {}
    bool Init();
    ProgramUPtr m_program;
    ProgramUPtr m_simpleProgram;
    ProgramUPtr m_textureProgram;

    MeshUPtr m_box;
    MeshUPtr m_plane;

    ModelUPtr m_model;
    
    TextureUPtr m_texture;
    float m_gamma {1.0f};

    // framebuffer
    FramebufferUPtr m_framebuffer;

    //camera parameter
    glm::vec3 m_cameraPos { glm::vec3(0.0f, 0.0f, 10.0f) };
    glm::vec3 m_cameraFront { glm::vec3(0.0f, 0.0f, -1.0f) };
    glm::vec3 m_cameraUp { glm::vec3(0.0f, 1.0f, 0.0f) };
    float m_cameraPitch { 0.0f };
    float m_cameraYaw { 0.0f };
    float m_cameraFov { 45.0f };
    bool m_cameraControl { false };
    glm::vec2 m_prevMousePos { glm::vec2(0.0f) };

    int m_width {WINDOW_WIDTH};
    int m_height {WINDOW_HEIGHT};

    // animation
    bool m_animation { true };

    // clear color
    glm::vec4 m_clearColor { glm::vec4(0.1f, 0.1f, 0.1f, 0.0f) };

    // light parameter
    struct Light {
    glm::vec3 position { glm::vec3(3.0f, 3.0f, 3.0f) };
    glm::vec3 ambient { glm::vec3(0.5f, 0.5f, 0.5f) };
    glm::vec3 diffuse { glm::vec3(0.5f, 0.5f, 0.5f) };
    glm::vec3 specular { glm::vec3(1.0f, 1.0f, 1.0f) };
    };
    Light m_light;

    glm::vec3 m_location { glm::vec3(1.0f, 1.0f, 1.0f) };
    glm::vec3 m_scale { glm::vec3(1.0f, 1.0f, 1.0f) };
};

#endif // __CONTEXT_H__