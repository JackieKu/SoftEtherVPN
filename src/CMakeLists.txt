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

math(EXPR BITS "${CMAKE_SIZEOF_VOID_P} * 8")

set(HEADERS_MAYAQUA
Mayaqua/Cfg.h Mayaqua/cryptoki.h Mayaqua/Encrypt.h Mayaqua/FileIO.h Mayaqua/intelaes/iaesni.h Mayaqua/Internat.h Mayaqua/Kernel.h Mayaqua/Mayaqua.h Mayaqua/MayaType.h Mayaqua/Memory.h Mayaqua/Microsoft.h Mayaqua/Network.h Mayaqua/Object.h Mayaqua/OS.h Mayaqua/Pack.h Mayaqua/pkcs11.h Mayaqua/pkcs11f.h Mayaqua/pkcs11t.h Mayaqua/Secure.h Mayaqua/Str.h Mayaqua/Table.h Mayaqua/TcpIp.h Mayaqua/Tick64.h Mayaqua/Tracking.h Mayaqua/TunTap.h Mayaqua/Unix.h Mayaqua/Win32.h Mayaqua/zlib/zconf.h Mayaqua/zlib/zlib.h
)

set(HEADERS_CEDAR
Cedar/Account.h Cedar/Admin.h Cedar/AzureClient.h Cedar/AzureServer.h Cedar/Bridge.h Cedar/BridgeUnix.h Cedar/BridgeWin32.h Cedar/Cedar.h Cedar/CedarPch.h Cedar/CedarType.h Cedar/Client.h Cedar/CM.h Cedar/CMInner.h Cedar/Command.h Cedar/Connection.h Cedar/Console.h Cedar/Database.h Cedar/DDNS.h Cedar/EM.h Cedar/EMInner.h Cedar/EtherLog.h Cedar/Hub.h Cedar/Interop_OpenVPN.h Cedar/Interop_SSTP.h Cedar/IPsec.h Cedar/IPsec_EtherIP.h Cedar/IPsec_IKE.h Cedar/IPsec_IkePacket.h Cedar/IPsec_IPC.h Cedar/IPsec_L2TP.h Cedar/IPsec_PPP.h Cedar/IPsec_Win7.h Cedar/IPsec_Win7Inner.h Cedar/Layer3.h Cedar/Link.h Cedar/Listener.h Cedar/Logging.h Cedar/Nat.h Cedar/NativeStack.h Cedar/netcfgn.h Cedar/netcfgx.h Cedar/NM.h Cedar/NMInner.h Cedar/NullLan.h Cedar/Protocol.h Cedar/Radius.h Cedar/Remote.h Cedar/Sam.h Cedar/SecureInfo.h Cedar/SecureNAT.h Cedar/SeLowUser.h Cedar/Server.h Cedar/Session.h Cedar/SM.h Cedar/SMInner.h Cedar/SW.h Cedar/SWInner.h Cedar/UdpAccel.h Cedar/UT.h Cedar/VG.h Cedar/Virtual.h Cedar/VLan.h Cedar/VLanUnix.h Cedar/VLanWin32.h Cedar/WaterMark.h Cedar/WebUI.h Cedar/Win32Com.h Cedar/winpcap/bittypes.h Cedar/winpcap/bucket_lookup.h Cedar/winpcap/count_packets.h Cedar/winpcap/Devioctl.h Cedar/winpcap/Gnuc.h Cedar/winpcap/ip6_misc.h Cedar/winpcap/memory_t.h Cedar/winpcap/normal_lookup.h Cedar/winpcap/Ntddndis.h Cedar/winpcap/Ntddpack.h Cedar/winpcap/Packet32.h Cedar/winpcap/pcap.h Cedar/winpcap/pcap-bpf.h Cedar/winpcap/pcap-int.h Cedar/winpcap/pcap-stdinc.h Cedar/winpcap/pthread.h Cedar/winpcap/remote-ext.h Cedar/winpcap/sched.h Cedar/winpcap/semaphore.h Cedar/winpcap/tcp_session.h Cedar/winpcap/time_calls.h Cedar/winpcap/tme.h Cedar/winpcap/Win32-Extensions.h Cedar/WinUi.h Cedar/Wpc.h
)

set(SOURCES_MAYAQUA
Mayaqua/Cfg.c Mayaqua/Encrypt.c Mayaqua/FileIO.c Mayaqua/Internat.c Mayaqua/Kernel.c Mayaqua/Mayaqua.c Mayaqua/Memory.c Mayaqua/Microsoft.c Mayaqua/Network.c Mayaqua/Object.c Mayaqua/OS.c Mayaqua/Pack.c Mayaqua/Secure.c Mayaqua/Str.c Mayaqua/Table.c Mayaqua/TcpIp.c Mayaqua/Tick64.c Mayaqua/Tracking.c Mayaqua/Unix.c Mayaqua/Win32.c
)

set(SOURCES_CEDAR
Cedar/Account.c Cedar/Admin.c Cedar/AzureClient.c Cedar/AzureServer.c Cedar/Bridge.c Cedar/BridgeUnix.c Cedar/BridgeWin32.c Cedar/Cedar.c Cedar/CedarPch.c Cedar/Client.c Cedar/CM.c Cedar/Command.c Cedar/Connection.c Cedar/Console.c Cedar/Database.c Cedar/DDNS.c Cedar/EM.c Cedar/EtherLog.c Cedar/Hub.c Cedar/Interop_OpenVPN.c Cedar/Interop_SSTP.c Cedar/IPsec.c Cedar/IPsec_EtherIP.c Cedar/IPsec_IKE.c Cedar/IPsec_IkePacket.c Cedar/IPsec_IPC.c Cedar/IPsec_L2TP.c Cedar/IPsec_PPP.c Cedar/IPsec_Win7.c Cedar/Layer3.c Cedar/Link.c Cedar/Listener.c Cedar/Logging.c Cedar/Nat.c Cedar/NativeStack.c Cedar/NM.c Cedar/NullLan.c Cedar/Protocol.c Cedar/Radius.c Cedar/Remote.c Cedar/Sam.c Cedar/SecureInfo.c Cedar/SecureNAT.c Cedar/SeLowUser.c Cedar/Server.c Cedar/Session.c Cedar/SM.c Cedar/SW.c Cedar/UdpAccel.c Cedar/UT.c Cedar/VG.c Cedar/Virtual.c Cedar/VLan.c Cedar/WaterMark.c Cedar/WebUI.c Cedar/WinUi.c Cedar/Wpc.c
)

set(HAMCORE_FILES
bin/hamcore/authors.txt bin/hamcore/backup_dir_readme.txt bin/hamcore/empty.config bin/hamcore/empty_sevpnclient.config bin/hamcore/eula.txt bin/hamcore/install_src.dat bin/hamcore/lang.config bin/hamcore/languages.txt bin/hamcore/languages_wine.txt bin/hamcore/legal.txt bin/hamcore/openvpn_readme.pdf bin/hamcore/openvpn_readme.txt bin/hamcore/openvpn_sample.ovpn bin/hamcore/root_certs.dat bin/hamcore/SOURCES_OF_BINARY_FILES.TXT bin/hamcore/strtable_cn.stb bin/hamcore/strtable_en.stb bin/hamcore/strtable_ja.stb bin/hamcore/vpnweb_sample_cn.htm bin/hamcore/vpnweb_sample_en.htm bin/hamcore/vpnweb_sample_ja.htm bin/hamcore/warning_cn.txt bin/hamcore/warning_en.txt bin/hamcore/warning_ja.txt bin/hamcore/webui/cryptcom.cgi bin/hamcore/webui/edituser.cgi bin/hamcore/webui/error.cgi bin/hamcore/webui/hub.cgi bin/hamcore/webui/license.cgi bin/hamcore/webui/listener.cgi bin/hamcore/webui/localbridge.cgi bin/hamcore/webui/login.cgi bin/hamcore/webui/newhub.cgi bin/hamcore/webui/redirect.cgi bin/hamcore/webui/securenat.cgi bin/hamcore/webui/server.cgi bin/hamcore/webui/session.cgi bin/hamcore/webui/user.cgi bin/hamcore/webui/webui.css
)

set(CONIO_LIBRARIES ${CURSES_LIBRARIES} ${READLINE_LIBRARIES})
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

include_directories(. Cedar Mayaqua ${OPENSSL_INCLUDE_DIR} ${ZLIB_INCLUDE_DIRS} ${CURSES_INCLUDE_DIR})

add_library(softether SHARED ${SOURCES_MAYAQUA} ${SOURCES_CEDAR})
target_link_libraries(softether ${CORE_LINK_LIBRARIES} ${CONIO_LIBRARIES})

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
