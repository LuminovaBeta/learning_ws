#include <ros/ros.h>
#include <learning_service/person.h>

bool person_callbacl(learning_service::person::Request &req, learning_service::person::Response &res)
{
    ROS_INFO("person request [name:%s, age:%d, sex:%d]", req.name.c_str(), req.age, req.sex);

    res.result = "OKOKOKOKOKOOK";
    return true;
}
int main(int argc, char *argv[])
{
    ros::init(argc, argv, "person_server_node");
    ros::NodeHandle nh;
    ros::ServiceServer person_server;
    person_server = nh.advertiseService("/show_person", person_callbacl);

    ROS_INFO("deady to show person information");
    ros::spin();
    return 0;
}
