cmake_minimum_required(VERSION 3.10)
project(convexSet)
set(CMAKE_CXX_STANDARD 17 )

set(COMMON_FLAGS "-g")

set(CMAKE_CXX_FLAGS "${COMMON_FLAGS}")

set(SCIPLOT_DIR_1 ./sciplot/sciplot)
set(SCIPLOT_DIR ./sciplot)

# find_package (Eigen3  REQUIRED)

include_directories(
		include
 		${CMAKE_CURRENT_SOURCE_DIR}
 		${EIGEN3_INCLUDE_DIR}
		${SCIPLOT_DIR}
		${SCIPLOT_DIR_1}
	)

set(CPP_FILES 
	src/SearchConvexSet.cpp
	src/Point.cpp
	# src/draw.cpp
)

add_library(convexSet STATIC ${CPP_FILES})

add_executable(main src/main.cpp)

target_link_libraries(main convexSet yaml-cpp  ${CMAKE_THREAD_LIBS_INIT})
