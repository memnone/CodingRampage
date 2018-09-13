###############################################################################
#
# CodingRampage Core/Sorting library
#
###############################################################################

if(RAMPAGE_BUILD_CORE)
	SET(PACKAGE_DIR "${PACKAGE_CORE}/Sorting")

	#FILE(GLOB_RECURSE PACKAGE_SOURCES "${PACKAGE_DIR}/src/*.cpp")
	FILE(GLOB_RECURSE PACKAGE_HEADERS "${PACKAGE_DIR}/include/*.h")

	if(RAMPAGE_DYNAMIC_LIBS)
		#ADD_LIBRARY(RampageSorting SHARED ${PACKAGE_SOURCES} ${PACKAGE_HEADERS})
		ADD_LIBRARY(RampageSorting SHARED ${PACKAGE_HEADERS})				
		TARGET_COMPILE_OPTIONS(RampageSorting PUBLIC ${CMAKE_DLL_EXPORT_FLAGS})
	else(RAMPAGE_DYNAMIC_LIBS)
		#ADD_LIBRARY(RampageSorting STATIC ${PACKAGE_SOURCES} ${PACKAGE_HEADERS})
		ADD_LIBRARY(RampageSorting STATIC ${PACKAGE_HEADERS})
	endif(RAMPAGE_DYNAMIC_LIBS)

	TARGET_LINK_LIBRARIES(RampageSorting RampageDefs RampageSys)
	
	TARGET_INCLUDE_DIRECTORIES(RampageSorting PUBLIC ${PACKAGE_DIR}/include)
	
	if (CPACK_BUILD_CORE)
		if(RAMPAGE_DYNAMIC_LIBS)
			if (WIN32)
				INSTALL(TARGETS RampageSorting RUNTIME DESTINATION bin COMPONENT core_libs)
			elseif (UNIX)
				INSTALL(TARGETS RampageSorting LIBRARY DESTINATION bin COMPONENT core_libs)
			endif()
		else(RAMPAGE_DYNAMIC_LIBS)
			INSTALL(TARGETS RampageSorting ARCHIVE DESTINATION lib COMPONENT core_libs)
		endif(RAMPAGE_DYNAMIC_LIBS)
		INSTALL(FILES ${PACKAGE_HEADERS} DESTINATION include/Rampage/Sorting/ COMPONENT core_headers)
	endif (CPACK_BUILD_CORE)
	
	SET_PROPERTY(TARGET RampageSorting PROPERTY PROJECT_LABEL "Sorting")
	SET_PROPERTY(TARGET RampageSorting PROPERTY FOLDER "Core")
	SOURCE_GROUP("Include Files" FILES ${PACKAGE_HEADERS})
endif(RAMPAGE_BUILD_CORE)
