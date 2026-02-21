# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\bankingsystemqt_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\bankingsystemqt_autogen.dir\\ParseCache.txt"
  "bankingsystemqt_autogen"
  )
endif()
