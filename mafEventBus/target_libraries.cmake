#
# See CMake/mafMacroGetTargetLibraries.cmake
# 
# This file should list the libraries required to build the current MAF module.
# 

SET(target_libraries
  ${MAF_BASE_LIBRARIES}
  ${QTSOAP_LIBRARY}
  ${QXMLRPC_LIBRARY}
  )
