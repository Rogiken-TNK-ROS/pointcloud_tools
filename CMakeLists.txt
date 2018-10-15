cmake_minimum_required(VERSION 2.8.3)
project(pointcloud_tools)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  pcl_ros
  roscpp
  rospy
  sensor_msgs
  std_msgs
  tf2
  tf2_geometry_msgs
  tf2_ros
  tf2_sensor_msgs
)

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES pointcloud_tools
  CATKIN_DEPENDS geometry_msgs pcl_ros roscpp rospy sensor_msgs std_msgs tf2 tf2_geometry_msgs tf2_ros tf2_sensor_msgs
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(pointcloud_converter_node src/pointcloud_converter_node.cpp src/pointcloud_converter.cpp)
target_link_libraries(pointcloud_converter_node ${catkin_LIBRARIES})

add_executable(pcd_writer_node src/pcd_writer_node.cpp src/pcd_writer.cpp)
target_link_libraries(pcd_writer_node ${catkin_LIBRARIES})

set(CPP_EXEC_NAMES 
  pointcloud_converter_node
  pcd_writer_node
  )
foreach(cpp_exec_names ${CPP_EXEC_NAMES})
  install(TARGETS ${cpp_exec_names}
    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
    )
endforeach(cpp_exec_names)
# include header files
install(DIRECTORY include/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

foreach(dir launch config)
  install(DIRECTORY ${dir}/
    DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)