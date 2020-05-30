add_definitions(-Wno-unused-variable -Wno-deprecated-declarations)

set(SYSTEM_LIBRARY_DIR ${CMAKE_CURRENT_LIST_DIR}/../boost/system)

set(boost_system_sources ${SYSTEM_LIBRARY_DIR}/src/error_code.cpp)
set(boost_system_headers ${SYSTEM_LIBRARY_DIR}/include)

add_library(boost_system_internal ${boost_system_sources})
target_include_directories(boost_system_internal SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})
