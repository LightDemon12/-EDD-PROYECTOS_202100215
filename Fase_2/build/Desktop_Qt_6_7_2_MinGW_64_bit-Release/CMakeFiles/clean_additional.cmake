# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\Fase_2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Fase_2_autogen.dir\\ParseCache.txt"
  "Fase_2_autogen"
  )
endif()