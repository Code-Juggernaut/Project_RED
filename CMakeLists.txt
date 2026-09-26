CMAKE_MINIMUM_REQUIRED(VERSION 3.17)
project(Project_RED)

#set(CMAKE_SYSTEM_NAME Windows)
#set(CMAKE_C_COMPILER /usr/bin/x86_64-w64-mingw32-gcc)
#set(CMAKE_CXX_COMPILER /usr/bin/x86_64-w64-mingw32-g++)



#set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libs" FORCE)
#set(SFML_BUILD_STATIC_LIBS OFF CACHE BOOL "" FORCE)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(libs/SFML build-sfml)
add_subdirectory(libs/json json)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/json/single_include)

add_library(generic OBJECT libs/UI/generic.cpp)
target_link_libraries(generic PRIVATE sfml-graphics sfml-window sfml-system)
add_library(frontend OBJECT frontend/frontend.cpp)
target_link_libraries(frontend PRIVATE sfml-graphics sfml-window sfml-system)
add_library(functional OBJECT functional/functional.cpp)
target_link_libraries(functional PRIVATE sfml-network)
#find_package(SFML 3.0 REQUIRED COMPONENTS  Graphics Window System)


target_link_libraries(functional PRIVATE nlohmann_json::nlohmann_json)


add_executable(sfml-app main.cpp)

#target_link_libraries(sfml-app PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(sfml-app PRIVATE sfml-graphics sfml-system sfml-window)
target_link_libraries(sfml-app PRIVATE sfml-network)
target_link_libraries(sfml-app PRIVATE generic)
target_link_libraries(sfml-app PRIVATE functional)
target_link_libraries(sfml-app PRIVATE frontend)



#if(WIN32)
#    target_link_libraries(sfml-app PRIVATE opengl32 gdi32 winmm ws2_32 ole32)
#    target_link_options(sfml-app PRIVATE 
#    -static-libgcc 
#    -static-libstdc++
#    -Wl,-Bstatic -lwinpthread -Wl,-Bdynamic
#    )
#ndif()
