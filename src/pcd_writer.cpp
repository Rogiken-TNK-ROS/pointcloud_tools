#include <pointcloud_tools/pcd_writer.h>

pcd_writer::pcd_writer()
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr latest_message_(new pcl::PointCloud<pcl::PointXYZ>);
    namespace fs = boost::filesystem;
    const fs::path path("/tmp/pcd");
    boost::system::error_code error;
    const bool result = fs::create_directory(path, error);
    if (!result || error)
    {
        //ROS_ERROR_STREAM("failed to create directory");
    }
}

pcd_writer::~pcd_writer()
{
    if(mode_ == SAVE_LATEST_MESSAGE)
    {
        boost::posix_time::ptime my_posix_time = ros::Time::now().toBoost();
        std::string iso_time_str = boost::posix_time::to_iso_extended_string(my_posix_time);
        pcl::io::savePCDFileBinary("/tmp/pcd/"+iso_time_str+".pcd", *latest_message_);
    }
}

void pcd_writer::run(int mode)
{
    mode_ = mode;
    sub_ = nh_.subscribe(ros::this_node::getName()+"/input", 10, &pcd_writer::pointcloud_callback_, this);
    return;
}

void pcd_writer::pointcloud_callback_(const sensor_msgs::PointCloud2::ConstPtr msg)
{
    pcl::fromROSMsg(*msg, *latest_message_);
    if(mode_ == SAVE_EVERY_MESSAGE)
    {
        boost::posix_time::ptime my_posix_time = ros::Time::now().toBoost();
        std::string iso_time_str = boost::posix_time::to_iso_extended_string(my_posix_time);
        pcl::io::savePCDFileBinary("/tmp/pcd/"+iso_time_str+".pcd", *latest_message_);
    }
    return;
}