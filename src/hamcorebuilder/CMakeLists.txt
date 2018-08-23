add_executable(hamcorebuilder hamcorebuilder.c)

set_target_properties(hamcorebuilder
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tmp"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tmp"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tmp"
)

target_link_libraries(hamcorebuilder cedar mayaqua)
