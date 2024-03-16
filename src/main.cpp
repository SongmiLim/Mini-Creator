#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(int argc, const char **argv)
{
    SPDLOG_INFO("Start program");

    // initialize glfw
    SPDLOG_INFO("Initialize glfw");
    if (!glfwInit())
    {
        const char *description = nullptr;
        glfwGetError(&description);
        SPDLOG_ERROR("failed to initialize glfw: {}", description);
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    // create glfw window
    SPDLOG_INFO("Create glfw window");
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME,
                                   nullptr, nullptr);
    if (!window)
    {
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // glad를 활용한 OpenGL 함수 로딩
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        SPDLOG_ERROR("failed to initialize glad");
        glfwTerminate();
        return -1;
    }
    // auto glVersion = glGetString(GL_VERSION);
    // SPDLOG_INFO("OpenGL context version: {}", glVersion);

    // start glfw loop
    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}