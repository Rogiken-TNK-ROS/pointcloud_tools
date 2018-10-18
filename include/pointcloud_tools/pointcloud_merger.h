#ifndef POINTCLOUD_MERGER_NODE_H_INCLUDED
#define POINTCLOUD_MERGER_NODE_H_INCLUDED

//headers in ROS
#include <ros/ros.h>

//headers in PCL
#include <pcl_conversions/pcl_conversions.h>

class pointcloud_merger
{
public:
    pointcloud_merger();
    ~pointcloud_merger();
private:
    ros::NodeHandle nh_;
};

#endif  //POINTCLOUD_MERGER_NODE_H_INCLUDED