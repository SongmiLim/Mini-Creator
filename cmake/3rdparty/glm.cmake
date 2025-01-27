include(FetchContent)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e
)

FetchContent_MakeAvailable(glm)
set(PROJECT_LINK_LIBS ${PROJECT_LINK_LIBS} PRIVATE glm::glm)


