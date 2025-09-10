#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Spawn.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "my_tf_listener");
    ros::NodeHandle nh;
    ros::Publisher vel_pub;
    ros::service::waitForService("/spawn");
    ros::ServiceClient add_turtle;
    vel_pub = nh.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 10);
    add_turtle = nh.serviceClient<turtlesim::Spawn>("/spawn");
    turtlesim::Spawn srv;
    add_turtle.call(srv);

    
    tf::TransformListener listener;
    ros::Rate rate(10);
    while (ros::ok())
    {
        // 获取坐标系之间的tf数据
        tf::StampedTransform transform;
        try
        {
            listener.waitForTransform("turtle2", "turtle1", ros::Time(0), ros::Duration(3));
            listener.lookupTransform("turtle2", "turtle1", ros::Time(0), transform);
        }
        catch(tf::TransformException &ex)
        {
            ROS_ERROR("%s", ex.what());
            ros::Duration(1.0).sleep();
            continue;
        }

        // 根据坐标见的向量，发布turtle2的速度消息
        geometry_msgs::Twist vel_msg;
        vel_msg.angular.z = 2.0 * atan2(transform.getOrigin().y(), transform.getOrigin().x() );
        vel_msg.linear.x = 0.5 * sqrt(pow(transform.getOrigin().x(), 2) + pow(transform.getOrigin().y(), 2) );
        vel_pub.publish(vel_msg);
        
        rate.sleep();
    }
    

    

    return 0;
}
