cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

message(VERBOSE "Executing patch step for freetype")

block(SCOPE_FOR VARIABLES)

execute_process(
  WORKING_DIRECTORY "/home/amo999/Projects/C++/Project_RED/build-win/_deps/freetype-src"
  COMMAND_ERROR_IS_FATAL LAST
  COMMAND  [====[/usr/bin/cmake]====] [====[-DFREETYPE_DIR=/home/amo999/Projects/C++/Project_RED/build-win/_deps/freetype-src]====] [====[-P]====] [====[/home/amo999/Projects/C++/Project_RED/libs/SFML/tools/freetype/PatchFreetype.cmake]====]
)

endblock()
