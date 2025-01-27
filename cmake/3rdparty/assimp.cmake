include(FetchContent)

FetchContent_Declare(
  assimp
  GIT_REPOSITORY https://github.com/assimp/assimp.git
)

FetchContent_MakeAvailable(assimp)
set(PROJECT_LINK_LIBS ${PROJECT_LINK_LIBS} assimp)