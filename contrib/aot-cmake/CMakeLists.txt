set(AOT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../aot)

add_custom_target(aot_bundle
  COMMAND cd ${AOT_SOURCE_DIR} && bash -c './build-linux.sh'
  BYPRODUCTS  ${CMAKE_SOURCE_DIR}/contrib/aot/Source/GraphanLib/libGraphanrst.a
  ${CMAKE_SOURCE_DIR}/contrib/aot/Source/LemmatizerLib/libLemmatizerrst.a
  ${CMAKE_SOURCE_DIR}/contrib/aot/Source/StructDictLib/libStructDictrst.a
  ${CMAKE_SOURCE_DIR}/contrib/aot/Source/MorphWizardLib/libMorphWizardrst.a
  ${CMAKE_SOURCE_DIR}/contrib/aot/Source/AgramtabLib/libAgramtabrst.a)
