set(target Client)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(ClientLib  ${CMAKE_CURRENT_SOURCE_DIR}/src/Client.cpp)
add_executable(${target} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${target} boost_system boost_thread ssl crypto pthread ClientLib)