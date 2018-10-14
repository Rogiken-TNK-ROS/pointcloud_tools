#ifndef POINTCLOUD_CONVERTER_H_INCLUDED
#define POINTCLOUD_CONVERTER_H_INCLUDED

//headers in ROS
#include <ros/ros.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud_conversion.h>

#define TYPE_POINTCLOUD 0
#define TYPE_POINTCLOUD2 1

class pointcloud_converter
{
public:
    pointcloud_converter();
    ~pointcloud_converter();
private:
    void pointcloud_callback_(const sensor_msgs::PointCloud::ConstPtr msg);
    void pointcloud2_callback_(const sensor_msgs::PointCloud2::ConstPtr msg);
    ros::NodeHandle nh_;
    ros::Subscriber sub_;
    ros::Publisher pub_;
    int input_type_;
};

#endif  //POINTCLOUD_CONVERTER_H_INCLUDED