cmake_minimum_required(VERSION 3.10)

project(NovaCore LANGUAGES CXX)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)

add_library(NovaCore STATIC ${SOURCES})

add_library(Nova::Core ALIAS NovaCore)

find_package(fmt CONFIG REQUIRED)
find_package(cglm CONFIG REQUIRED)

target_include_directories(NovaCore
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_compile_features(NovaCore PUBLIC cxx_std_20)

target_link_libraries(NovaCore
    PUBLIC
        fmt::fmt
        Nova::Logger
        cglm::cglm
)

target_compile_definitions(NovaCore
    PRIVATE
        $<$<CONFIG:Debug>:BUILD_DEBUG>
        $<$<CONFIG:Release>:BUILD_RELEASE>
)