cmake_minimum_required (VERSION 3.15)

project(log-demo)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE main.cpp logger.cpp)
set(HEADER logger.h)

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADER})


#target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
#target_include_directories(${PROJECT_NAME} PUBLIC "${JSONCPP_DIR}/include")

#target_link_libraries(${PROJECT_NAME} PUBLIC "jsoncpp_static.lib")
#target_link_libraries(${PROJECT_NAME} PUBLIC "wininet.lib" "Msi.lib")
