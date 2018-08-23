file(GLOB SOURCES_CEDAR "*.c")
file(GLOB HEADERS_CEDAR "*.h")

add_library(cedar STATIC ${SOURCES_CEDAR} ${HEADERS_CEDAR})

find_library(LIB_READLINE readline)

target_link_libraries(cedar ${LIB_READLINE})

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
  target_link_libraries(cedar pcap)
endif()
