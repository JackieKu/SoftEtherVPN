cmake_minimum_required(VERSION 2.8.9)
project(SoftEtherVPN)

function(SimpleFindLibrary lib)
	include(CMakeParseArguments)
	cmake_parse_arguments("o" "REQUIRED" "" "" ${ARGN})
	if (o_REQUIRED)
		set(errorLevel FATAL_ERROR)
	else()
		set(errorLevel STATUS)
	endif()

	string(TOUPPER "${lib}" LIB)
	find_library("${LIB}_FOUND" ${lib})
	if(${LIB}_FOUND)
		set("${LIB}_FOUND" "${${LIB}_FOUND}" PARENT_SCOPE)
		set("${LIB}_LIBRARIES" "${${LIB}_FOUND}" PARENT_SCOPE)
		message(STATUS "Found ${lib}: ${${LIB}_FOUND}")
	else()
		set("${LIB}_FOUND" "${lib}-NOTFOUND" PARENT_SCOPE)
		message(${errorLevel} "Couldn't find ${lib}")
	endif()
endfunction()

find_package(OpenSSL REQUIRED)
find_package(Curses REQUIRED)
find_package(ZLIB REQUIRED)
SimpleFindLibrary(readline REQUIRED)

add_subdirectory(Mayaqua/3rdparty/cpu_features EXCLUDE_FROM_ALL)

math(EXPR BITS "${CMAKE_SIZEOF_VOID_P} * 8")

file(GLOB HEADERS_MAYAQUA "Mayaqua/*.h")
file(GLOB SOURCES_MAYAQUA "Mayaqua/*.c")

file(GLOB HEADERS_CEDAR "Cedar/*.h")
file(GLOB SOURCES_CEDAR "Cedar/*.c")

set(CONIO_LIBRARIES ${READLINE_LIBRARIES})
set(CORE_LINK_LIBRARIES ${OPENSSL_LIBRARIES} ${ZLIB_LIBRARIES})

add_definitions(-DVPN_SPEED -DCPU_${BITS} -D_REENTRANT -DREENTRANT -D_THREAD_SAFE -D_THREADSAFE -DTHREAD_SAFE -DTHREADSAFE -D_FILE_OFFSET_BITS=64)
if(UNIX)
	add_definitions(-DUNIX)
endif()
if(APPLE)
	add_definitions(-DUNIX_MACOS)

	SimpleFindLibrary(iconv REQUIRED)
	list(APPEND CORE_LINK_LIBRARIES ${ICONV_LIBRARIES})

	SimpleFindLibrary(pcap)
	if(PCAP_FOUND)
		list(APPEND CORE_LINK_LIBRARIES ${PCAP_LIBRARIES})
		add_definitions(-DBRIDGE_PCAP)
	else()
		message(WARNING "Could not found pcap. Bridging function may not work.")
	endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	add_definitions(-DUNIX_LINUX)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
else()
	message(FATAL_ERROR "Building for ${CMAKE_SYSTEM_NAME} is not implemented yet.")
endif()

include_directories(. Cedar Mayaqua ${OPENSSL_INCLUDE_DIR} ${ZLIB_INCLUDE_DIRS} ${CURSES_INCLUDE_DIR} Mayaqua/3rdparty/cpu_features/include)

add_library(softether SHARED ${SOURCES_MAYAQUA} ${SOURCES_CEDAR})
target_link_libraries(softether cpu_features ${CORE_LINK_LIBRARIES} ${CONIO_LIBRARIES})

function(add_exe_ _exe _src)
	add_executable(${_exe} ${_exe}/${_src}.c)
	target_link_libraries(${_exe} softether)
endfunction()

function(add_exe _exe)
	add_exe_(${_exe} ${_exe})
endfunction()

add_exe(vpncmd)
add_exe(vpnserver)
add_exe_(vpnclient vpncsvc)
add_exe(vpnbridge)
add_exe(hamcorebuilder)

include(GNUInstallDirs)
set(MAIN_DIR ${CMAKE_INSTALL_LIBEXECDIR}/softether-vpn)

install(
	TARGETS softether vpncmd vpnserver vpnclient vpnbridge
	RUNTIME DESTINATION ${MAIN_DIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

add_custom_command(OUTPUT hamcore.se2
	COMMAND hamcorebuilder "${CMAKE_CURRENT_SOURCE_DIR}/bin/hamcore/" hamcore.se2
	MAIN_DEPENDENCY hamcorebuilder
)
add_custom_target(hamcore ALL DEPENDS hamcore.se2)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/hamcore.se2" DESTINATION ${MAIN_DIR})
