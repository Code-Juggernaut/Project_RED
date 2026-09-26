cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

message(VERBOSE "Executing patch step for mbedtls")

block(SCOPE_FOR VARIABLES)

execute_process(
  WORKING_DIRECTORY "/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src"
  COMMAND_ERROR_IS_FATAL LAST
  COMMAND  [====[/usr/bin/cmake]====] [====[-DMBEDTLS_DIR=/home/amo999/Projects/C++/Project_RED/build-win/_deps/mbedtls-src]====] [====[-P]====] [====[/home/amo999/Projects/C++/Project_RED/libs/SFML/tools/mbedtls/PatchMbedTLS.cmake]====]
)

endblock()
