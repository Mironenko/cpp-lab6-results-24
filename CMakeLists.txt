project (lab6)

set(SRC_LIST 
    sources/main.cpp 
    sources/al-6.h 
    sources/Exceptions.h 
    sources/Q.cpp 
    sources/Q.h 
    sources/QMatrix.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

add_executable(${PROJECT_NAME} ${SRC_LIST})