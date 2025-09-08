#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include <std_srvs/Trigger.h>

ros::Publisher vel_com_pub;
bool PubCommand = false;

bool turtle_command_callback(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res)
{
    PubCommand = !PubCommand;

    ROS_INFO("Publish turtle vel command [%s]", PubCommand==true?"yes":"no");
    res.message = "change turtle command state";
    res.success = true;

    return true;
}
int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "zh_CN.UTF-8");
    ros::init(argc, argv, "turtle_command_server");
    ros::NodeHandle nh;
    ros::ServiceServer command_server;
    command_server = nh.advertiseService("/turtle_command", turtle_command_callback);
    vel_com_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    ros::Rate loop_rate(10);

    ROS_INFO("速度发布服务以就绪，等待服务请求");
    while (ros::ok())
    {
        ros::spinOnce();
        if(PubCommand)
        {
            geometry_msgs::Twist vel_msg;
            vel_msg.linear.x = 1;
            vel_msg.angular.z = 0.8;
            vel_com_pub.publish(vel_msg);
        }
        loop_rate.sleep();
    }
    return 0;
}
