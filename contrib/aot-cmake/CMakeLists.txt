set(AOT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../aot)

add_custom_target(aot_bundle
  ALL COMMAND cd ${AOT_SOURCE_DIR} &&
  RML_PCRE_INCUDE=${CMAKE_CURRENT_SOURCE_DIR}/..
  RML_PCRE_LIB=${CMAKE_CURRENT_BINARY_DIR}
  bash -c './build-linux.sh')
