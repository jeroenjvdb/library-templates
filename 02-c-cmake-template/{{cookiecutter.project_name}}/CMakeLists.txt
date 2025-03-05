# Define library. Only source files here!
project(lib{{cookiecutter.project_name}} VERSION 0.1 LANGUAGES C)

add_library({{cookiecutter.project_name}}
    src/{{cookiecutter.module_name}}.c
)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories({{cookiecutter.project_name}} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src
)

# If we have compiler requirements for this library, list them
# here
target_compile_features({{cookiecutter.project_name}}
    PUBLIC cxx_auto_type
    PRIVATE cxx_variadic_templates
)

# Depend on a library that we defined in the top-level file
target_link_libraries({{cookiecutter.project_name}}
)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS {{cookiecutter.project_name}} EXPORT MyLibraryConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
# install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT MyLibraryConfig DESTINATION share/MyLibrary/cmake)

# This makes the project importable from the build directory
export(TARGETS {{cookiecutter.project_name}} FILE MyLibraryConfig.cmake)

# Every library has unit tests, of course
add_executable(test{{cookiecutter.project_name}}
    test/test_{{cookiecutter.module_name}}.cpp
)

target_link_libraries(test{{cookiecutter.project_name}}
    {{cookiecutter.project_name}}
)

add_test(test{{cookiecutter.project_name}} test{{cookiecutter.project_name}})