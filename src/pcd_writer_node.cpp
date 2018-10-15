// headers in this package
#include <pointcloud_tools/pcd_writer.h>

// headers for ros
#include <ros/ros.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "pcd_writer_node");
    pcd_writer writer;
    ros::spin();
    return 0;
}