#include <ros/ros.h>
#include "learning_topic/person.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "person_pub_node");
    ros::NodeHandle nh;
    ros::Publisher person_pub;
    person_pub = nh.advertise<learning_topic::person>("/person", 10);
    ros::Rate loop_rate(0.5);
    while (ros::ok())
    {
        learning_topic::person msg;
        msg.name = "machao";
        msg.age = 100;
        msg.sex = learning_topic::person::male;
        // msg.sex = 1;
        person_pub.publish(msg);
        ROS_INFO("publish person Info: name:%s, age:%d, sex:%d", msg.name.c_str(), msg.age, msg.sex);

        loop_rate.sleep();
    }
    
    return 0;
}
