#include <ros/ros.h>
#include <tf2/LinearMath/Vector3.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2_ros/transform_broadcaster.h>


#include <pcl_ros/transforms.h>
#include <laser_geometry/laser_geometry.h>
#include <pcl/ros/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud_conversion.h> 
#include "sensor_msgs/LaserScan.h"
#include "pcl_ros/point_cloud.h"
#include <Eigen/Dense>
#include <dynamic_reconfigure/server.h>
#include <ira_laser_tools/laserscan_multi_mergerConfig.h>


class PointCloud2Merger
{
public:
  PointCloud2Merger();
private:
  ros::NodeHandle node_;
  tf2_ros::Buffer tfBuffer_;
  tf2_ros::TransformListener tfListener_;

  ros::Publisher pc2_publisher_;
  vector<ros::Subscriber> pc2_subscriber_;

  vector<pcl::PCLPointCloud2> cloud_;
  vector<string> input_topic_name_;
  
};


PointCloud2Merger::PointCloud2Merger()
{
  ros::NodeHandle nh();
  pc2_subscriber_.resize(2);
  pc2_subscriber_[0] = node_.subscribe<sensor_msgs::PointCloud2>
  pc2_subscriber_[0] = node_.subscribe(input_cloud_, 5, &euclidean_clustering::poincloud_callback, this);
  }

  
  nh.getParam("point_cloud2_topics", )
  
}
