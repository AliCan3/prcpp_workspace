cmake_minimum_required(VERSION 3.10)

include(cpplint)

# project settings
set(project_name example)
project(${project_name})

# collect sources
file(GLOB_RECURSE src_lib src/*.cpp)
file(GLOB_RECURSE hdr_lib src/*.h*)
file(GLOB_RECURSE src_test unittest/*.cpp)
file(GLOB_RECURSE hdr_test unittest/*.h*)
file(GLOB_RECURSE src_main src/main.cpp)
list(REMOVE_ITEM src_lib ${src_main})

# internal library target
set(${project_name}_lib)
add_library(${project_name}_lib STATIC ${src_lib})
target_include_directories(${project_name}_lib PUBLIC src)

# main app target
add_executable(${project_name}_app ${src_main})
target_link_libraries(${project_name}_app PRIVATE ${project_name}_lib)

# unit unittest target
add_executable(${project_name}_test ${src_test})
target_link_libraries(${project_name}_test PRIVATE ${project_name}_lib)

# style checks
setup_cpplint(${project_name}_lib ${src_lib} ${hdr_lib})
setup_cpplint(${project_name}_app ${src_main} )
setup_cpplint(${project_name}_test ${src_test} ${hdr_test})

# set compiler flags
target_compile_options(${project_name}_lib PRIVATE ${cxxflags})
target_compile_options(${project_name}_app PRIVATE ${cxxflags})
target_compile_options(${project_name}_test PRIVATE ${cxxflags})
