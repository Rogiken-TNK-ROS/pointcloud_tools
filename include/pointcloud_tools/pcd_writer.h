#ifndef PCD_WRITER_H_INCLUDED
#define PCD_WRITER_H_INCLUDED

//headers in ROS
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>

//headers in Boost
#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

//headers in PCL
#include <pcl/io/pcd_io.h>
#include <pcl_conversions/pcl_conversions.h>

#define SAVE_LATEST_MESSAGE 0
#define SAVE_EVERY_MESSAGE 1

class pcd_writer
{
public:
    pcd_writer();
    ~pcd_writer();
    void run(int mode);
private:
    void pointcloud_callback_(const sensor_msgs::PointCloud2::ConstPtr msg);
    ros::NodeHandle nh_;
    ros::Subscriber sub_;
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr latest_message_;
    int mode_;
};
#endif  //PCD_WRITER_H_INCLUDED