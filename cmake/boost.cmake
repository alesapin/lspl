set (Boost_SYSTEM_LIBRARY boost_system_internal)
set (Boost_INCLUDE_DIRS)

file (GLOB Boost_INCLUDE_DIRS_ "${CMAKE_SOURCE_DIR}/contrib/boost/*/include")
list (APPEND Boost_INCLUDE_DIRS ${Boost_INCLUDE_DIRS_})


message (STATUS "Using Boost: ${Boost_INCLUDE_DIRS} : ${Boost_SYSTEM_LIBRARY}")
