# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\IP_Info_App_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\IP_Info_App_autogen.dir\\ParseCache.txt"
  "IP_Info_App_autogen"
  )
endif()
