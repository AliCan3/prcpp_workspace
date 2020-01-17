cmake_minimum_required(VERSION 3.10)

include(cpplint)


function(prcpp_code project_name)
    file(GLOB_RECURSE src_lib src/*.cpp)
    list(LENGTH src_lib src_count)
    file(GLOB_RECURSE src_main src/main.cpp)
    list(LENGTH src_main main_count)
    file(GLOB_RECURSE src_test unittest/*.cpp)
    list(LENGTH src_test test_count)

    if((test_count GREATER 0) AND (src_count GREATER 1) AND (main_count EQUAL 1))
        prcpp_code_lib(${project_name})
    elseif((test_count GREATER 0) AND (main_count EQUAL 1))
        prcpp_code_app_test(${project_name})
    elseif((test_count GREATER 0) AND (main_count EQUAL 0))
        prcpp_code_test(${project_name})
    elseif((test_count EQUAL 0) AND (main_count EQUAL 1))
        prcpp_code_app(${project_name})
    else()
        message(FATAL_ERROR "unknown type of prcpp code project")
    endif()
endfunction()


function(prcpp_code_app project_name)
    project(${project_name})
    message(STATUS "${project_name} is prcpp_code_app")

    # collect sources
    file(GLOB_RECURSE src_app src/*.cpp)
    file(GLOB_RECURSE hdr_app src/*.h*)

    add_executable(${project_name}_app ${src_app})
    setup_cpplint(${project_name}_app ${src_app} ${hdr_app})
    target_compile_options(${project_name}_app PRIVATE ${cxxflags})
endfunction()


function(prcpp_code_test project_name)
    project(${project_name})
    message(STATUS "${project_name} is prcpp_code_test")

    # collect sources
    file(GLOB_RECURSE src_lib src/*.cpp)
    file(GLOB_RECURSE hdr_lib src/*.h*)
    file(GLOB_RECURSE src_test unittest/*.cpp)
    file(GLOB_RECURSE hdr_test unittest/*.h*)

    add_executable(${project_name}_test ${src_lib} ${src_test})
    target_include_directories(${project_name}_test PUBLIC src)
    setup_cpplint(${project_name}_test ${src_lib} ${hdr_lib} ${src_test} ${hdr_test})
    target_compile_options(${project_name}_test PRIVATE ${cxxflags})
    add_test(${project_name} ${project_name}_test)
endfunction()


function(prcpp_code_app_test project_name)
    project(${project_name})
    message(STATUS "${project_name} is prcpp_code_app_test")

    # collect sources
    file(GLOB_RECURSE hdr_lib src/*.h*)
    file(GLOB_RECURSE src_test unittest/*.cpp)
    file(GLOB_RECURSE hdr_test unittest/*.h*)
    file(GLOB_RECURSE src_main src/main.cpp)

    # main app target
    add_executable(${project_name}_app ${src_main})

    # unittest target
    add_executable(${project_name}_test ${src_test})
    target_include_directories(${project_name}_test PUBLIC src)
    add_test(${project_name} ${project_name}_test)

    # style checks
    setup_cpplint(${project_name}_app ${src_main} ${hdr_lib})
    setup_cpplint(${project_name}_test ${hdr_lib} ${src_test} ${hdr_test})

    # set compiler flags
    target_compile_options(${project_name}_app PRIVATE ${cxxflags})
    target_compile_options(${project_name}_test PRIVATE ${cxxflags})
endfunction()


function(prcpp_code_lib project_name)
    project(${project_name})
    message(STATUS "${project_name} is prcpp_code_lib")

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

    # unittest target
    add_executable(${project_name}_test ${src_test})
    target_link_libraries(${project_name}_test PRIVATE ${project_name}_lib)
    add_test(${project_name} ${project_name}_test)

    # style checks
    setup_cpplint(${project_name}_lib ${src_lib} ${hdr_lib})
    setup_cpplint(${project_name}_app ${src_main})
    setup_cpplint(${project_name}_test ${src_test} ${hdr_test})

    # set compiler flags
    target_compile_options(${project_name}_lib PRIVATE ${cxxflags})
    target_compile_options(${project_name}_app PRIVATE ${cxxflags})
    target_compile_options(${project_name}_test PRIVATE ${cxxflags})
endfunction()
