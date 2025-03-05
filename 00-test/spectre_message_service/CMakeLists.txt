cmake_minimum_required(VERSION 3.5)

# Define library. Only source files here!
project(libspectre_message_service VERSION 0.1 LANGUAGES C)

add_executable(application
    src/main.c
)

target_link_libraries(application
    utils
)

add_library(spectre_message_service
    src/message_service.c
)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(spectre_message_service PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src
)

# If we have compiler requirements for this library, list them
# here
target_compile_features(spectre_message_service
    PUBLIC cxx_auto_type
    PRIVATE cxx_variadic_templates
)

# Depend on a library that we defined in the top-level file
target_link_libraries(spectre_message_service
    utils
)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS spectre_message_service EXPORT MyLibraryConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
# install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT MyLibraryConfig DESTINATION share/MyLibrary/cmake)

# This makes the project importable from the build directory
export(TARGETS spectre_message_service FILE MyLibraryConfig.cmake)

# Every library has unit tests, of course
# add_executable(testlib
#     test/test_spectre_message_service.cpp
# )

# target_link_libraries(testlib
#     spectre_message_service
# )

# add_test(testlib testlib)