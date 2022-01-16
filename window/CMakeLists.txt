cmake_minimum_required (VERSION 3.15)

project(window)

set(CMAKE_CXX_STANDARD 17)

FILE(GLOB src_file ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

set(SOURCE main.cpp ${src_file})
set(HEADER )

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADER})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

set (LIBS SDL2 SDL2_image SDL2_ttf)

if (WIN32)
    add_definitions(-DUNICODE)

    if (MSVC_VERSION GREATER_EQUAL "1900")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
        if (_cpp_latest_flag_supported)
            add_compile_options("/std:c++latest")
        endif()
    endif()
    message("platform is win32")
	set(TARGET_CL_BIT x86)
	if (CMAKE_CL_64)
	    set(TARGET_CL_BIT x64)
	endif() # TARGET_CL_BIT
	

	function(add_win_lib libname)
	    set(${libname}_LIBDIR_PREFIX "/${libname}/lib/${TARGET_CL_BIT}")
	    set(${libname}_INCLUDE_PREFIX "/${libname}/include")
	    file(GLOB ${libname}_RUNTIME_DLL "${CMAKE_CURRENT_SOURCE_DIR}${${libname}_LIBDIR_PREFIX}/*.dll")
	    file(GLOB ${libname}_BUILD_LIB "${CMAKE_CURRENT_SOURCE_DIR}${${libname}_LIBDIR_PREFIX}/*.lib")
	
	    set(${libname}_LIBS)
	    foreach(file_path ${${libname}_BUILD_LIB})
	        string(REGEX REPLACE ".+/(.+)\\..*" "\\1" file_name ${file_path})
	        set(${libname}_LIBS ${${libname}_LIBS} ${file_name})
            endforeach(file_path)

            message("add link dir: ${CMAKE_CURRENT_SOURCE_DIR}${${libname}_LIBDIR_PREFIX}")
            target_link_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}${${libname}_LIBDIR_PREFIX}")
	    target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}${${libname}_INCLUDE_PREFIX}")
	
	    file(COPY ${${libname}_RUNTIME_DLL}
	        DESTINATION  ${CMAKE_CURRENT_BINARY_DIR})
	
	    target_link_libraries(${PROJECT_NAME} PUBLIC ${${libname}_LIBS})
	endfunction(add_wind_lib)

	foreach(libname ${LIBS})
		add_win_lib(${libname})
	endforeach(libname)
endif() #WIN32

if (UNIX)
	set (LIBS sdl2 SDL2_image)
	foreach(libname ${LIBS})
		#find_package(${libname})
		#if(${libname}_FOUND)
		#	target_include_directories(${PROJECT} PRIVATE ${${libname}_INCLUDE_DIR})
    	#	target_link_libraries(${PROJECT} ${${libname}_LIBRARY})
		#else(${libname}_FOUND)
    	#	message(FATAL_ERROR "${libname} library not found")
		#endif(${libname}_FOUND)
		find_package(PkgConfig)
		#string(TOLOWER ${libname} LIB_NAME)
		pkg_search_module(${libname} REQUIRED ${libname})

		message("add ${PROJECT_NAME} ${${libname}_INCLUDE_DIRS})")

		target_include_directories(${PROJECT_NAME} PUBLIC ${${libname}_INCLUDE_DIRS})
		target_link_libraries(${PROJECT_NAME} PUBLIC ${${libname}_LIBRARIES})
	endforeach(libname)
endif() # UNIX
