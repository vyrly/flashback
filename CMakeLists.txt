cmake_minimum_required(VERSION 2.8)
PROJECT (flashback)

# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(test "Build all tests." OFF) # Makes boolean 'test' available.

find_package(OpenCV REQUIRED) # Required for image manipulations

if (UNIX)
  find_package(X11 REQUIRED) # Required for taking screenshot on linux
endif (UNIX)

set(CMAKE_CXX_FLAGS "-std=c++14 -g3 -O0")

set( NAME_SRC
    src/flashback.cpp
    src/Screenshot.cpp
    src/ScreenshotManager.cpp
    external/xhklib/xhklib.c
)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/external/easylogging++)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable( flashback ${NAME_SRC} ${NAME_HEADERS} )

target_link_libraries( flashback ${OpenCV_LIBS} ${X11_LIBRARIES})

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
