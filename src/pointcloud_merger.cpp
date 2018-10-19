#include <pointcloud_tools/pointcloud_merger.h>

pointcloud_merger::pointcloud_merger() : tf_listener_(tf_buffer_)
{
    nh_.param<std::string>(ros::this_node::getName()+"/topic1", pc1_topic_, ros::this_node::getName()+"/points_raw_1");
    nh_.param<std::string>(ros::this_node::getName()+"/topic2", pc2_topic_, ros::this_node::getName()+"/points_raw_2");
    nh_.param<std::string>(ros::this_node::getName()+"/output_topic", output_topic_, ros::this_node::getName()+"/merged_points");
    nh_.param<std::string>(ros::this_node::getName()+"/output_frame", output_frame_, "base_link");
    pointcloud_pub_ = nh_.advertise<sensor_msgs::PointCloud2>(output_topic_, 10);
    pc1_sub_ = boost::make_shared<message_filters::Subscriber<sensor_msgs::PointCloud2> >(nh_, pc1_topic_, 1);
    pc2_sub_ = boost::make_shared<message_filters::Subscriber<sensor_msgs::PointCloud2> >(nh_, pc2_topic_, 1);
    sync_ = boost::make_shared<message_filters::Synchronizer<sync_policy> >(sync_policy(10), *pc1_sub_, *pc2_sub_);
}

pointcloud_merger::~pointcloud_merger()
{

}

void pointcloud_merger::callback_(const sensor_msgs::PointCloud2ConstPtr& pc1_msg, const sensor_msgs::PointCloud2ConstPtr& pc2_msg)
{
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr pcl_pc1;
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr pcl_pc2;
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr output_pcl_pc_;
    sensor_msgs::PointCloud2 transformed_pc1;
    sensor_msgs::PointCloud2 transformed_pc2;
    if(pc1_msg->header.frame_id != output_frame_)
    {
        geometry_msgs::TransformStamped transform_stamped;
        transform_stamped = tf_buffer_.lookupTransform(pc1_msg->header.frame_id, output_frame_, ros::Time(0));
        tf2::doTransform(*pc1_msg, transformed_pc1, transform_stamped);
    }
    else
    {
        transformed_pc1 = *pc1_msg;
    }
    if(pc2_msg->header.frame_id != output_frame_)
    {
        geometry_msgs::TransformStamped transform_stamped;
        transform_stamped = tf_buffer_.lookupTransform(pc2_msg->header.frame_id, output_frame_, ros::Time(0));
        tf2::doTransform(*pc2_msg, transformed_pc2, transform_stamped);
    }
    else
    {
        transformed_pc2 = *pc2_msg;
    }
    pcl::fromROSMsg(transformed_pc1, *pcl_pc1);
    pcl::fromROSMsg(transformed_pc2, *pcl_pc2);
    *output_pcl_pc_ = *pcl_pc1 + *pcl_pc2;
    return;
}