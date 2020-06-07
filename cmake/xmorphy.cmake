find_package(ICU COMPONENTS i18n uc data REQUIRED)

set (Xmorphy_LIBRARY Xmorphy ${ICU_LIBRARIES})
set (Xmorphy_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/contrib/Xmorphy/src")

message (STATUS "Using Xmorphy: ${Xmorphy_INCLUDE_DIR} : ${Xmorphy_LIBRARY}")
