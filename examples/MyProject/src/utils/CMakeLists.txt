# Define library. Only source files here!
project(libutils VERSION 0.1 LANGUAGES C)

add_library(utils
    src/logger.c
)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(utils PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src
)

# If we have compiler requirements for this library, list them
# here
target_compile_features(utils
    PUBLIC cxx_auto_type
    PRIVATE cxx_variadic_templates
)

# Depend on a library that we defined in the top-level file
target_link_libraries(utils
)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS utils EXPORT MyLibraryConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
# install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT MyLibraryConfig DESTINATION share/MyLibrary/cmake)

# This makes the project importable from the build directory
export(TARGETS utils FILE MyLibraryConfig.cmake)

# Every library has unit tests, of course
add_executable(testutils
    test/test_logger.cpp
)

target_link_libraries(testutils
    utils
)

add_test(testutils testutils)