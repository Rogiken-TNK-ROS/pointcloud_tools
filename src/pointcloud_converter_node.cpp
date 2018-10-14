// headers in this package
#include <pointcloud_tools/pointcloud_converter.h>

// headers for ros
#include <ros/ros.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "pointcloud_converter_node");
    pointcloud_converter converter;
    ros::spin();
    return 0;
}