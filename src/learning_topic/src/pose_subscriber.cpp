#include <ros/ros.h>
#include "turtlesim/Pose.h"
void pose_cb(const turtlesim::Pose::ConstPtr& msg)
{
    ROS_INFO("Turtle Pose:[x:%.2f, y:%.2f]", msg->x, msg->y);
}
int main(int argc, char *argv[])
{
    ros::init(argc, argv, "pose_subscriber_node");
    ros::NodeHandle nh;
    ros::Subscriber pose_sub;
    pose_sub = nh.subscribe("/turtle1/pose", 10, pose_cb);
    while (ros::ok())
    {
        ros::spin();
    }
    
    return 0;
}
