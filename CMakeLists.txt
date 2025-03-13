cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    Jengine
    VERSION 0.1.0
    DESCRIPTION "Particle simulation built in c++"
    HOMEPAGE_URL "https://joswinjohn.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    Jengine_lib OBJECT
    src/lib.cpp
)

target_include_directories(
    Jengine_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
)

target_compile_features(Jengine_lib PUBLIC cxx_std_20)

find_package(fmt REQUIRED)
target_link_libraries(Jengine_lib PRIVATE fmt::fmt)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
add_dependencies(Jengine_lib OpenGL::OpenGL)
target_link_libraries(Jengine_lib PRIVATE OpenGL::OpenGL)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(Jengine_lib PRIVATE glfw)

find_package(glm CONFIG REQUIRED)
target_link_libraries(Jengine_lib PRIVATE glm::glm)

# ---- Declare executable ----

add_executable(Jengine_exe src/main.cpp)
add_executable(Jengine::exe ALIAS Jengine_exe)

set_property(TARGET Jengine_exe PROPERTY OUTPUT_NAME Jengine)

target_compile_features(Jengine_exe PRIVATE cxx_std_20)

target_link_libraries(Jengine_exe PRIVATE Jengine_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT Jengine_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of Jengine"
  )
endif()

include(cmake/dev-mode.cmake)
