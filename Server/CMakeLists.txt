set(target Server)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(ServerLib  ${CMAKE_CURRENT_SOURCE_DIR}/src/Server.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/Session.cpp)
add_executable(${target} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${target} boost_system boost_thread ssl crypto pthread ServerLib)