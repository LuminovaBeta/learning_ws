#include <ros/ros.h>
#include "learning_topic/person.h"
void person_info_callback(learning_topic::person msg)
{
    ROS_INFO("subscriber person Info: name:%s, age:%d, sex:%d", msg.name.c_str(), msg.age, msg.sex);
}
int main(int argc, char *argv[])
{
    ros::init(argc, argv, "person_sub");
    ros::NodeHandle nh;
    ros::Subscriber person_sub;
    person_sub = nh.subscribe("/person", 10, person_info_callback);

    ros::spin();
    
    return 0;
}
