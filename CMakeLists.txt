cmake_minimum_required(VERSION 3.8)
project(libUtils LANGUAGES CXX)

#do not append lib to library name
set(CMAKE_STATIC_LIBRARY_PREFIX "")

set(CMAKE_CXX_STANDARD 14 )

set(SOURCE_FILES MutexWithOwnersip.h)
add_library(libUtils ${SOURCE_FILES})

set_target_properties(libUtils PROPERTIES LINKER_LANGUAGE CXX)

file(GLOB HEADERS *.h)
install(FILES ${HEADERS} DESTINATION ~/source/pkg/include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} DESTINATION ~/source/pkg/lib)

add_custom_target(install_${PROJECT_NAME}
        $(MAKE) install
        DEPENDS ${PROJECT_NAME}
        COMMENT "Installing ${PROJECT_NAME}")

####### Unit Tests ##############
add_subdirectory(GTest)