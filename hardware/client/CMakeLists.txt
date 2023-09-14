cmake_minimum_required(VERSION 3.0)

project(gc_client)

find_package(OpenCL REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(XILINX_XRT /opt/xilinx/xrt)
set(XILINX_VITIS /home/Vitis/Vitis/2021.1/)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../host/include)
include_directories(${OpenCL_INCLUDE_DIRS})
include_directories(${XILINX_XRT}/include)

set(BOOST_ROOT /home/hfeng/tool/boost)
find_package(Boost 1.81 REQUIRED COMPONENTS program_options)

link_directories(${CMAKE_INSTALL_PREFIX}/lib)

file(GLOB SOURCES src/*.c*)

# todo build as library for titan use
#add_executable(${PROJECT_NAME} ${SOURCES})

#target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR})
#target_link_libraries(${PROJECT_NAME} compression-host pthread dl ${Boost_LIBRARIES})

#install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)