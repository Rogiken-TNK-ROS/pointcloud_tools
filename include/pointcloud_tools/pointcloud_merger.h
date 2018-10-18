#ifndef POINTCLOUD_MERGER_NODE_H_INCLUDED
#define POINTCLOUD_MERGER_NODE_H_INCLUDED

//headers in ROS
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

//headers in PCL
#include <pcl_conversions/pcl_conversions.h>

//headers in boost
#include <boost/shared_ptr.hpp>

typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::PointCloud2, sensor_msgs::PointCloud2> sync_policy;

class pointcloud_merger
{
public:
    pointcloud_merger();
    ~pointcloud_merger();
private:
    void callback_(const sensor_msgs::PointCloud2ConstPtr& pc1_msg, const sensor_msgs::PointCloud2ConstPtr& pc2_msg);
    std::string pc1_topic_;
    boost::shared_ptr<message_filters::Subscriber<sensor_msgs::PointCloud2> > pc1_sub_;
    std::string pc2_topic_;
    boost::shared_ptr<message_filters::Subscriber<sensor_msgs::PointCloud2> > pc2_sub_;
    ros::Publisher pointcloud_pub_;
    boost::shared_ptr<message_filters::Synchronizer<sync_policy> > sync_;
    ros::NodeHandle nh_;
};

#endif  //POINTCLOUD_MERGER_NODE_H_INCLUDED