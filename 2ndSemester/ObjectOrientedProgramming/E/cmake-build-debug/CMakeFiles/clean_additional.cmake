# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\e_retake_913_Iaguta_Alen_Mihael_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\e_retake_913_Iaguta_Alen_Mihael_autogen.dir\\ParseCache.txt"
  "e_retake_913_Iaguta_Alen_Mihael_autogen"
  )
endif()
