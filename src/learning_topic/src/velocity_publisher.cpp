#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "velocity_publisher_node");

    ros::NodeHandle nh;

    ros::Publisher turtle_vel_pub;
    turtle_vel_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    ros::Rate loop_rate(10);
    
    int count = 0;

    while (ros::ok())
    {
       geometry_msgs::Twist vel_msg;
       vel_msg.angular.z = 0.8;
       vel_msg.linear.x = 1;
       turtle_vel_pub.publish(vel_msg);
       ROS_INFO("publish Turtle velocity command[%.2f m/s, %.2f rad/s]", vel_msg.linear.x, vel_msg.angular.z);
       loop_rate.sleep();
    }

    return 0;
}
