cmake_minimum_required(VERSION 2.8)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

PROJECT (flashback)

# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(test "Build all tests." OFF) # Makes boolean 'test' available.

find_package(OpenCV REQUIRED) # Required for image processing
find_package(SFML REQUIRED) # Required for image manipulations and displaying

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED graphics window system)


if (UNIX)
  find_package(X11 REQUIRED) # Required for taking screenshot on linux
endif (UNIX)

set(CMAKE_CXX_FLAGS "-std=c++14 -g3 -O0")

set( NAME_SRC
    src/flashback.cpp
    src/Screenshot.cpp
    src/ScreenshotManager.cpp
    external/xhklib/xhklib.c # ???needed???
)


if(SFML_FOUND)
  # !!!Use this!!!
endif()

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include ${SFML_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/external/easylogging++) #???easylogging???

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable( flashback ${NAME_SRC} ${NAME_HEADERS} )

target_link_libraries( flashback ${SFML_LIBRARIES} ${OpenCV_LIBS} ${X11_LIBRARIES})

# Testing ######################################################################
# Based on GTest framework

if (test)
  # Enable ExternalProject CMake module
  include(ExternalProject)

  # Download and install GoogleTest
  ExternalProject_Add(
      gtest
      URL https://github.com/google/googletest/archive/release-1.7.0.zip
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
      # Disable install step
      INSTALL_COMMAND ""
  )

  # Create a libgtest target to be used as a dependency by test programs
  add_library(libgtest IMPORTED STATIC GLOBAL)
  add_dependencies(libgtest gtest)

  # Set gtest properties
  ExternalProject_Get_Property(gtest source_dir binary_dir)
  set_target_properties(libgtest PROPERTIES
      "IMPORTED_LOCATION" "${binary_dir}/libgtest.a"
      "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
  #    "INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
  )
  # I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
  include_directories("${source_dir}/include")

#  # This adds another subdirectory, which has 'project(gtest)'.
#  add_subdirectory(lib/gtest-1.6.0)

  set( TEST_SRC
      test/test_Screenshot.cpp
  )

  enable_testing()

#  # Include the gtest library. gtest_SOURCE_DIR is available due to
#  # 'project(gtest)' above.
#  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

  add_executable(runUnitTests ${TEST_SRC})

  # Standard linking to gtest stuff.
  target_link_libraries(runUnitTests libgtest gtest_main)

#  # Extra linking for the project.
#  target_link_libraries(runUnitTests project1_lib)

  # This is so you can do 'make test'
  add_test(NAME test COMMAND runUnitTests)

endif()
