// headers in this package
#include <pointcloud_tools/pointcloud_converter.h>

pointcloud_converter::pointcloud_converter()
{
    std::string input_type_str;
    ros::param::param<std::string>(ros::this_node::getName() + "/input_type", input_type_str, "pointcloud");
    if(input_type_str == "pointcloud")
    {
        input_type_ = TYPE_POINTCLOUD;
    }
    else if(input_type_str == "pointcloud2")
    {
        input_type_ = TYPE_POINTCLOUD2;
    }
    else
    {
        input_type_ = TYPE_POINTCLOUD;
    }
    if(input_type_ == TYPE_POINTCLOUD)
    {
        pub_ = nh_.advertise<sensor_msgs::PointCloud2>(ros::this_node::getName()+"/output", 10);
        sub_ = nh_.subscribe(ros::this_node::getName()+"/input", 10, &pointcloud_converter::pointcloud_callback_, this);
    }
    else
    {
        pub_ = nh_.advertise<sensor_msgs::PointCloud>(ros::this_node::getName()+"/output", 10);
        sub_ = nh_.subscribe(ros::this_node::getName()+"/input", 10, &pointcloud_converter::pointcloud2_callback_, this);
    }
}

pointcloud_converter::~pointcloud_converter()
{

}

void pointcloud_converter::pointcloud_callback_(const sensor_msgs::PointCloud::ConstPtr msg)
{
    sensor_msgs::PointCloud2 output;
    sensor_msgs::convertPointCloudToPointCloud2(*msg, output);
    pub_.publish(output);
    return;
}

void pointcloud_converter::pointcloud2_callback_(const sensor_msgs::PointCloud2::ConstPtr msg)
{
    sensor_msgs::PointCloud output;
    sensor_msgs::convertPointCloud2ToPointCloud(*msg, output);
    pub_.publish(output);
    return;
}