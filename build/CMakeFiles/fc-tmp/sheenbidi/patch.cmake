cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

message(VERBOSE "Executing patch step for sheenbidi")

block(SCOPE_FOR VARIABLES)

execute_process(
  WORKING_DIRECTORY "/home/amo999/Projects/C++/Project_RED/build/_deps/sheenbidi-src"
  COMMAND_ERROR_IS_FATAL LAST
  COMMAND  [====[/usr/bin/cmake]====] [====[-DSHEENBIDI_DIR=/home/amo999/Projects/C++/Project_RED/build/_deps/sheenbidi-src]====] [====[-P]====] [====[/home/amo999/Projects/C++/Project_RED/libs/SFML/tools/sheenbidi/PatchSheenBidi.cmake]====]
)

endblock()
