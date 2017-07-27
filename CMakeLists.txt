cmake_minimum_required(VERSION 3.8)
project(libUtils)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES MutexWithOwnersip.h library.cpp.cpp)
add_library(libUtils ${SOURCE_FILES})

file(GLOB HEADERS *.h)
install(FILES ${HEADERS} DESTINATION ~/source/pkg/include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} DESTINATION ~/source/pkg/lib)

add_custom_target(install_${PROJECT_NAME}
        $(MAKE) install
        DEPENDS ${PROJECT_NAME}
        COMMENT "Installing ${PROJECT_NAME}")

####### Unit Tests ##############
set (GTEST_ROOT /usr)
find_package(GTest REQUIRED)
set(UnitTest_SOURCE_FILES GTest/Main.cpp GTest/MutexWithOwnershipTest.cpp)
add_executable(UnitTest ${UnitTest_SOURCE_FILES})
target_link_libraries(UnitTest GTest::GTest GTest::Main libUtils)
