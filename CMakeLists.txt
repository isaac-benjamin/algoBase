cmake_minimum_required(VERSION 3.23)

project(numPaths CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /std:c11") 
set(CMAKE_BUILD_TYPE Debug)

add_executable(numPaths)

include(FetchContent)
FetchContent_Declare(
  cpptrace
  GIT_REPOSITORY https://github.com/jeremy-rifkin/cpptrace.git
  GIT_TAG        v1.0.4 # <HASH or TAG>
)
FetchContent_MakeAvailable(cpptrace)
target_link_libraries(numPaths PRIVATE cpptrace::cpptrace pthread)

target_sources(numPaths 
  PRIVATE
   numPaths.cpp)

# target_compile_options(xyz PRIVATE -g -rdynamic)

# Needed for shared library builds on windows:  copy cpptrace.dll to the same directory as the
# executable for your_target
if(WIN32)
  add_custom_command(
    TARGET numPaths POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:cpptrace::cpptrace>
    $<TARGET_FILE_DIR:numPaths>
  )
endif()