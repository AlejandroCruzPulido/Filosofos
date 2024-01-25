# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\filosofos_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\filosofos_autogen.dir\\ParseCache.txt"
  "filosofos_autogen"
  )
endif()
