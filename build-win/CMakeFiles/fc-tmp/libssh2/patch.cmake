cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

message(VERBOSE "Executing patch step for libssh2")

block(SCOPE_FOR VARIABLES)

execute_process(
  WORKING_DIRECTORY "/home/amo999/Projects/C++/Project_RED/build-win/_deps/libssh2-src"
  COMMAND_ERROR_IS_FATAL LAST
  COMMAND  [====[/usr/bin/cmake]====] [====[-DLIBSSH2_DIR=/home/amo999/Projects/C++/Project_RED/build-win/_deps/libssh2-src]====] [====[-DMODULES_DIR=/home/amo999/Projects/C++/Project_RED/libs/SFML/src/SFML/Network/../../../cmake/Modules]====] [====[-P]====] [====[/home/amo999/Projects/C++/Project_RED/libs/SFML/tools/libssh2/PatchLibssh2.cmake]====]
)

endblock()
