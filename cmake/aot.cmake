set(AOT_LIBRARIES
  ${CMAKE_SOURCE_DIR}/contrib/aot/Source/GraphanLib/libGraphanrst.a
  ${CMAKE_SOURCE_DIR}/contrib/aot/Source/LemmatizerLib/libLemmatizerrst.a
  ${CMAKE_SOURCE_DIR}/contrib/aot/Source/StructDictLib/libStructDictrst.a
  ${CMAKE_SOURCE_DIR}/contrib/aot/Source/MorphWizardLib/libMorphWizardrst.a
  ${CMAKE_SOURCE_DIR}/contrib/aot/Source/AgramtabLib/libAgramtabrst.a
)
set(AOT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/contrib/aot/Source)

message (STATUS "Using AOT=${AOT_INCLUDE_DIR} : ${AOT_LIBRARIES}")
