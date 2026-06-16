include(FetchContent)

# Trim the assimp build: we only import meshes, so skip exporters, tools,
# and tests. Must be set before FetchContent_MakeAvailable.
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  assimp
  GIT_REPOSITORY https://github.com/assimp/assimp.git
  GIT_TAG v5.4.3
)

FetchContent_MakeAvailable(assimp)
set(PROJECT_LINK_LIBS ${PROJECT_LINK_LIBS} assimp)