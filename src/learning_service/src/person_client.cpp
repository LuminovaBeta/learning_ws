#include <ros/ros.h>
#include <learning_service/person.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "person_client");
    ros::NodeHandle nh;
    ros::service::waitForService("/show_person");
    ros::ServiceClient person_client;
    person_client = nh.serviceClient<learning_service::person>("/show_person");
    learning_service::person srv;
    srv.request.name = "machao";
    srv.request.age = 100;
    srv.request.sex = 1;
    person_client.call(srv);
    ROS_INFO("call service to show person[name:%s, age:%d, sex:%d]",srv.request.name.c_str(), srv.request.age, srv.request.sex);
    ROS_INFO("show person result:%s", srv.response.result.c_str());
    return 0;
}
